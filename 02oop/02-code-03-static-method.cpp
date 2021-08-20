#include <cassert>
#include <cmath>
#include <stdexcept>

class Sphere {
 public:
  static float Volume(int radius);/*
  // 1. can be defined inside the class
  {
    if (radius <= 0) throw std::invalid_argument("radius must be positive");

    return pi_ * 4 / 3 * pow(radius, 3);
  }*/

 private:
  static float constexpr pi_{3.14159};
};

// 2. or outside the class
float Sphere::Volume(int radius)
{
  if (radius < 1 ) throw std::invalid_argument("radius must be 1 or greater");
  return pi_ * 4 / 3 * pow(radius, 3);
}

// Test
int main(void) {
  assert(abs(Sphere::Volume(5) - 523.6) < 1);
}