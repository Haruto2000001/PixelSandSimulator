#pragma once

#include <SDL.h>

#include "Grid.h"

class Input {
public:
  explicit Input(int scale);

  void handleEvent(const SDL_Event &e, Grid &grid);
  void handleMouse(Grid &grid);

  bool running() const;
  bool paused() const;
  int brush() const;
  Cell mode() const;

private:
  int scale_;
  bool running_;
  bool paused_;
  bool leftDown_;
  bool rightDown_;
  int brush_;
  Cell mode_;
};
