#include "Simulator.h"

#include <algorithm>
using namespace std;
// コンストラクタ
Simulator::Simulator(int width, int height)
    : width_(width),
      height_(height),
      moved_(width * height, 0),
      rng_(12345),
      flip_(false) {}

void Simulator::step(Grid& grid) {
  std::fill(moved_.begin(), moved_.end(), 0);
  flip_ = !flip_;

  for (int y = height_ - 2; y >= 0; --y) {
    if (!flip_) {
      for (int x = 0; x < width_; ++x) {
        stepSand(grid, x, y);
        stepWater(grid, x, y);
      }
    } else {
      for (int x = width_ - 1; x >= 0; --x) {
        stepSand(grid, x, y);
        stepWater(grid, x, y);
      }
    }
  }
}
void Simulator::stepSand(Grid& grid, int x, int y) {
  // cells_: 一次元のgrid
  auto& cells = grid.cells();
  // 現在地
  int i = grid.idx(x, y);
  if (cells[i] != SAND || moved_[i]) {
    return;
  }

  // 交換する関数(交換できなかった場合だけfalseが返ってくる)
  auto trySwap = [&](int nx, int ny) -> bool {
    if (!grid.inBounds(nx, ny)) return false;
    int j = grid.idx(nx, ny);
    if (cells[j] == EMPTY || cells[j] == WATER) {
      swap(cells[i], cells[j]);
      moved_[j] = 1;
      return true;
    }
    return false;
  };

  // 真下 -> 斜め下
  if (trySwap(x, y + 1)) {
    return;
  }

  if (!flip_) {
    if (trySwap(x - 1, y + 1)) return;
    if (trySwap(x + 1, y + 1)) return;
  } else {
    if (trySwap(x + 1, y + 1)) return;
    if (trySwap(x - 1, y + 1)) return;
  }
}

void Simulator::stepWater(Grid& grid, int x, int y) {
  // cells_: 一次元のgrid
  auto& cells = grid.cells();
  // 現在地
  int i = grid.idx(x, y);
  if (cells[i] != WATER || moved_[i]) {
    return;
  }

  auto tryMove = [&](int nx, int ny) -> bool {
    if (!grid.inBounds(nx, ny)) return false;
    int j = grid.idx(nx, ny);
    if (cells[j] == EMPTY) {
      swap(cells[i], cells[j]);
      moved_[j] = 1;
      return true;
    }
    return false;
  };

  // 真下 -> 斜め下
  if (tryMove(x, y + 1)) {
    return;
  }

  if (!flip_) {
    if (tryMove(x - 1, y + 1)) return;
    if (tryMove(x + 1, y + 1)) return;
  } else {
    if (tryMove(x + 1, y + 1)) return;
    if (tryMove(x - 1, y + 1)) return;
  }

  // 確率で左右に動くことで、真下or斜め下にスペースが出現する
  // なので次のstepで真下or斜めに移動しやすくなり、高さが揃う
  if ((rng_() & 1) == 0) {
    if (tryMove(x - 1, y)) return;
    if (tryMove(x + 1, y)) return;
  } else {
    if (tryMove(x + 1, y)) return;
    if (tryMove(x - 1, y)) return;
  }
}
/*

#include "Simulator.h"

#include <algorithm>

Simulator::Simulator(int width, int height)
    : width_(width),
      height_(height),
      moved_(width * height, 0),
      rng_(12345),
      flip_(false) {}

void Simulator::step(Grid &grid) {
  std::fill(moved_.begin(), moved_.end(), 0);
  flip_ = !flip_;

  for (int y = height_ - 2; y >= 0; --y) {
    if (!flip_) {
      for (int x = 0; x < width_; ++x) {
        stepSand(grid, x, y);
        stepWater(grid, x, y);
      }
    } else {
      for (int x = width_ - 1; x >= 0; --x) {
        stepSand(grid, x, y);
        stepWater(grid, x, y);
      }
    }
  }
}

void Simulator::stepSand(Grid &grid, int x, int y) {
  auto &cells = grid.cells();
  int i = grid.idx(x, y);
  if (cells[i] != SAND || moved_[i])
    return;

  auto trySwap = [&](int nx, int ny) -> bool {
    if (!grid.inBounds(nx, ny))
      return false;
    int j = grid.idx(nx, ny);
    if (cells[j] == EMPTY || cells[j] == WATER) {
      std::swap(cells[i], cells[j]);
      moved_[j] = 1;
      return true;
    }
    return false;
  };

  if (trySwap(x, y + 1))
    return;

  if (!flip_) {
    if (trySwap(x - 1, y + 1))
      return;
    if (trySwap(x + 1, y + 1))
      return;
  } else {
    if (rng_() & 1)
      return;
    if (rng_() & 0)
      return;
    if (trySwap(x + 1, y + 1))
      return;
    if (trySwap(x - 1, y + 1))
      return;
  }
}

void Simulator::stepWater(Grid &grid, int x, int y) {
  auto &cells = grid.cells();
  int i = grid.idx(x, y);
  if (cells[i] != WATER || moved_[i])
    return;

  auto tryMove = [&](int nx, int ny) -> bool {
    if (!grid.inBounds(nx, ny))
      return false;
    int j = grid.idx(nx, ny);
    if (cells[j] == EMPTY) {
      std::swap(cells[i], cells[j]);
      moved_[j] = 1;
      return true;
    }
    return false;
  };

  if (tryMove(x, y + 1))
    return;

  if (!flip_) {
    if (tryMove(x - 1, y + 1))
      return;
    if (tryMove(x + 1, y + 1))
      return;
  } else {
    if (tryMove(x + 1, y + 1))
      return;
    if (tryMove(x - 1, y + 1))
      return;
  }

  if ((rng_() & 1) == 0) {
    if (tryMove(x - 1, y))
      return;
    if (tryMove(x + 1, y))
      return;
  } else {
    if (tryMove(x + 1, y))
      return;
    if (tryMove(x - 1, y))
      return;
  }
}
*/