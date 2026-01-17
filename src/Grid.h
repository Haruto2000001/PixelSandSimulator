#pragma once

#include <cstdint>
#include <vector>

enum Cell : uint8_t { EMPTY = 0, WALL = 1, SAND = 2, WATER = 3 };

const char* CellName(Cell c);

class Grid {
 public:
  Grid(int width, int height);

  int width() const;
  int height() const;

  bool inBounds(int x, int y) const;
  int idx(int x, int y) const;

  Cell get(int x, int y) const;
  void set(int x, int y, Cell c);

  void clear(Cell value = EMPTY);
  void paintCircle(int cx, int cy, int r, Cell cell);

  const std::vector<Cell>& cells() const;
  std::vector<Cell>& cells();

 private:
  int width_;
  int height_;
  std::vector<Cell> cells_;
};
