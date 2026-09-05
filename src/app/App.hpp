#pragma once

#include "game/Game.hpp"
#include "render/Renderer.hpp"

namespace app {

// Owns the SDL window/lifecycle and the fixed-timestep loop.
// Keeps simulation (game) separate from presentation (render).
class App {
public:
  App() = default;
  ~App();

  App(const App&) = delete;
  App& operator=(const App&) = delete;

  bool init(const char* title, int width, int height);
  void run();
  void shutdown();

private:
  void pump_events();
  void tick(float dt);
  void draw();

  bool running_ = false;
  Game game_{};
  Renderer renderer_{};
  Input input_{};
};

}  // namespace app
