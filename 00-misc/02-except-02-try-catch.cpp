#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

/*

In this challenge, you are required to handle error messages while working with small computational server that performs complex calculations.
It has a function that takes

large numbers as its input and returns a numeric result. Unfortunately, there are various exceptions that may occur during execution.

Complete the code in your editor so that it prints appropriate error messages, should anything go wrong. The expected behavior is defined as follows:

    If the compute function runs fine with the given arguments, then print the result of the function call.
    If it fails to allocate the memory that it needs, print Not enough memory.
    If any other standard C++ exception occurs, print Exception: S where 

is the exception's error message.
If any non-standard exception occurs, print Other Exception.

Input Format:

The first line contains an integer, , the number of test cases.
Each of the subsequent lines describes a test case as space-separated integers, and , respectively.

*/

class Server {
private:
	static int load;
public:
	static int compute(long long A, long long B) {
		load += 1;
		if(A < 0) {
			throw std::invalid_argument("A is negative");
		}
		vector<int> v(A, 0);
		int real = -1, cmplx = sqrt(-1);
		if(B == 0) throw 0;
		real = (A/B)*real;
		int ans = v.at(B);
		return real + A - B*ans;
	}
	static int getLoad() {
		return load;
	}
};
int Server::load = 0;

static istringstream ss;

int main() {
  string lines = "";
  lines += "4\n";
  lines += "8 5\n";
  lines += "1435434255433 5\n";
  lines += "3 10\n";
  lines += "-8 -5\n";
  ss.str(lines);

	int T; ss >> T;
	while(T--) {
		long long A, B;
		ss >> A >> B;

		/* Enter your code here. */
        try {
            cout << Server::compute(A, B) << endl;
        } catch (std::bad_alloc &e){
            cout << "Not enough memory" << endl;
        } catch (std::exception &e) {
            string error_msg = e.what();
            cout << "Exception: " << error_msg << endl;
        } catch (...){
            cout << "Other Exception" << endl;
        }
        // WARNING: ERROR MESSAGE IS PLATFORM DEPENDENT

	}
}