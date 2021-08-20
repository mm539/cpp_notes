// note: i added some consts and parameter names just to see what that would do. doesn't appear to have done anything.

class NoCopyClass1{
  private: //PRIVATE!
    NoCopyClass1(const NoCopyClass1 & ncc1);
    NoCopyClass1& operator=(const NoCopyClass1 &);
  public:
    NoCopyClass1(){}; // isn't this line unnecessary?
};

class NoCopyClass2{
  public:
    NoCopyClass2(){}
    NoCopyClass2(const NoCopyClass2 &);
    NoCopyClass2& operator=(NoCopyClass2 & ncc2);
};

int main(){
  NoCopyClass1 original1;
  NoCopyClass1 copy1a(original1);
  NoCopyClass1 copy1b = original1;
  // "declared private" error

  NoCopyClass2 original2;
  NoCopyClass2 copy2a(original2);
  NoCopyClass2 copy2b = original2;
  // undefined reference error

  return 0;
}