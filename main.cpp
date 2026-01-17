#include "src/App.h"

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  const int W = 1280;
  const int H = 720;
  const int SCALE = 1;

  App app(W, H, SCALE);
  if (!app.init()) return 1;
  app.run();
  return 0;
}
