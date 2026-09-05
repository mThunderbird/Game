#pragma once

class Game;

// Presentation only — draws simulation state, never mutates game rules.
class Renderer {
public:
  Renderer() = default;
  ~Renderer();

  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;

  bool init(const char* title, int width, int height);
  void shutdown();
  void draw(const Game& game);

private:
  struct SDL_Window* window_ = nullptr;
  struct SDL_Renderer* renderer_ = nullptr;
};
