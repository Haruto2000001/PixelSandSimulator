#include "Input.h"

#include <algorithm>
using namespace std;

Input::Input(int scale)
    : scale_(scale),
      running_(true),
      paused_(false),
      leftDown_(false),
      rightDown_(false),
      brush_(4),
      mode_(SAND) {}

void Input::handleEvent(const SDL_Event& e, Grid& grid) {
  // 全ての入力を受け取る
  if (e.type == SDL_QUIT) {
    running_ = false;
    return;
  }

  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
      case SDLK_ESCAPE:
        running_ = false;
        break;
      case SDLK_SPACE:
        paused_ = !paused_;
        break;
      case SDLK_r:
        grid.clear();
        break;
      case SDLK_0:
        mode_ = EMPTY;
        break;
      case SDLK_1:
        mode_ = SAND;
        break;
      case SDLK_2:
        mode_ = WATER;
        break;
      case SDLK_3:
        mode_ = WALL;
        break;
      case SDLK_LEFTBRACKET:
        brush_ = max(1, brush_ - 1);
        break;
      case SDLK_RIGHTBRACKET:
        brush_ = min(30, brush_ + 1);
        break;
      default:
        break;
    }
  }

  if (e.type == SDL_MOUSEBUTTONDOWN) {
    if (e.button.button == SDL_BUTTON_LEFT) leftDown_ = true;
    if (e.button.button == SDL_BUTTON_RIGHT) rightDown_ = true;
  }
  if (e.type == SDL_MOUSEBUTTONUP) {
    if (e.button.button == SDL_BUTTON_LEFT) leftDown_ = false;
    if (e.button.button == SDL_BUTTON_RIGHT) rightDown_ = false;
  }
}

void Input::handleMouse(Grid& grid) {
  if (leftDown_) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    int lmx = mx / scale_;
    int lmy = my / scale_;
    grid.paintCircle(lmx, lmy, brush_, mode_);
  }
}

bool Input::running() const { return running_; }

bool Input::paused() const { return paused_; }

int Input::brush() const { return brush_; }

Cell Input::mode() const { return mode_; }
/*

Input::Input(int scale)
    : scale_(scale),
      running_(true),
      paused_(false),
      leftDown_(false),
      rightDown_(false),
      brush_(4),
      mode_(SAND) {}

void Input::handleEvent(const SDL_Event& e, Grid& grid) {
  if (e.type == SDL_QUIT) {
    running_ = false;
    return;
  }

  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
      case SDLK_ESCAPE:
        running_ = false;
        break;
      case SDLK_SPACE:
        paused_ = !paused_;
        break;
      case SDLK_r:
        grid.clear();
        break;
      case SDLK_0:
        mode_ = EMPTY;
        break;
      case SDLK_1:
        mode_ = SAND;
        break;
      case SDLK_2:
        mode_ = WATER;
        break;
      case SDLK_3:
        mode_ = WALL;
        break;
      case SDLK_LEFTBRACKET:
        brush_ = std::max(1, brush_ - 1);
        break;
      case SDLK_RIGHTBRACKET:
        brush_ = std::min(30, brush_ + 1);
        break;
      default:
        break;
    }
  }

  if (e.type == SDL_MOUSEBUTTONDOWN) {
    if (e.button.button == SDL_BUTTON_LEFT) leftDown_ = true;
    if (e.button.button == SDL_BUTTON_RIGHT) rightDown_ = true;
  }
  if (e.type == SDL_MOUSEBUTTONUP) {
    if (e.button.button == SDL_BUTTON_LEFT) leftDown_ = false;
    if (e.button.button == SDL_BUTTON_RIGHT) rightDown_ = false;
  }
}

void Input::handleMouse(Grid& grid) {
  int mx, my;
  SDL_GetMouseState(&mx, &my);
  int lmx = mx / scale_;
  int lmy = my / scale_;

  if (leftDown_) {
    grid.paintCircle(lmx, lmy, brush_, mode_);
  }
}

bool Input::running() const { return running_; }

bool Input::paused() const { return paused_; }

int Input::brush() const { return brush_; }

Cell Input::mode() const { return mode_; }

*/