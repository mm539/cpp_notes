#include <iostream>
#include <thread>
using namespace std;


int main()
{
  cout << "Capture lists:\n";
  int id = 0;

  auto f0 = [&id](){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "A) ID in t1 (capture-by-reference) = " << id << std::endl;
  };
  std::thread t1(f0); // start the first thread

  // this thread uses an anonymous inline function
  std::thread t2([id]() { // mutable {
    std::cout << "B) ID in t2 (capture-by-value) = " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(700));
    std::cout << "B) ID in t2 (capture-by-value) = " << id << std::endl;
  }); // start the second thread

  id++;
  this_thread::sleep_for(chrono::milliseconds(500));
  id++;
  std::cout << "C) ID in main = " << id << std::endl;

  t1.join();
  t2.join();

  /* OBSERVE
  The capture-by-value thread is executed with the compile-time-value of id.

  paraphrase->"When data to which the reference refers changes before the thread is executed, those changes will be visible to the thread.

  So, what determines order of execution?
  What happens if you add/remove time delays in certain places?

  I removed the time delay from f0, the output remained the same.
  I added a time delay prior to id++;, changed! Just as expected
  */

  cout << "\n\nParameter lists:\n";
  // auto f1 = [](int x){ x++};
  auto f1 = [](int x){};
  auto f2 = [](int& x) { x++; };
  auto f3 = [](int x) mutable { x++; };

  int x = 0;

  thread t01(f1, x);
  //thread t02(f2, x); // <--- didn't work
  thread t02(f2, ref(x)); 
  thread t03(f3, x);

  t01.join();
  t02.join(); 
  t03.join();

  cout << "x: " << x << endl;
  return 0;
}