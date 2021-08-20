#include <iostream>

/* EXAMPLE #1 */
class Book
{
 public:
  virtual void fall() const { std::cout << a << std::endl; }
  void open() const { std::cout << "the book is empty" << std::endl; }
 private:
  int a{5};
};

class ScienceBook: public Book {};

class MathBook: public Book
{
 public:
  void open() const { std::cout << "the book has a lot of numbers" << std::endl; }
  void fall() const
  {
    std::cout << "thmpf\n";
  }
};

/* EXAMPLE #2 */
class Animal
{
 public:
  virtual void talk() const = 0;
};

class Human: public Animal
{
 public:
  void talk() const
  {
    std::cout << "Hi!\n";
  }
};

/* Example #3 */
// Example solution for Shape inheritance
#include <assert.h>
#include <cmath>
#include <iostream>

static float pi{3.14159};

class Shape
{
public:
    virtual float Area() const = 0;
    virtual float Perimeter() const = 0;
};

class Rectangle: Shape
{
public:
    Rectangle(float w, float h): w_(w), h_(h){}
    // override is optional
    // note: "override const" would NOT work. why not? what's the difference?
    float Area() const override { return w_ * h_; }
    float Perimeter() const { return 2 * w_ + 2 * h_; }
private:
    float w_, h_;
};

class Circle: Shape
{
public:
    Circle(float r): r_(r){}
    float Area() const { return pi * pow(r_, 2); }
    float Perimeter() const { return 2 * pi * r_; }
private:
    float r_;
};


int main()
{
  Book book;
  book.fall();
  book.open();
  ScienceBook scibook;
  scibook.fall();
  MathBook mathbook;
  mathbook.fall();
  mathbook.open();
  // book can be instantiated because although its fall function is a virtual function it is not a virtual function.

  //Animal animal; // Animal is an abstract class bc it has a pure virtual function
  Human human;
  human.talk();


  double epsilon = 0.1; // useful for floating point equality

  // Test circle
  Circle circle(12.31);
  assert(abs(circle.Perimeter() - 77.35) < epsilon);
  assert(abs(circle.Area() - 476.06) < epsilon);

  // Test rectangle
  Rectangle rectangle(10, 6);
  assert(rectangle.Perimeter() == 32);
  assert(rectangle.Area() == 60);
}