#include "vga.h"
#include "keyboard.h"

#include <cstdio>
#include <cstring>
#include <SDL2/SDL.h>

static uint32_t g_screen_w = 400;
static uint32_t g_screen_h = 300;

static SDL_Window   *g_sdl_window   = nullptr;  // 窗口句柄
static SDL_Renderer *g_sdl_renderer = nullptr;  // GPU 渲染器（硬件加速）
static SDL_Texture  *g_sdl_texture  = nullptr;  // 纹理 = 显存中的像素数组 要把g_fp传到这个里面
static uint32_t     *g_fb           = nullptr;  // CPU 侧的像素数组（双缓冲的背面） cpu在fb拼完后搬到屏幕上
static bool          g_sdl_ready    = false;     // 初始化完成标志（防重入）
static bool          g_sdl_quit     = false;     // 收到退出信号

// BLIT 寄存器（临时存储参数）
static uint32_t blit_src  = 0;
static int      blit_x    = 0;
static int      blit_y    = 0;
static int      blit_w    = 0;
static int      blit_h    = 0;

// dpic.cpp 提供的批量读接口
extern "C" void pmem_read_bulk(uint32_t addr, uint32_t *dst, int count);

// ===== SDL 初始化（懒加载，首次渲染时触发） =====

static void sdl_init(void) 
{
  if (g_sdl_ready) return;   //只跑一次
  if (SDL_Init(SDL_INIT_VIDEO) != 0) return; //初始化sdl视频子系统
  g_sdl_window = SDL_CreateWindow     //创建窗口
  (   
      "NPC VGA",
      SDL_WINDOWPOS_UNDEFINED, 
      SDL_WINDOWPOS_UNDEFINED,
      (int)g_screen_w, 
      (int)g_screen_h,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
  if (!g_sdl_window) return;
  g_sdl_renderer = SDL_CreateRenderer(g_sdl_window, -1, SDL_RENDERER_ACCELERATED); //创建硬件加速渲染器
  if (!g_sdl_renderer) return;
  g_sdl_texture = SDL_CreateTexture     //创建显存画布 每帧更新 4字节像素
  (   
      g_sdl_renderer,
      SDL_PIXELFORMAT_ARGB8888, 
      SDL_TEXTUREACCESS_STREAMING,
      (int)g_screen_w, 
      (int)g_screen_h
    );
  if (!g_sdl_texture) return;
  g_fb = new uint32_t[g_screen_w * g_screen_h];     //分配cpu帧缓冲 初始化黑色
  std::memset(g_fb, 0, g_screen_w * g_screen_h * sizeof(uint32_t));//std防止撞名 用标准库的函数
  g_sdl_ready = true;
  std::printf("[VGA] SDL initialized, screen %ux%u\n", g_screen_w, g_screen_h);
}

// ===== 屏幕渲染 + SDL 事件处理 =====

static void sdl_render(void) 
{
  if (!g_sdl_ready) return;

  SDL_UpdateTexture(g_sdl_texture, nullptr, g_fb,
                    (int)g_screen_w * (int)sizeof(uint32_t)); 
  //把g_fb从cpu内存传到gpu纹理 每行字节数400*4 
  
  SDL_RenderClear(g_sdl_renderer);  //清空渲染器
  SDL_RenderCopy(g_sdl_renderer, g_sdl_texture, nullptr, nullptr); //把纹理画到渲染器？
  SDL_RenderPresent(g_sdl_renderer);  //交换缓冲区 屏幕可见
    //标准的 SDL2 渲染流程：Update → Clear → Copy → Present。缺一步屏幕就不更新。


  SDL_Event ev;
  while (SDL_PollEvent(&ev)) //遍历事件列表
  {
    if (ev.type == SDL_QUIT) 
    {
      std::printf("[VGA] SDL window closed, quitting...\n");
      g_sdl_quit = true;
      SDL_DestroyTexture(g_sdl_texture);
      SDL_DestroyRenderer(g_sdl_renderer);
      SDL_DestroyWindow(g_sdl_window);
      SDL_Quit();
      g_sdl_ready = false;
    }
    keyboard_handle_event(&ev);  // 投喂给键盘模块 模块收到键盘事件后转给键盘模块入队。
  }
}

// ===== BLIT：从 guest pmem 批量拷贝像素到帧缓冲 =====

static void gpu_blit(void) 
{
  int x = blit_x, y = blit_y, w = blit_w, h = blit_h;
  if (w <= 0 || h <= 0) return;
  if (x < 0) x = 0;
  if (y < 0) y = 0;
  if (x + w > (int)g_screen_w) w = (int)g_screen_w - x;
  if (y + h > (int)g_screen_h) h = (int)g_screen_h - y;
  if (w <= 0 || h <= 0) return;

  uint32_t *row_buf = new uint32_t[w];
  for (int j = 0; j < h; j++) 
  {
    pmem_read_bulk(blit_src + j * w * 4, row_buf, w);
    std::memcpy(&g_fb[(y + j) * g_screen_w + x], row_buf, w * sizeof(uint32_t));
  }
  delete[] row_buf;
}

// ===== 对外接口 =====

bool vga_in_range(uint32_t addr) 
{
  return addr >= VGACTL_ADDR && addr <= BLIT_BASE + 20;
}

uint32_t vga_read(uint32_t addr, int len) 
{
  if (addr == VGACTL_ADDR)  // 返回屏幕尺寸，不初始化 SDL（延迟到渲染）
    return (g_screen_w << 16) | g_screen_h;
  return 0;
}

void vga_write(uint32_t addr, int len, uint32_t data) 
{
  if (addr == SYNC_ADDR)       { sdl_init(); sdl_render(); return; }
  if (addr == BLIT_BASE + 0)  { blit_src = data; return; }
  if (addr == BLIT_BASE + 4)  { blit_x   = (int)data; return; }
  if (addr == BLIT_BASE + 8)  { blit_y   = (int)data; return; }
  if (addr == BLIT_BASE + 12) { blit_w   = (int)data; return; }
  if (addr == BLIT_BASE + 16) { blit_h   = (int)data; return; }
  if (addr == BLIT_BASE + 20) { sdl_init(); gpu_blit(); return; } //BLIT_BASE+0 到 +16 只是暂存参数，+20（EXEC）才真正执行。
}

bool vga_was_ready(void) { return g_sdl_ready; }

bool vga_quit(void) //退出检查，每周期被调
{
  SDL_Event ev;
  while (SDL_PollEvent(&ev))
  {
    if (ev.type == SDL_QUIT) 
    {
      g_sdl_quit = true;
      if (g_sdl_ready) 
      {
        // 直接销毁窗口，不依赖 sdl_render
        SDL_DestroyTexture(g_sdl_texture);
        SDL_DestroyRenderer(g_sdl_renderer);
        SDL_DestroyWindow(g_sdl_window);
        SDL_Quit();
        g_sdl_ready = false;
      }
    }
    else { keyboard_handle_event(&ev); }
  }
  return g_sdl_quit || keyboard_quit();
}
