#pragma once

#include "Input.hpp"

// Simulation state only — no SDL, no rendering.
// Fixed-timestep ticks advance this; render reads it.
class Game {
public:
  void reset();
  void tick(float dt, const Input& input);

  // Phase 0: just prove the clock is alive.
  float elapsed_seconds() const { return elapsed_seconds_; }
  unsigned tick_count() const { return tick_count_; }



  // Getters for player position
  float x() const { return x_; }
  float y() const { return y_; }
  float speed() const { return speed_; }

private:
  float elapsed_seconds_ = 0.0f;
  unsigned tick_count_ = 0;

  // Primitive player
  float x_ = 0.0f;
  float y_ = 0.0f;
  float speed_ = 100.0f;
};
