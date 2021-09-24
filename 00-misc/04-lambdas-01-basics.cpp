#include <iostream>
class MyClass {
  private:
    int i_;
  public:
    MyClass(int i): i_(i){}
    void AddOne(){ i_++; }
    int GetVal(){ return i_; }
};

int main()
{
  // EXAMPLE 1: CAPTURE LIST
  std::cout << "***Example 1: Capture Lists***\n";

  int id = 0;
  int initial_id = id;
  // auto f0 = []() { std::cout << "ID = " << id << std::endl; }; // ERROR: id cannot be accessed

  auto f1 = [id]() { std::cout << "f1: capture-by-value: id = " << id << std::endl; }; // 'id' is captured by value, but can it be modified? see f3

  auto f2 = [&id]() { std::cout << "f2: capture-by-reference: id = " << ++id << std::endl; }; // 'id' is captured by reference

  // auto f3 = [id]() { std::cout << "ID = " << ++id << std::endl; }; // ERROR: 'id' may not be modified

  auto f4 = [id]() mutable { std::cout << "f4: capture-by-value && with keyword mutable: id = " << ++id << std::endl; }; // a local, compile-time version of 'id' may be modified
  
  f1();
  f2();
  f4();
  
  std::cout << "id changed from " <<  initial_id << " to " << id << std::endl;

  // EXAMPLE 2: Runtime vs Compile-time
  std::cout << "\n***Example 2: Runtime vs Compile-time***\n";
  int b = 0;

  auto f8 = [&b]() { std::cout << "a) capture-by-reference, b = " << b << std::endl; };
  auto f9 = [b]() {std::cout << "b) capture-by-value, b = " << b << std::endl; };

  std::cout << "initial value of b: " << b++ << "\nb++\n";
  f8();
  f9();

  // EXAMPE 3: mutable
  // 1. from cplusplus.com:
  //     mutable is a lambda-declarator that removes const qualification from parameters captured by copy 
  // 2. adding mutable to a capture-by-value capture list creates a "hidden," persistent scope that contains the variables
  std::cout << "\n***Example 3: mutable***\n";

  MyClass obj1(1);
  std::cout << std::endl;
  // EXPERIMENT WITH THESE DIFFERENT SIGNATURES
  auto f5 = [obj1]() mutable { // <- INTERESTING
  //auto f5 = [&obj1]() mutable {
  //auto f5 = [&obj1]() {
    std::cout << "\n\tCalling f5:";
    std::cout << "\n\tinitial obj1.GetVal() = " << obj1.GetVal();
    std::cout << "\n\tCalling AddOne() ... ";
    obj1.AddOne();
    std::cout << "\n\tobj1.GetVal() = " << obj1.GetVal() << std::endl;
  };

  for (int j = 0; j < 2; j++){
    std::cout << "for loop, iteration: " << j;
    f5();

    std::cout << "  exit f5: obj1.GetVal() = " << obj1.GetVal() << "\n\n"; 
  }

  for (int j = 0; j < 2; j++){
    std::cout << "for loop, iteration: " << j;
    f5();

    std::cout << "  exit f5: obj1.GetVal() = " << obj1.GetVal() << "\n\n"; 
  }

  // EXAMPLE 4: USING THE PARAMETER LIST
  std::cout << "\n***Example 4: Parameter List***\n";
  int j = 0;

  auto f6 = [](int p) {
    std::cout << "Pass-by-value variable value = " << ++p << std::endl;
  };
  auto f7 = [](int& p){
    std::cout << "Pass-by-reference variable value = " << ++p << std::endl;
  };

  f6(j);
  std::cout << "value of j in main scope: " << j <<"\n\n";
  f7(j);
  std::cout << "value of j in main scope: " << j << std::endl;


  return 0;
}