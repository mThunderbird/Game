#include "game/Game.hpp"
#include "physics/Utils.hpp"
#include "Config.hpp"

#include <cmath>
#include <random>

void Game::reset() {
  elapsed_seconds_ = 0.0f;
  tick_count_ = 0;

  walls_.clear();
  balls_.clear();
  directions_.clear();
  speeds_.clear();

  const Vector2 center{config::kScreenWidth * 0.5f, config::kScreenHeight * 0.5f};
  constexpr float kMargin = 300.0f;
  constexpr float kRadius = 10.0f;
  const float half_w = config::kScreenWidth * 0.5f - kMargin;
  const float half_h = config::kScreenHeight * 0.5f - kMargin;
  const float tilt = 15.0f * std::numbers::pi_v<float> / 180.0f;

  Vector2 corners[4] = {
      Vector2{-half_w, -half_h}.rotate(tilt) + center,
      Vector2{half_w, -half_h}.rotate(tilt) + center,
      Vector2{half_w, half_h}.rotate(tilt) + center,
      Vector2{-half_w, half_h}.rotate(tilt) + center,
  };
  for (int i = 0; i < 4; ++i) {
    walls_.push_back(Line{corners[i], corners[(i + 1) % 4]});
  }

  std::random_device dev;
  std::mt19937 rng(dev());

  std::uniform_real_distribution<float> angle_dist(0.0f, 2.0f * std::numbers::pi_v<float>);
  std::uniform_real_distribution<float> speed_dist(100.0f, 500.0f);
  const float spawn_pad = kRadius * 3.0f;
  std::uniform_real_distribution<float> x_dist(-(half_w - spawn_pad), half_w - spawn_pad);
  std::uniform_real_distribution<float> y_dist(-(half_h - spawn_pad), half_h - spawn_pad);

  for (int i = 0; i < 50; ++i) {
    const Vector2 local{x_dist(rng), y_dist(rng)};
    balls_.push_back(Circle{local.rotate(tilt) + center, kRadius});

    const float angle = angle_dist(rng);
    directions_.push_back(Vector2{std::cos(angle), std::sin(angle)});
    speeds_.push_back(speed_dist(rng));
  }
}

void Game::tick(float dt, const Input& /*input*/) {
  elapsed_seconds_ += dt;
  ++tick_count_;

  for (std::size_t i = 0; i < balls_.size(); ++i) {
    Vector2 old_position = balls_[i].center;
    balls_[i].center = balls_[i].center + directions_[i] * speeds_[i] * dt;

    for (const Line& wall : walls_) {
      if (circleIntersectsLine(balls_[i], wall)) {
        balls_[i].center = old_position;
        directions_[i] = directions_[i].reflect(wall.normal());
        break;
      }
    }
  }

  // Separate overlapping balls and bounce both off the contact normal.
  for (std::size_t i = 0; i < balls_.size(); ++i) {
    for (std::size_t j = i + 1; j < balls_.size(); ++j) {
      Vector2 delta = balls_[j].center - balls_[i].center;
      float dist = delta.length();
      const float min_dist = balls_[i].radius + balls_[j].radius;

      if (dist >= min_dist) {
        continue;
      }

      Vector2 n = (dist < 1e-6f) ? Vector2{1.0f, 0.0f} : (delta * (1.0f / dist));
      const float overlap = min_dist - ((dist < 1e-6f) ? 0.0f : dist);

      balls_[i].center = balls_[i].center - n * (overlap * 0.5f);
      balls_[j].center = balls_[j].center + n * (overlap * 0.5f);

      directions_[i] = directions_[i].reflect(n);
      directions_[j] = directions_[j].reflect(n);
    }
  }
}
