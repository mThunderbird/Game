#pragma once

#include <cmath>
#include <numbers>
#include <algorithm>

struct Vector2 {
    float x;
    float y;
    
    Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
    Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
    Vector2 operator*(const float scalar) const { return  Vector2(x * scalar, y * scalar); }
    bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }

    float length() const { return std::sqrt(x * x + y * y); }
    Vector2 normalized() const { return Vector2(x / length(), y / length()); }
    Vector2 rotate(float radians) const { 
        float cos = std::cos(radians);
        float sin = std::sin(radians);
        return Vector2(x * cos - y * sin, x * sin + y * cos); 
    }

    Vector2 reflect(const Vector2& normal) const { 
        Vector2 v = this->normalized();
        Vector2 n = normal.normalized();
        float dot = v.x * n.x + v.y * n.y;
        return v - n * 2.f * dot;
    }

};

inline float dot(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }
inline float distance(const Vector2& a, const Vector2& b) { return (a - b).length(); }

struct Circle {
    Vector2 center;
    float radius;

};

struct Line {
    Vector2 point1;
    Vector2 point2;

    float length() const { return distance(point1, point2); }
    Vector2 normal() const { return (point2 - point1).rotate(std::numbers::pi_v<float> / 2.0f); }
};

struct Rect {
    // Top left corner
    Vector2 pos;
    Vector2 size;
};


inline bool circleIntersectsLine(const Circle& circle, const Line& line) {

    if (line.point1 == line.point2) {
        return distance(circle.center, line.point1) <= circle.radius;
    }

    Vector2 AB = line.point2 - line.point1;
    Vector2 AC = circle.center - line.point1;
    float t = std::clamp(dot(AB, AC) / dot(AB, AB), 0.f, 1.f);
    Vector2 closest = line.point1 + AB * t;
    return distance(circle.center, closest) <= circle.radius;
}

inline bool circleIntersectsCircle(const Circle& a, const Circle& b) {
    return distance(a.center, b.center) <= a.radius + b.radius;
}