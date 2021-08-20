#include <iostream>

int main()
{
  int i;
  std::cout << "Enter an int value for i: ";
  std::cin >> i;
  const int j = i * 2; // <--- "=" is initialization
  // j can only be evaluated at RUN time
  // "I promise" not to change it after it is initialized
  // i. running j++ after would produce a compilation error

  constexpr int k = 3;
  // k can be evaluated at COMPILE time
  // i. running k++ would also cause an error
  // ii. constexpr int k = i * 3 would cause an error bc "k" needs to be evaluated at run time because we don't yet have a value for i, but constexpr says that "k" should be evaluated at compile time

  std::cout << "j = " << j << "\n";
  std::cout << "k = " << k << "\n";
}