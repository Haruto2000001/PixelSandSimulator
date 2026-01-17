#include "Grid.h"

#include <algorithm>
using namespace std;

const char* CellName(Cell c) {
  switch (c) {
    case EMPTY:
      return "EMPTY";
    case WALL:
      return "WALL";
    case SAND:
      return "SAND";
    case WATER:
      return "WATER";
    default:
      return "UNKNOWN";
  }
}

Grid::Grid(int width, int height)
    : width_(width), height_(height), cells_(width * height, EMPTY) {}

int Grid::width() const { return width_; }
int Grid::height() const { return height_; }
bool Grid::inBounds(int x, int y) const {
  return 0 <= x && x < width_ && 0 <= y && y < height_;
}
int Grid::idx(int x, int y) const { return y * width_ + x; }
Cell Grid::get(int x, int y) const { return cells_[idx(x, y)]; }
void Grid::set(int x, int y, Cell c) { cells_[idx(x, y)] = c; }
void Grid::clear(Cell value) { fill(cells_.begin(), cells_.end(), value); }
void Grid::paintCircle(int cx, int cy, int r, Cell cell) {
  int r2 = r * r;
  for (int dx = -r2; dx <= r2; dx++) {
    for (int dy = -r2; dy <= r2; dy++) {
      if ((dx * dx + dy * dy) > r2) continue;
      int x = cx + dx;
      int y = cy + dy;
      if (!inBounds(x, y)) continue;
      cells_[idx(x, y)] = cell;
    }
  }
}

const vector<Cell>& Grid::cells() const { return cells_; }
vector<Cell>& Grid::cells() { return cells_; }
/*
#include "Grid.h"

#include <algorithm>

const char* CellName(Cell c) {
  switch (c) {
    case EMPTY:
      return "EMPTY";
    case WALL:
      return "WALL";
    case SAND:
      return "SAND";
    case WATER:
      return "WATER";
    default:
      return "UNKNOWN";
  }
}

Grid::Grid(int width, int height)
    : width_(width), height_(height), cells_(width * height, EMPTY) {}

int Grid::width() const { return width_; }

int Grid::height() const { return height_; }

bool Grid::inBounds(int x, int y) const {
  return 0 <= x && x < width_ && 0 <= y && y < height_;
}

int Grid::idx(int x, int y) const { return y * width_ + x; }

Cell Grid::get(int x, int y) const { return cells_[idx(x, y)]; }

void Grid::set(int x, int y, Cell c) { cells_[idx(x, y)] = c; }

void Grid::clear(Cell value) { std::fill(cells_.begin(), cells_.end(), value); }

void Grid::paintCircle(int cx, int cy, int r, Cell cell) {
  int r2 = r * r;
  for (int dy = -r; dy <= r; dy++) {
    for (int dx = -r; dx <= r; dx++) {
      if (dx * dx + dy * dy > r2) continue;
      int x = cx + dx;
      int y = cy + dy;
      if (!inBounds(x, y)) continue;
      cells_[idx(x, y)] = cell;
    }
  }
}

// 読み取り専用
const std::vector<Cell>& Grid::cells() const { return cells_; }
// 更新用
std::vector<Cell>& Grid::cells() { return cells_; }
*/