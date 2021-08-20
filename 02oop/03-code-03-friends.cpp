#include <iostream>
#include <assert.h>

/* 

Sidenote:

There is something here, not directly related to friends, that tripped me up for a sec.

If class A uses class B in its definition (either by storing it as a member value or just extracting a value from it), then class B MUST BE defined first otherwise there will be a compilation error.

*/

/* EXAMPLE #1 */
class Heart
{
 public:
  int rate { 80 };
  friend class Human;
};

class Human
{
 public:
  Heart heart;
  void exercise() { heart.rate = 150; }
  int getHeartRate() { return heart.rate; }
};

/* EXAMPLE #2 */

class Square {
public:
    Square(int side): side_(side) {}
private:
    int side_;
    friend class Rectangle;
};

class Rectangle {
public:
    Rectangle(Square& square);
    int Area() { return width_ * height_; }
private:
    int width_;
    int height_;
};

Rectangle::Rectangle(Square& square) : width_(square.side_), height_(square.side_){}

int main()
{
  Human human;
  std::cout << human.getHeartRate() << std::endl;


  Square square(4);
  Rectangle rectangle(square);
  assert(rectangle.Area() == 16); 
}
