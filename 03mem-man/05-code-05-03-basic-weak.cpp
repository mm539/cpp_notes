#include <iostream>
#include <memory>
using namespace std;

int main(){
  // PART 1: INTRO
  shared_ptr<int> mySharedPtr(new int);
  cout << "Shared pointer count = " << mySharedPtr.use_count() << endl;

  
  weak_ptr<int> myWeakPtr1(mySharedPtr);
  weak_ptr<int> myWeakPtr2(mySharedPtr);
  cout << "Shared pointer count = " << mySharedPtr.use_count() << "\n\n";

  // PART 2: EXPIRED
  mySharedPtr.reset(new int);

  if (myWeakPtr1.expired() == true) cout << "Weak pointer expired!\n\n";

  // PART 3: LOCKING
  cout << "\n";
  weak_ptr<string> weak;
  auto shared1 = make_shared<string>("hello");
  weak = shared1;
  cout << "use count: " << shared1.use_count() << endl;
  auto shared2 = weak.lock();
  cout << "use count: " << shared1.use_count() << endl;

  // PART 4: SCOPE
  cout << "weak pointer expired: " << (weak.expired() ? "true": "false") << endl;
  {
    auto shared3 = make_shared<string>("blah");
    weak = shared3;
  }
  cout << "weak pointer expired: " << (weak.expired() ? "true": "false") << endl;

  return 0;
}