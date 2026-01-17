#pragma once

#include <cstdint>
#include <random>
#include <vector>

#include "Grid.h"

class Simulator {
public:
  Simulator(int width, int height);

  void step(Grid &grid);

private:
  void stepSand(Grid &grid, int x, int y);
  void stepWater(Grid &grid, int x, int y);

  int width_;
  int height_;
  std::vector<uint8_t> moved_;
  std::mt19937 rng_;
  bool flip_;
};
