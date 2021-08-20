#include <iostream>
using std::cout;

class Date
{
 public:
  // constructor
  Date(){} // <--- this is what the default constructor looks like
  Date( int d ); // declare another Date constructor

  // getters AKA Accessors
  int Day() const { return _day; } 
  int Month() const { return _month; }
  int Year() const { return _year; }

  // setters AKA Mutators
  void Day( int day ) { _day = day; }
  void Month( int month )
  {
    if( month < 1 || month > 12 ) _month = 1;
    else _month = month;
  }
  void Year( int year ) { _year = year; }

 private:
  int _day{ 01 };
  int _month{ 01 };
  int _year{ 00 };

};

// here is an example of a scope resolution operator in use
Date::Date( int day )
{
  Day( day );
}

/*
// this code will cause a compile error. 
// ... ‘namespace Date { }’ redeclared as different kind of entity ...
namespace Date
{
  void Year( int year ) { _year = year; }
}
*/

int main()
{
  Date first;

  first.Day(8);


  std::cout << first.Day() << std::endl;
  cout << "this also works!\n";
}