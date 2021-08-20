#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#define pi 3.14159
using std::cout;
using std::string;
using std::vector;

/* EXAMPLE #1 */

class Wheel {
  public:
    Wheel() : diameter(50) {}
    float diameter;
};

class Car {
  public:
    Car() : wheels(4, Wheel()){}
    vector<Wheel> wheels;
};

/* EXAMPLE #2 */

class LineSegment
{
 public:
  LineSegment( float length ) : _length( length ) {}
  float _length;
};

class Circle
{
 public:
  Circle( LineSegment& radius ) : _radius( radius ) {}
  float Area()
  {
    return pi * _radius._length * _radius._length;
  }
  LineSegment& _radius;
};


int main() {
  Car car;
  cout << car.wheels.size() << "\n";

  LineSegment radius {3};
  Circle circle(radius);
  assert(int(circle.Area()) == 28);

}