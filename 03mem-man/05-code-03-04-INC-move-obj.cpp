#include <iostream>
#include <memory>
using namespace std;

/*
  I need to answer the follow questions:
  what happens when calling move on a:
    i. stack object
    ii. heap object via its handle
    iii. smart pointer

  WHAT I DID:

  ANSWER:
*/

class MyClass{
  public:
    int* _hMember = nullptr;
    int _sMember;
    unique_ptr<int> _uMember;
    MyClass(){
      cout << "default constructor\n";
      _hMember = new int(5);
      _sMember = 100;
      _uMember.reset(new int(25));
    }
    ~MyClass(){ // 1. destructor
      if (_hMember != nullptr) { delete _hMember; _hMember = nullptr; }
    }
    MyClass(MyClass& source){ // 2. copy constructor
      cout << "Copy constructor\n";

      _sMember = source._sMember;
      _hMember = new int;
      if (source._hMember != nullptr) *_hMember = *source._hMember;
      _uMember.reset( new int( *source._uMember ) );
    }
    MyClass& operator=(MyClass& source){ // 3. copy assignment
      cout << "Copy assignment\n";
      if (this == &source){ return *this; }

      _sMember = source._sMember;
      if (_hMember != nullptr) { delete _hMember; _hMember = nullptr; _hMember = new int; }
      *_hMember = *source._hMember;
      _uMember.reset( new int(*source._uMember) );

      return *this;
    }
    MyClass(MyClass&& source){ // 4. move constructor
      cout << "Move constructor\n";

      _sMember = source._sMember;
      if (source._hMember != nullptr) {
        _hMember = new int;
        *_hMember = *source._hMember;
        delete source._hMember;
        source._hMember = nullptr;
      } 
      _uMember.swap(source._uMember);  // reset( new int( *source._uMember ) );
    }
    MyClass& operator=(MyClass&& source){ // 5. move assignment 
      cout << "Move assignment\n";
      if (this == &source) return *this;

      _sMember = source._sMember;

      if (_hMember != nullptr){ delete _hMember; _hMember = nullptr; }
      if (source._hMember != nullptr){
        _hMember = new int;
        *_hMember = *source._hMember;
        delete source._hMember;
        source._hMember = nullptr;
      }

      _uMember.reset();
      _uMember.swap(source._uMember);

      return *this;
    }
};

int main(){
  // Part 1: MODIFYING PUBLIC MEMBERS WITH MOVE SEMANTICS
  MyClass c1;
  MyClass c2;

  c1._sMember = 500;
  c2._sMember = move(c1._sMember);

  cout << c1._sMember << " " << c2._sMember << endl;

  //
  delete c1._hMember;
  c1._hMember = new int(1);
  c2._hMember = move(c1._hMember);
  cout << *c1._hMember << " " << *c2._hMember << endl;

  //
  c1._uMember.reset(new int(50));
  c2._uMember = move(c1._uMember);
  if (c1._uMember) cout << *c1._uMember; else cout << "empty";
  cout << " " << *c2._uMember << endl;

  // only the unique pointer was destroyed
  {
    c1._sMember = 99;
    c2._sMember = 3;

    cout << "\n";
  }

  // PART 2: MOVING OBJECTS
  MyClass c3(move(c2));
  cout << c3._sMember << endl;

  c3 = move(c1);
  cout << c3._sMember << endl;

  return 0;
}