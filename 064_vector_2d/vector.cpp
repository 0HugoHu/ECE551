#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

double Vector2D::getMagnitude() const {
  return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::operator+(const Vector2D & r) const {
  Vector2D res(x + r.x, y + r.y);
  return res;
}

Vector2D & Vector2D::operator+=(const Vector2D & r) {
  x += r.x;
  y += r.y;
  return *this;
}

double Vector2D::dot(const Vector2D & r) const {
  return x * r.x + y * r.y;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
