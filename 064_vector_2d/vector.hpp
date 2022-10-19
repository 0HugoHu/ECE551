/* write your class interface in this file
   write function definitions only if they are very short
 */

class Vector2D {
 private:
  double x;
  double y;

 public:
  Vector2D() {
    x = 0.0;
    y = 0.0;
  }

  Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
  }

  void initVector(double x, double y) {
    this->x = x;
    this->y = y;
  }
  double getMagnitude() const;
  Vector2D operator+(const Vector2D & r) const;
  Vector2D & operator+=(const Vector2D & r);
  double dot(const Vector2D & r) const;
  void print() const;
};
