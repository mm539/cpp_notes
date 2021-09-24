#include <iostream>
#include <cstring>
//using namespace std;
/*
  CLASS TEMPLATE SPECIALIZATION

  1. EXAMPLE 1: Class Specialization
  2. EXAMPLE 2: Function Specialization
  3. EXAMPLE 3: Structs and Enums

  source(s):
    ...
    https://eli.thegreenplace.net/2011/04/22/c-template-syntax-patterns
*/

// EXAMPLE 1: Class Specialization
template <class T>
class MyContainer {
  T element;
  public:
    MyContainer (T arg) {element = arg;}
	T increase() {return ++element;}
};

template<> // <- HERE is the class template specialization
class MyContainer <char>
{
  
  private:
    char element;
  public:
    MyContainer (char arg) { element = arg; }
    char uppercase()
    {
      if ((element>='a') && (element<='z')) element += 'A'-'a';
      return element;
    }
};

// EXAMPLE 2: Function Specialization
template<typename T> bool less(T aa, T bb) { return aa < bb; }

//specialize
template<> bool less(const char* aa, const char* bb) {
  // string compare = strcmp
  return strcmp(aa, bb) < 0;
}

// EXAMPLE 3: Structs and Enums
enum class Size { small, medium, big };
enum class Vehicle { boat, tricycle, bicycle, car, truck, bus };

template<typename T> struct Traits{};

template<> struct Traits<Size>{
  static std::string Get(int i){
    switch (i)
    {
    case 0:
      return "small";
    case 1:
      return "medium";
    case 2:
      return "big";
    
    default:
      return "unknown";
    }
  }
};

template<> struct Traits<Vehicle>{
  static std::string Get(int i){
    switch (i)
    {
    case 0 : return "boat";
    case 1 : return "tricycle";
    case 2 : return "bicycle";
    case 3 : return "car";
    case 4 : return "truck";
    case 5 : return "bus";
    default:
      return "unknown";
    }
  }
};


/* I don't particulary like this solution. it seems clunky.
wouldn't it be wonderful to be able to do:
  return Color[i]; ?
*/

int main()
{
  MyContainer<int> myint (7);
  MyContainer<char> mychar('j');
  std::cout << myint.increase() << std::endl;
  std::cout << mychar.uppercase() << std::endl;

  std::cout << less<int>(45, 35) << std::endl;
  std::cout << less<char>('a', 'b') << std::endl;

  //std::cout << Traits<Size>::Get(0) << " " << Traits<Vehicle>::Get(1) << std::endl;

  return 0;
}