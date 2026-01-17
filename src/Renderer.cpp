#include "Renderer.h"

#include <cstring>

Renderer::Renderer()
    : width_(0),
      height_(0),
      window_(nullptr),
      renderer_(nullptr),
      texture_(nullptr),
      pixels_() {}

Renderer::~Renderer() { shutdown(); }

bool Renderer::init(const char* title, int width, int height, int scale) {
  width_ = width;
  height_ = height;
  pixels_.assign(width_ * height_, 0);

  window_ =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width_ * scale, height_ * scale, SDL_WINDOW_SHOWN);
  if (!window_) {
    SDL_Log("CreateWindow: %s", SDL_GetError());
    return false;
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer_) {
    SDL_Log("CreateRenderer: %s", SDL_GetError());
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  SDL_RenderSetLogicalSize(renderer_, width_, height_);

  texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING, width_, height_);
  if (!texture_) {
    SDL_Log("CreateTexture: %s", SDL_GetError());
    return false;
  }

  return true;
}

void Renderer::render(const Grid& grid) {
  static const uint32_t LUT[] = {
      0xFF101014,  // EMPTY
      0xFF6B6B6B,  // WALL
      0xFFFFD050,  // SAND
      0xFF3F7BFF   // WATER
  };

  const auto& cells = grid.cells();
  for (size_t i = 0; i < cells.size(); ++i) {
    pixels_[i] = LUT[static_cast<uint8_t>(cells[i])];
  }

  void* texPixels = nullptr;
  int pitch = 0;
  if (SDL_LockTexture(texture_, nullptr, &texPixels, &pitch) == 0) {
    for (int y = 0; y < height_; ++y) {
      std::memcpy(static_cast<uint8_t*>(texPixels) + y * pitch,
                  &pixels_[y * width_], width_ * sizeof(uint32_t));
    }
    SDL_UnlockTexture(texture_);
  }

  SDL_RenderClear(renderer_);
  SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
  SDL_RenderPresent(renderer_);
}

void Renderer::setTitle(const char* title) {
  if (window_) {
    SDL_SetWindowTitle(window_, title);
  }
}

void Renderer::shutdown() {
  if (texture_) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }
  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }
  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }
}
