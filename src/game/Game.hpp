#pragma once

#include "Input.hpp"
#include <vector>
#include "physics/Utils.hpp"

// Simulation state only — no SDL, no rendering.
// Fixed-timestep ticks advance this; render reads it.
class Game {
public:
  void reset();
  void tick(float dt, const Input& input);

  // Phase 0: just prove the clock is alive.
  float elapsed_seconds() const { return elapsed_seconds_; }
  unsigned tick_count() const { return tick_count_; }

  const std::vector<Line>& walls() const { return walls_; }
  const std::vector<Circle>& balls() const { return balls_; }
  const std::vector<Vector2>& directions() const { return directions_; }
  const std::vector<float>& speeds() const { return speeds_; }

private:
  float elapsed_seconds_ = 0.0f;
  unsigned tick_count_ = 0;

  std::vector<Line> walls_;
  std::vector<Circle> balls_;
  std::vector<Vector2> directions_;
  std::vector<float> speeds_;
};
