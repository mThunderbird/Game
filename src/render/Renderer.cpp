#include "render/Renderer.hpp"

#include "game/Game.hpp"

#include <SDL3/SDL.h>

#include <cmath>
#include <cstdio>

Renderer::~Renderer() {
  shutdown();
}

bool Renderer::init(const char* title, int width, int height) {
  window_ = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
  if (!window_) {
    std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    return false;
  }

  renderer_ = SDL_CreateRenderer(window_, nullptr);
  if (!renderer_) {
    std::fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(window_);
    window_ = nullptr;
    return false;
  }

  return true;
}

void Renderer::shutdown() {
  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }
  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }
}

void Renderer::draw(const Game& game) {
  // Slow pulse so we can see the fixed tick driving something visible.
  const float t = game.elapsed_seconds();
  const float pulse = 0.5f + 0.5f * std::sin(t * 2.0f);

  const Uint8 r = static_cast<Uint8>(20 + 40 * pulse);
  const Uint8 g = static_cast<Uint8>(40 + 80 * pulse);
  const Uint8 b = static_cast<Uint8>(70 + 100 * pulse);

  SDL_SetRenderDrawColor(renderer_, r, g, b, 255);
  SDL_RenderClear(renderer_);

  // Draw the player's rectangle.
  SDL_FRect rect = {game.x(), game.y(), 32.0f, 32.0f};
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer_, &rect);

  SDL_RenderPresent(renderer_);
}
