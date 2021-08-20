#include <iostream>
using namespace std;

void PassByRef(int &val) { cout << "ref -> val: " << val << endl;}
void PassByValue(int val) { cout << "val -> val: " << val << endl; }

int main(){
  // PART 1: lvalues and rvalues
  int i, j, *p;
  i = 42; // i is an lvalue, 42 is an rvalue
  p = new int; *p = i; delete p; // the dereferenced pointer is an lvalue
  ((i < 42) ? i : j) = 23; // the conditional operator returns an lvalue
  i = ((i < 42) ? i : j); // but what about here?


  // 42 = i; //error: the left operand must be an lvalue
  // j * 42 = 23; //error: the left operand must be an lvalue

  int *k = &i; 
  // the address operator & generates an lvalue from an rvalue
  // but when the expression &i appears on the right side, it generates the address of i as an rvalue and assigns it to the lvalue operand on the left
  // this rvalue is assiged to k, which is an lvalue holding the memory location of i

  // PART 2: lvalue references
  int &m = i;
  i++;
  cout << "m: " << m << " " << &m << endl;
  cout << "i: " << i << " " << &i << endl;

  // PART 3: rvalue references
  int a = 1;
  int b = 2;
  int c = a + b;
  int &&d = a + b;
  //PassByRef(a+b);// error: cannot bind non-const lvalue reference of type 'int&' to an rvalue of type 'int'
  PassByRef(d);
  PassByValue(a+b);
  PassByValue(d);

  /*
After creating the integers i and j on the stack, the sum of both is added to a third integer k. Let us examine this simple example a little more closely. In the first and second assignment, i and j are created as lvalues, while 1 and 2 are rvalues, whose value is copied into the memory location of i and j. Then, a third lvalue, k, is created. The sum i+j is created as an rvalue, which holds the result of the addition before being copied into the memory location of k. This is quite a lot of copying and holding of temporary values in memory. With an rvalue reference, this can be done more efficiently.

The expression int &&l creates an rvalue reference, to which the address of the temporary object is assigned, that holds the result of the addition. So instead of first creating the rvalue i+j , then copying it and finally deleting it, we can now hold the temporary object in memory. This is much more efficient than the first approach, even though saving a few bytes of storage in the example might not seem like much at first glance. One of the most important aspects of rvalue references is that they pave the way for move semantics, which is a mighty technique in modern C++ to optimize memory usage and processing speed. Move semantics and rvalue references make it possible to write code that transfers resources such as dynamically allocated memory from one object to another in a very efficient manner and also supports the concept of exclusive ownership, as we will shortly see when discussing smart pointers. In the next section we will take a close look at move semantics and its benefits for memory management.





  */

  return 0;
}