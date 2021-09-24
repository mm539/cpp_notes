#include <iostream>


/*
  "Partial specialization seems to refer to two slightly different syntaxes."

  Note: The following partial specializations are done for classes, but partial specializations can also be done for functions.

  1. EXAMPLE 1: Specializing for some modifier of a type
  2. EXAMPLE 2: Specializing by some parameters 
    - "Another face of partial specialization is taking a template with more than one parameter and specializing it by some of the parameters."

  Source:
    https://eli.thegreenplace.net/2011/04/22/c-template-syntax-patterns
*/

// EXAMPLE 1: Specializing for some modifier of a type
template<typename T>
class Array{};

template<typename T>
class Array<T*>{}; // here is the specialization for pointer types

// EXAMPLE 2: Specializing by some parameters 
template<typename T, typename Allocator>
class vector{};

template<typename Allocator>
class vector<bool, Allocator>{}; // specialization for bool

int main(){
  return 0;
}