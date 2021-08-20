#include <iostream>
#include <stdexcept>
using std::cout;

/*
thoughts:
  i. using initializer lists is good practice.

  ii. combining initializer lists with a Validate function (that will throw an error if the data used to instantiate an object is invalid) in the constructor is a good strategy

*/

// 1. this definition of class Date does NOT have an initializer list
// however, one of the constructors is defined with an initializer list. see point #4.
class Date
{
 public:
  Date(){}
  Date( int d, int month );
  void Validate();

  // getters AKA Accessors
  int Day() const { return _day; } 
  int Month() { return _month; }
  int Year() { return _year; } // single line function definitions become inline functions! --> good!

  // setters AKA Mutators
  void setDay( int day );
  void setMonth( int month )
  {
    _month = ( month < 1 || month > 12 ) ? _month = 1 : month;
  }
  void setYear( int year ) { _year = year; }

 private:
  // first, the member variables are initialized to the values here
  // however, if the constructor has an initializer list, the values of the initializer list overwrite the ones here.
  int _day{ 01 };
  int _month{ 01 };
  int _year{ 00 };

};

void Date::setDay(int day)
{
  _day = day;
  Validate();
}

void Date::Validate() {
    if (_day < 1 || _day > 31)
      throw std::invalid_argument("negative dimension");
}

// 2. Birthday has an initializer list
class Birthday
{
 public:
  Birthday( int d, int m, int y ): _day( d ), _month( m ), _year( y ) {}
  // i. this is an initializer list
  // ii. does the constructor need to be defined here?
  // iii. we need to use an initializer list to initialize const member variables
  int Day() const { return _day; } 
  int Month() const { return _month; }
  int Year() const { return _year; }

 private:
  int const _day;
  int const _month;
  int const _year;
};

// 3. here is one way to combine invariants with initializer lists: you can make an external function
Birthday makeBirthday( int d, int m, int y )
{
  // you could put invariant logic in here.
  // "enforcing code"
  Birthday bday = Birthday( d, m, y );
  return bday;
}

// 4. initializer lists bypass the conditions set by any invariant logic located in mutator functions
Date::Date( int day, int month )
: _day( day ), _month( month ) // <--- initializer list
{
  // 5. however, we can have special member functions that check that the members have valid data
  Validate();
}


int main()
{
  Date first( 1, 13 );
  Birthday myBirthday = makeBirthday( 1, 1, 2000 );
  // Birthday testBday = Birthday(); // what error is produced here?

  std::cout << first.Month() << std::endl;
}