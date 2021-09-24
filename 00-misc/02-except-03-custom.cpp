#include <iostream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;

/*
Sample Input

3
Peter
Me
Arxwwz

Sample Output

Valid
Too short: 2
Invalid
*/

/* Define the exception here */
class BadLengthException: public exception{
    private:
        string n_;
    public:
        BadLengthException(int n) {n_ = to_string(n);}
        const char* what() const throw() { return n_.c_str(); }
};


bool checkUsername(string username) {
	bool isValid = true;
	int n = username.length();
	if(n < 5) {
		throw BadLengthException(n);
	}
	for(int i = 0; i < n-1; i++) {
		if(username[i] == 'w' && username[i+1] == 'w') {
			isValid = false;
		}
	}
	return isValid;
}

int main() {
	int T; cin >> T;
	while(T--) {
		string username;
		cin >> username;
		try {
			bool isValid = checkUsername(username);
			if(isValid) {
				cout << "Valid" << '\n';
			} else {
				cout << "Invalid" << '\n';
			}
		} catch (BadLengthException e) {
			cout << "Too short: " << e.what() << '\n';
		}
	}
	return 0;
}