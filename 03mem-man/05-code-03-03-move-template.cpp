#include <iostream>
using namespace std;


// This class for managing a template-based heap ressource implements move semantics
template <class T>
class MyClass {
  private:
    T *data = nullptr;
  public:
    // constructors
    MyClass() { cout << "calling default constructor for MyClass at " << this << endl; }
    MyClass(T d) { cout << "calling constructor for MyClass at " << this << endl; data = new double{d}; }
    MyClass(T *d) { data = d; cout << "Calling pointer argument constructor for MyClass at " << this << endl;}

    ~MyClass() { // 1 : destructor
        cout << "calling destructor for " << this << endl;
        if (data){ cout << "deleting data " << *data << " at " << data << endl; delete data; }
    }
    
    MyClass(MyClass &&source){ // 4 : move constructor
        cout << "Move constructor\n";
        data = source.data;
        source.data = nullptr;
    }
    MyClass &operator=(MyClass &&source){// 5 : move assignment operator
        cout << "Move assigment\n";
        if (this == &source){ return *this; }

        if (data){ cout << "\tdeleting data " << data << " from " << this << endl;delete data; }
        data = source.data;
        source.data = nullptr;
        return *this;
    }
    MyClass(const MyClass &) = delete; // 2 : copy constructor
    MyClass &operator=(const MyClass &) = delete; // 3 : copy assignment operator
    void Print(){
      if (data != nullptr){
        cout << "Print: " << *data << " at " << data << endl;
      }
      else cout << "error: pointer not valid\n";

    }

};


int main()
{
    /* EXERCISE 3-1: create an instance h1 of class MyClass with data of type 'double' using the regular constructor */
    MyClass<double> h1(5.23);
    h1.Print();
    
    // /* EXERCISE 3-2: create an instance h2 of class MyClass using the move constructor (moving from h1) */
    MyClass<double> h2(0.0);
    h2 = (move(h1));

    /* EXERCISE 3-3: disable copying for class MyClass */
      // Two possible solution:
        //  1. set visibility of MyClass(const MyClass &) and of MyClass &operator=(const MyClass &) to private
        //  2. set them to "=delete"

    // MY OWN EXERCISE - PART 1
    h1.Print();

    // MY OWN EXERCISE - PART 2
    MyClass<double> h3(new double{0.23421});
    h3.Print();

    double d = 10593.153;
    double* pd = &d;
    MyClass<double>h4(pd);
    h4.Print();


    cout << "*****************reached the line before \"return 0\"\n";
    return 0;
}