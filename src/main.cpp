#include "app/App.hpp"

#include <cstdio>

int main(int, char*[]) {
  app::App app;
  if (!app.init("Dungeon Run", 1280, 720)) {
    std::fprintf(stderr, "Failed to initialize app.\n");
    return 1;
  }

  app.run();
  app.shutdown();
  return 0;
}
