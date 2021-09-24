#include <iostream>
using namespace std;
/*
  syntax:
    template <classORtypename identifier> function_declaration;
    template <typename T> myFunction(T a)

  source:
    https://eli.thegreenplace.net/2011/04/22/c-template-syntax-patterns

*/

// i. single type
template <typename myType>
myType GetMax (myType a, myType b){
  return (a > b ? a: b);
}

// ii. two types
template<typename T, typename U> T GetMin(T a, U b){
  return (a < b ? a : b);
}

// iii. non-type template parameter
template <int N>
void printN(){ cout << N << endl;}

// iv. default values
template <typename T = int, int N=20>
void printTN(T a){
  cout << a << endl << N << endl;
}


int main (){
  int x = 3, y = 1;
  long a = 5, b = 10.5;
  GetMax<int>(x, y);
  GetMax<long>(a, b);
  GetMax(x, y); // implicit method is also okay! compiler can infer types

  GetMin<int, long> (x, a);
  GetMin(x, a);

  printN<5>(); // iii. non-type

  printTN(25); // default types
  printTN<>(25);
  printTN<double>(23.3);

  return 0;
}