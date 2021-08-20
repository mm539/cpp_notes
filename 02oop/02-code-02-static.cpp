#include <cassert>
#include <cmath>
#include <stdexcept>
#include <iostream>

/*
  Static member variables:

  1. specify a member variable as static, NOT constexpr
    i. declare it within its class
    ii. define && initialized it within the GLOBAL scope*

  2. specify a member variable as static and constexpr
    - it should be declared and defined within the class definition

  *Memory is allocated for static variables immediately when the program begins, at the same time any global variables are initialized.
*/


// PART 1: constexpr
class Sphere {
  public:
    Sphere(int radius) {Radius(radius); }

    int Radius() { return radius_; }
    int Volume() { return volume_; }
    void Radius(int radius){
      if(radius <=0) throw std::invalid_argument("radius must be positive");
      radius_ = radius;
      UpdateVolume();
    }
    static const double pi;
  private:
    static float constexpr pi_{3.14159};
    // static must be specified within the class definition
    //   - Define only if the var is of type constexpr
    //   - OTHERWISE, define in the global scope
    int radius_;
    float volume_;
    void UpdateVolume(){
      volume_ = pi_ * 4 / 3 * pow(radius_, 3);
    }
};

//const double Sphere::pi{3.14}; 
// pi should be defined/initialized in the global scope
// if the code attempts to retrieve the value of Sphere::pi, then the code won't compile
// however, if there is no attempt, then the code will compile
// TRICKY!

// PART 2: simple example
class Foo
{
  public:
    Foo(){ count_++; }
    static int count_;
    int Count(){ return count_; }
    
};

int Foo::count_{0};

int main(){
  // PART 1
  Sphere sphere(3);
  assert(sphere.Radius() == 3);
  assert(abs(sphere.Volume() - 113.1) < 1);

  // std::cout << "the value of pi is " << sphere.getPi() << std::endl;
  // if this line is uncommented, the code will not compile

  // PART 2
  Foo foo1{};
  Foo foo2;
  // Foo foo3(); // this one doesn't increment count
  // also, the members are not accessible. why not?
  std::cout << Foo::count_ << std::endl;
  std::cout << foo1.count_ << std::endl;
  std::cout << foo2.Count() << std::endl;

}