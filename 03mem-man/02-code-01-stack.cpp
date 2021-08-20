#include <iostream>
#include <string>
#include <vector>

/* 
The purpose of this exercise is to witness the expansion and contraction of the stack.
*/

class MyClass
{
  public:
    MyClass(){_value = 5;}
    int _value;
};

void myFunc(){int a = 5;printf( "myFunc: %p \n", &a );}
void myFuncVal( int b ){printf( "myFuncVal: %p \n", &b );}
void myFuncVal2( int b ){printf( "myFuncVal2: %p \n", &b );}
void myFuncRef( int &c ){printf( "myFuncRef: %p \n", &c );}

int main()
{
  int i = 1;
  printf( "1: %p \n", &i );

  int j = 1;
  printf( "2: %p \n", &j );

  myFunc();
  myFuncVal( j );
  myFuncVal2( i );
  myFuncVal( i );

  myFuncRef( j );

  int k = 2;
  printf( "3: %p \n", &k );

  std::string a = "h"; // it doesn't seem to matter how long this variable is. &var just shows the address of the variable. gosh i really don't get this.
  printf( "string 1: %p \n", &a );

  std::string b = "h";
  printf( "string 2: %p \n", &b );

  std::string c = "h";
  printf( "string 2: %p \n", &c );

  MyClass myclass;
  printf( "class: %p \n", &myclass );

  return 0;
}