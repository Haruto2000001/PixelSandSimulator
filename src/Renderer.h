#pragma once

#include <SDL.h>
#include <cstdint>
#include <vector>

#include "Grid.h"

class Renderer {
public:
  Renderer();
  ~Renderer();

  bool init(const char *title, int width, int height, int scale);
  void render(const Grid &grid);
  void setTitle(const char *title);
  void shutdown();

private:
  int width_;
  int height_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;
  SDL_Texture *texture_;
  std::vector<uint32_t> pixels_;
};
