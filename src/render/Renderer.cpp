#include "render/Renderer.hpp"

#include "game/Game.hpp"

#include <SDL3/SDL.h>

#include <cmath>
#include <cstdio>

namespace {

void drawFilledCircle(SDL_Renderer* renderer, float cx, float cy, float radius) {
  constexpr int kSegments = 24;
  SDL_Vertex verts[kSegments + 2];
  const SDL_FColor color{1.0f, 1.0f, 1.0f, 1.0f};

  verts[0].position = {cx, cy};
  verts[0].color = color;
  verts[0].tex_coord = {0.0f, 0.0f};

  for (int i = 0; i <= kSegments; ++i) {
    const float angle =
        (static_cast<float>(i) / static_cast<float>(kSegments)) * (2.0f * SDL_PI_F);
    verts[i + 1].position = {cx + std::cos(angle) * radius,
                             cy + std::sin(angle) * radius};
    verts[i + 1].color = color;
    verts[i + 1].tex_coord = {0.0f, 0.0f};
  }

  int indices[kSegments * 3];
  for (int i = 0; i < kSegments; ++i) {
    indices[i * 3 + 0] = 0;
    indices[i * 3 + 1] = i + 1;
    indices[i * 3 + 2] = i + 2;
  }

  SDL_RenderGeometry(renderer, nullptr, verts, kSegments + 2, indices,
                     kSegments * 3);
}

}  // namespace

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
  SDL_SetRenderDrawColor(renderer_, 20, 40, 70, 255);
  SDL_RenderClear(renderer_);

  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  for (const auto& wall : game.walls()) {
    SDL_RenderLine(renderer_, wall.point1.x, wall.point1.y, wall.point2.x,
                   wall.point2.y);
  }

  for (const auto& ball : game.balls()) {
    drawFilledCircle(renderer_, ball.center.x, ball.center.y, ball.radius);
  }

  SDL_RenderPresent(renderer_);
}
