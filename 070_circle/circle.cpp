#include "circle.hpp"
#include <cmath>
#include <algorithm>

#define PI 3.14159265

void Circle::move(double dx, double dy) {
  c.move(dx, dy);
}


double Circle::intersectionArea(const Circle & c2) {
  double r1 = this->r;
  double r2 = c2.r;
  double d = this->c.distanceFrom(c2.c);

  // no intersection
  if (d > (r1 + r2)) {
    return 0.0;
  }
  // small circle inside large circle
  if (d <= std::abs(r1 - r2)) {
    return PI * std::min(r1, r2) * std::min(r1, r2);
  }

  double alpha = acos((r1 * r1 - r2 * r2 + d * d) / (2 * d * r1));
  double beta = acos((r2 * r2 - r1 * r1 + d * d) / (2 * d * r2));

  double intersection = alpha * r1 * r1 + beta * r2 * r2 - d * r1 * sin(alpha);

  return intersection;
}