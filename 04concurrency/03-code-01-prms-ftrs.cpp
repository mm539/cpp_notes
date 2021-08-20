#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <memory>
using namespace std;

/*
  This example serves as an intro to promises and futures.

  1.How to use them?
    i. make a function:
        - whose function signature has a parameter for an r-value reference to a promise
        - uses prms.set_value()

    ii. make a promise, make a future (prms.get_future())

    iii. initialize the thread with the function. pass std::move(prms) as an argument

    iv. before joining the thread, use ftr.get() to retrive data from the other thread

  2. You may be asking "Why not just use pass-by-reference OR use lambdas with capture lists that capture references?"
    -> Bc this way is much safer in terms of memory management

  3. lambda example at the bottom; also observe the relationship between detach and get (get blocks)
*/

void modifyMsg( promise<string>&& prms, string msg){
  this_thread::sleep_for(chrono::milliseconds(2000));
  string mMsg = "a copy of \"" + msg + "\" was in another thread";
  prms.set_value(mMsg);
}

int main(){
  string msg = "Msg1";
  promise<string> prms;
  future<string> ftr = prms.get_future();

  thread t(modifyMsg, move(prms), msg);


  cout << "msg: " << msg << endl;
  cout << "ftr.get() : " << ftr.get() << endl;
  // cout << "ftr.get() returns " << ftr.get() << endl; // <--- call twice; returns std::future_error: no associated state

  t.join();

  /* experiment #1  with lambda and move semantics -> didn't work
  //    error: promise(const promise&) = delete;

  promise<string> prms0;
  future<string> ftr0 = prms0.get_future();

  thread t0([msg, move(prms0)](){});
  t0.join();
  */

  // experiment # 2 with lambda and references
  promise<string> prms1;
  future<string> ftr1 = prms1.get_future();

  thread t1([msg, &prms1](){
    prms1.set_value(msg + " lambda!");
  });
  t1.detach();
  cout << "ftr1.get() : " << ftr1.get() << endl;
  // t1.detach();


  return 0;
}