#include <iostream>

struct Rectangle
{
  float _length;
  float _width;
};

struct Square
{
  float _a{ 5 };
};

class Date // struct Date
// according to the cpp guidelines, classes should be used when there are invariants. however, this code appears to work fine whenever compiled and run.
// ???
{
 public:
  // getters AKA Accessors
  int Day() const { return _day; }
  // we can also add "const." const promises not to modify the Date object
  // this is not required, but is good defensive programming
  int Month() { return _month; }
  int Year() { return _year; }

  // setters AKA Mutators
  void Day( int day ) { _day = day; }
  void Month( int month )
  {
    // this if-else is called an "invariant." it is a logical condition that restricts the definition of variables
    if( month < 1 || month > 12 ) _month = 1;
    else _month = month;
  }
  void Year( int year ) { _year = year; }

 // we can use access modifiers ( public and private ) to control how the member variables are defined
 private:
  int _day{ 01 };
  int _month{ 01 };
  int _year{ 00 };

};

int main()
{
  Rectangle rect;
  Square square;
  Date first;

  rect._length = 2;
  first.Day(8);

  std::cout << rect._width << std::endl; // some random number bc value was not defined
  std::cout << square._a << std::endl;
  std::cout << first.Day() << std::endl;
}