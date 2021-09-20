#include <iostream>
#include <memory>
#include <future>
#include <thread>
using namespace std;

void divide(promise<double> &&prms, double num, double denom){
  try
  {
    if (denom == 0) throw runtime_error("Cannot divide by Zero!"); 
    prms.set_value(num/denom);
  }
  catch(...) // <--- ellipsis operator catches all exceptions
  {
    prms.set_exception(current_exception());
  }
  
}

int main(){
  double num = 55, denom = 0;
  promise<double> prms;
  future<double> ftr = prms.get_future();

  thread t(divide, move(prms), num, denom);
  try
  {
    double result = ftr.get();
    cout << "result: " << result << endl;
  }
  catch( const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  

  t.join();
  return 0;
}