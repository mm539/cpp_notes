#include <iostream>
#include <string>

class Human {};
class Dog {};

std::string hello(){ std::cout << "hello!\n"; }
std::string hello( Human human ){ std::cout << "hello human!\n"; }
std::string hello( Dog dog ){ std::cout << "hello dog!\n"; }

int main()
{
  hello( Dog() );
  hello( Human() );
  hello();
}