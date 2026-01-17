#pragma once

#include <cstdint>

#include "Grid.h"
#include "Input.h"
#include "Renderer.h"
#include "Simulator.h"

class App {
 public:
  App(int width, int height, int scale);
  bool init();
  void run();

 private:
  void updateTitle();

  int width_;
  int height_;
  int scale_;

  Grid grid_;
  Simulator simulator_;
  Renderer renderer_;
  Input input_;

  uint32_t lastTicks_;  // 前のフレームの時刻
  float fps_;
  uint32_t titleTimer_;
};
