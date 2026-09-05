#include "app/App.hpp"

#include <SDL3/SDL.h>

#include <algorithm>
#include <cstdio>

namespace app {
namespace {

constexpr float kTickRate = 60.0f;
constexpr float kFixedDt = 1.0f / kTickRate;
constexpr float kMaxFrameSeconds = 0.25f;

}  // namespace

App::~App() {
  shutdown();
}

bool App::init(const char* title, int width, int height) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return false;
  }

  if (!renderer_.init(title, width, height)) {
    SDL_Quit();
    return false;
  }

  game_.reset();
  running_ = true;
  return true;
}

void App::run() {
  Uint64 previous = SDL_GetPerformanceCounter();
  const double freq = static_cast<double>(SDL_GetPerformanceFrequency());
  float accumulator = 0.0f;

  while (running_) {
    pump_events();

    const Uint64 now = SDL_GetPerformanceCounter();
    float frame_seconds = static_cast<float>((now - previous) / freq);
    previous = now;
    frame_seconds = std::min(frame_seconds, kMaxFrameSeconds);
    accumulator += frame_seconds;

    while (accumulator >= kFixedDt) {
      tick(kFixedDt);
      accumulator -= kFixedDt;
    }

    draw();
  }
}

void App::shutdown() {
  renderer_.shutdown();
  if (SDL_WasInit(SDL_INIT_VIDEO)) {
    SDL_Quit();
  }
  running_ = false;
}

void App::pump_events() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      running_ = false;
    }
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
      running_ = false;
    }
  }
  const bool* keys = SDL_GetKeyboardState(nullptr);
  input_.up = keys[SDL_SCANCODE_W];
  input_.down = keys[SDL_SCANCODE_S];
  input_.left = keys[SDL_SCANCODE_A];
  input_.right = keys[SDL_SCANCODE_D];
}

void App::tick(float dt) {
  game_.tick(dt, input_);
}

void App::draw() {
  renderer_.draw(game_);
}

}  // namespace app
