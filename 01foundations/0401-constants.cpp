#include <iostream>
#include <vector>
using namespace std;

// CONST # 3
// const is often used in function signatures to guard against accidentally changed a variable
int sum(const vector<int>& v)
{
  int sum = 0;
  for (int i: v)
    sum += i;
  return sum;
}

int main()
{
  // CONST #1
  int i;
  cout << "enter an integer value for i: ", cin >> i;
  
  const int j = i * 2; 
  // j can only be evaluated at run time
  // "but i promise not to change it after it is initialized"
  cout << "i: " << i << endl;
  cout << "j : " << j << endl;


  try
  {
    //j++;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  


  // CONSTEXPR  # 1
  constexpr int k = 3; 
  // k is evaluated at compile time

  // CONST #2
  // j++; // this line will cause a compile error

  // CONSTEXPR # 2
  // k++; this line will also cause a compile error

  // CONSTEXPR #3
  //constexpr int m = i * 2;
  // because i can only be evaluated at run time, the above line will cause a compile error

  // CONST # 3 - SEE FUNCTION DEFINED ABOVE
  vector<int>v {1,2,3,4};
  cout << sum(v) << endl;
}