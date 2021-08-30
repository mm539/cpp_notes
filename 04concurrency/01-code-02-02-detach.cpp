#include <thread>
#include <iostream>
using namespace std;

void threadFunctionEvenP(int w)
{
  this_thread::sleep_for(chrono::milliseconds(w));
  std::cout << "Even thread\n";
}

void threadFunctionOddP(int w)
{
  this_thread::sleep_for(chrono::milliseconds(w));
  cout << "Odd thread\n";
}

// what happens if we don't use a function with parameters and instead just sleep it for 1ms?
void threadFunctionEven()
{
  this_thread::sleep_for(chrono::milliseconds(1));
  std::cout << "Even thread\n";
}

void threadFunctionOdd()
{
  this_thread::sleep_for(chrono::milliseconds(1));
  cout << "Odd thread\n";
}


int main()
{
  // PART 1: FN WITH PARAM
  // observe how variations with the number of threats and with the wait time affect output
  int n_threads = 24; 
  int wait_time = 1;

  for (int i = 0; i < n_threads; i++)
  {
    if (i % 2 == 0){
      thread t(threadFunctionEvenP, wait_time);
      t.detach();
    }
    else
    {
      thread t(threadFunctionOddP, wait_time);
      t.detach();
    }
    
  }

  this_thread::sleep_for(chrono::milliseconds(1000)); 
  cout << "End of PART 1 is reached\n\n";

  // PART 2: FN WITHOUT PARAM
  for (int i = 0; i < n_threads; i++)
  {
    if (i % 2 == 0){
      thread t(threadFunctionEven);
      t.detach();
    }
    else
    {
      thread t(threadFunctionOdd);
      t.detach();
    }
    
  }

this_thread::sleep_for(chrono::milliseconds(1)); // <--- what happens if this is commented out?
  cout << "End of main is reached\n";
  return 0;
}