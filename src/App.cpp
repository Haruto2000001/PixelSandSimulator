#include "App.h"

#include <SDL.h>

#include <cstdio>
using namespace std;

// まずコンストラクタ
App::App(int width, int height, int scale)
    : width_(width),
      height_(height),
      scale_(scale),
      grid_(width, height),
      simulator_(width, height),
      renderer_(),
      input_(scale),
      lastTicks_(0),
      fps_(0.0f),
      titleTimer_(0) {}

// SDLのウィンドウ設定
bool App::init() {
  // ウィンドウをビデオモードに初期化
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return false;
  }

  // 　レンダラーの初期化
  if (!renderer_.init("SDL2 Pixel Sand Simulator", width_, height_, scale_)) {
    renderer_.shutdown();
    SDL_Quit();
    return false;
  }

  // 前のフレームの時刻の初期化
  lastTicks_ = SDL_GetTicks();
  return true;
}

// SDL2の描画を開始
// inputを受け付けてinput_に渡すだけで良い
void App::run() {
  while (input_.running()) {
    // 入力を受け取る
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      input_.handleEvent(e, grid_);
    }

    // マウスを押していた場合は粒子を作成し,
    input_.handleMouse(grid_);
    // 次のステップをシミュレーションし、
    if (!input_.paused()) {
      simulator_.step(grid_);
    }
    // レンダーする
    renderer_.render(grid_);

    // FPSの計算
    uint32_t now = SDL_GetTicks();
    uint32_t dt = now - lastTicks_;
    lastTicks_ = now;
    if (dt > 0) {
      fps_ = 1000.0f / static_cast<float>(dt);
    }

    // 毎回更新すると重いので100溜まってから
    titleTimer_ += dt;
    if (titleTimer_ > 100) {
      titleTimer_ = 0;
      updateTitle();
    }
  }

  renderer_.shutdown();
  SDL_Quit();
}

void App::updateTitle() {
  char title[128];
  snprintf(title, sizeof(title),
           "SDL2 Sand | %dx%d | mode=%s | brush=%d | FPS=%.1f | %s", width_,
           height_, CellName(input_.mode()), input_.brush(), fps_,
           input_.paused() ? "PAUSED" : "RUN");
  renderer_.setTitle(title);
}
/*

#include "App.h"

#include <SDL.h>
#include <cstdio>
App::App(int width, int height, int scale)
    : width_(width)
    , height_(height)
    , scale_(scale)
    , grid_(width, height)
    , simulator_(width, height)
    , renderer_()
    , input_(scale)
    , lastTicks_(0)
    , fps_(0.0f)
    , titleTimer_(0) {}

bool App::init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return false;
  }

  if (!renderer_.init("SDL2 Sand (Streaming Texture)", width_, height_,
                      scale_)) {
    renderer_.shutdown();
    SDL_Quit();
    return false;
  }

  lastTicks_ = SDL_GetTicks();
  return true;
}

void App::run() {
  while (input_.running()) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      input_.handleEvent(e, grid_);
    }

    input_.handleMouse(grid_);

    if (!input_.paused()) {
      simulator_.step(grid_);
    }

    renderer_.render(grid_);

    uint32_t now = SDL_GetTicks();
    uint32_t dt = now - lastTicks_;
    lastTicks_ = now;
    if (dt > 0) {
      fps_ = 1000.0f / static_cast<float>(dt);
    }

    titleTimer_ += dt;
    if (titleTimer_ > 250) {
      titleTimer_ = 0;
      updateTitle();
    }
  }

  renderer_.shutdown();
  SDL_Quit();
}

void App::updateTitle() {
  char title[128];
  std::snprintf(title, sizeof(title),
                "SDL2 Sand | %dx%d | mode=%s | brush=%d | FPS=%.1f | %s",
                width_, height_, CellName(input_.mode()), input_.brush(), fps_,
                input_.paused() ? "PAUSED" : "RUN");
  renderer_.setTitle(title);
}

*/
