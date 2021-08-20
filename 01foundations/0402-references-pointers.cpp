#include <iostream>
#include <string>
using std::cout;

void AddOnePointer(int* j)
{
    // Dereference the pointer and increment the int being pointed to.
    (*j)++;
}

void AddOneReference(int& j)
{
     // Increment the referenced int and return the
     // address of j.
     j++;
}

void AddOne(int k)
{
  k++;
}


int main() {
    // 1. USE FUNCTION THAT TAKES A POINTER / MEMORY ADDRESS
    int i = 1;
    cout << "The value of i is: " << i << "\n";
    
    int& refi = i; // what is the type of "refi"?
    int* pig = &i; // Declare a pointer to i:
    AddOnePointer(pig);
    AddOnePointer(&i);
    AddOnePointer(&refi);
    cout << "The value of i is now: " << i << "\n";

    cout << "typeid of pig: " << typeid(pig).name() << "\n";
    cout << "typeid of refi: " << typeid(refi).name() << "\n";


    // -----------------------------------------
    // 2. USE FUNCTION THAT PASSES A REFERENCE
    int j = 1;
    cout << "The value of j is: " << j << "\n";

    // Declare a pointer and initialize to the value
    // returned by AddOne:
    AddOneReference(j);
    cout << "The value of i is now: " << j << "\n";
    

    // 3. USE STANDARD FUNCTION TO PASS-BY-VALUE
    int k = 1;
    cout << "The value of k is: " << k << "\n";
    AddOne(k);
    cout << "The value of k is: " << k << "\n";

}