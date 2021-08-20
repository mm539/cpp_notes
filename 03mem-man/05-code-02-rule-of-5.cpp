#include <stdlib.h>
#include <iostream>
/*
  deep copy strat

  note: for all constructors, what are the values of the member variables of the new copies?

    Answer: Whatever values they are initialized to in the class definition. Compare:
      int _size;
      int _size{5};
*/
class MyMovableClass
{
private:
    int _size;
    int *_data;

public:
    MyMovableClass(size_t size) // constructor
    {
        _size = size;
        _data = new int[_size];
        std::cout << "CREATING instance of MyMovableClass at " << this << " allocated with size = " << _size*sizeof(int)  << " bytes" << std::endl;
    }

    ~MyMovableClass() // 1 : destructor
    {
        std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
        delete[] _data;
    }
    MyMovableClass(const MyMovableClass &source) // 2 : copy constructor
    {
        _size = source._size;
        _data = new int[_size];
        *_data = *source._data;
        std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
    }

    MyMovableClass& operator=(const MyMovableClass &source) // 3 : copy assignment constructor
    {
        std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
        if (this == &source){ return *this; }
        delete[] _data;
        _size = source._size;
        _data = new int[_size];
        *_data = *source._data;
        return *this;
    }
    MyMovableClass(MyMovableClass &&source) // 4. move constructor
    {
      std::cout << "MOVING (c’tor) instance " << &source << " to instance " << this << std::endl;
      _data = source._data;
      _size = source._size;
      source._data = nullptr;
      source._size = 0;
    }
    MyMovableClass& operator=(MyMovableClass &&source) // 5. move assignment operator
    {
      std::cout << "MOVING (assign) instance " << &source << " to " << this << std::endl;
      if (this == &source) { return *this; }
      delete[] _data;

      _data = source._data;
      _size = source._size;
      source._size = 0;
      source._data = nullptr;
      return *this;
    }
};

MyMovableClass createObject(int size){
  MyMovableClass obj(size); // regular constructor
  // MyMovableClass obj = MyMovableClass(size); 
  // move constructor; MyMovableClass(size) returns an rvalue
  return obj;
}

int main()
{
    // compare the output of this code when running:
    //  -std=c++11 -fno-elide-constructors
    //    vs
    //  -std=c++17
    {
      MyMovableClass obj1(10); // regular constructor
      MyMovableClass obj2(obj1); // copy constructor
      obj2 = obj1; // copy assignment operator

      MyMovableClass obj3 = obj1; 
      // here, copy assignment operator is NOT called
      // the copy constructor is called
    }

    std::cout << "\n\n";
    {
      MyMovableClass obj4 = createObject(10);
      MyMovableClass obj5(createObject(12));
    }

    std::cout << "\n\n";
    MyMovableClass obj1(100); // constructor
    obj1 = MyMovableClass(200); // constructor AND move assignment operator
    MyMovableClass obj2 = MyMovableClass(300); // (constructor AND move constructor) OR normal  constructor
    // output depends on compile standard and arguments used
    return 0;
}

/*
  SELF QUIZ: WHICH CONSTRUCTORS WILL THE FOLLOWING CODE CALL

  MyMovableClass obj1(10); 
  MyMovableClass obj2(obj1);
  obj2 = obj1; 

  MyMovableClass obj3 = obj1; 

  MyMovableClass obj4 = createObject(10);
  MyMovableClass obj5(createObject(12));

  MyMovableClass obj1(100); 
  obj1 = MyMovableClass(200);
  MyMovableClass obj2 = MyMovableClass(300);
*/