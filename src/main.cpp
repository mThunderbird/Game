#include "app/App.hpp"
#include "Config.hpp"

#include <cstdio>

int main(int, char*[]) {
  app::App app;
  if (!app.init("Dungeon Run", config::kScreenWidth, config::kScreenHeight)) {
    std::fprintf(stderr, "Failed to initialize app.\n");
    return 1;
  }

  app.run();
  app.shutdown();
  return 0;
}
