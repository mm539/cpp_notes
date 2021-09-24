#include <iostream>
using namespace std;

/*
   I want this section to cover variadic template FUNCTIONS
   
   In 03-variadics-02-templates.cpp variadic template classes will be covered.

  EXAMPLE 1: BASIC EXAMPLE (adder functions)
  EXAMPLE 2: TBC

  ===============================================

  EXAMPLE 1: BASIC EXAMPLE

  Variadic templates can be used with recursion

  In the following example,
    1. the first function template operates as a base case
    2. the variadic template employs recursion

  From Eli Bendersky's website:
    adder will accept any number of arguments, and will compile properly as long as it can apply the + operator to them. This checking is done by the compiler, at compile time. There's nothing magical about it - it follows C++'s usual template and overload resolution rules.

    typename... Args is called a template parameter pack, and 
    Args... args is called a function parameter pack (Args is, of course, a completely arbitrary name and could be anything else). Variadic templates are written just the way you'd write recursive code - you need a base case (the adder(T v) declaration above) and a general case which "recurses" [1]. The recursion itself happens in the call adder(args...). Note how the general adder is defined - the first argument is peeled off the template parameter pack into type T (and accordingly, argument first). So with each call, the parameter pack gets shorter by one parameter. Eventually, the base case is encountered.


*/
// i. a basic function template
template<typename T>
T adder(T v){
  cout << __PRETTY_FUNCTION__ << endl;
  return v;
}

// ii. a variadic template that uses the function
template<typename T, typename... Args> // "typename... Args" is called a template parameter pack
T adder(T first, Args... args){ // "Args... args" is called a function parameter pack
  cout << __PRETTY_FUNCTION__ << endl;
  return first + adder(args...); // "args..." is called "parameter pack expansion"
}

int main(){
  auto sum = adder(1,2,3,4,5);
  return 0;
}