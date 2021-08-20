#include <iostream>
#include <string>
using std::string;
/*
Analysis Qs
  1. Try to access a protected member from main(). Is it possible?
  2. Try to access a private member from main(). Is it possible?
  3. Try to access a member of the base class from within the derived class that has protected inheritance. Is it possible?
  4. Try to access a member of the base class from within the derived class that has private inheritance. Is it possible?



*/
class BaseClass
{
  public:
    string publicMember{"PublicMember"};
  protected:
    string protectedMember{"ProtectedMember"};
  private:
    string privateMember{"PrivateMember"};
};

class A: public BaseClass {
  public:
    string GetProtected();
    string GetPrivate();
};

string A::GetProtected(){ return protectedMember; }
// string A::GetPrivate(){ return privateMember; } // can't access

int main()
{
  BaseClass base;
  // base.protectedMember; can't access

  A a;
  a.publicMember;
  // a.protectedMember; // can't access
  a.GetProtected();
}