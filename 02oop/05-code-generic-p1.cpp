#include <iostream>
#include <string>

template< typename T >
T sum( T a, T b )
{
  return a + b;
}

template< typename T >
std::string greater( T a, T b )
{
  return "hahaha";
}

int main()
{
  std::cout << sum( 2, 5 ) << std::endl;
  // template deduction:
  // above, we didn't specify the type. but the compiler deduced how to handle the input.
  std::cout << sum<float>( 22, 5 ) << std::endl;
  std::cout << greater( 2, 5) << std::endl;
}