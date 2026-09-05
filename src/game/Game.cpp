#include "game/Game.hpp"

void Game::reset() {
  elapsed_seconds_ = 0.0f;
  tick_count_ = 0;

  x_ = 640.0f;
  y_ = 360.0f;
  speed_ = 100.0f;
}

void Game::tick(float dt, const Input& input) {
  elapsed_seconds_ += dt;
  ++tick_count_;

  if (input.up) {
    y_  -= speed_ * dt;
  }
  if (input.down) {
    y_ += speed_ * dt;
  }
  if (input.left) {
    x_ -= speed_ * dt;
  }
  if (input.right) {
    x_ += speed_ * dt;
  }
}
