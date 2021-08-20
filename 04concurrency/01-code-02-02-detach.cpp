#include <thread>
#include <iostream>
using namespace std;

void threadFunctionEven(int w)
{
  this_thread::sleep_for(chrono::milliseconds(w));
  std::cout << "Even thread\n";
}

// what happens if we don't use a function with parameters and instead just sleep it for 1ms?
void threadFunctionOdd(int w)
{
  this_thread::sleep_for(chrono::milliseconds(w));
  cout << "Odd thread\n";
}



int main()
{
  // observe how variations with the number of threats and with the wait time affect output
  int n_threads = 24; 
  int wait_time = 1;

  for (int i = 0; i < n_threads; i++)
  {
    if (i % 2 == 0){
      thread t(threadFunctionEven, wait_time);
      t.detach();
    }
    else
    {
      thread t(threadFunctionOdd, wait_time);
      t.detach();
    }
    
  }
  this_thread::sleep_for(chrono::milliseconds(1)); // <--- what happens if this is commented out?

  cout << "End of main is reached\n";
  return 0;
}