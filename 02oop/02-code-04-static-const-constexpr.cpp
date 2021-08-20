#include <iostream>

/*
static -> belongs to an entire class
  keyword cannot be put outside class definition.
const -> evaluated at run time
constexpr -> must be evaluated at compile time
*/
class MyClassK
{
 public:
 private:
  static float const _k;
};

float const MyClassK::_k = 2;

class MyClassP
{
 private:
  static float constexpr _p { 2.2 };
};

/*
class MyClassM
{
 private:
  static constexpr float _m; <--- this doesn't work because constexpr vars must have initializer.
};


*/

int main()
{

}