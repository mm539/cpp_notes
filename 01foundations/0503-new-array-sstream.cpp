#include <iostream>
#include <sstream>
using namespace std;

/* PROBLEM STATEMENT

The first line contains n, the number of students in Kristen's class. The subsequent lines contain each student's exam grades for this semester.

How many students got a higher total score than "kristen"

*/

static istringstream ss;

// Write your Student class here
class Student{
    public:
        void input();
        int calculateTotalScore();
    private:
        int scores[5];
};

void Student::input(){
    int n;
    
    for(int i = 0; i < 5; i++){
        ss >> n;
        scores[i] = n;
        cout << scores[i] << " ";
    }
    cout << endl;
}

int Student::calculateTotalScore(){
    int sum{0};
    
    for(int i = 0; i < 5; i++){
        sum += scores[i];
    }
    return sum;
}

int main() {
    string lines{"4 "}; // first line;
    lines += "30 40 45 10 10 ";
    lines += "40 40 40 10 10 ";
    lines += "50 20 30 10 10 ";
    lines += "50 50 50 50 50 ";
    ss.str(lines);


    int n; // number of students
    ss >> n;
    Student *s = new Student[n]; // an array of n students
    
    for(int i = 0; i < n; i++){
        s[i].input();
    }

    // calculate kristen's score
    int kristen_score = s[0].calculateTotalScore();

    // determine how many students scored higher than kristen
    int count = 0; 
    for(int i = 1; i < n; i++){
        int total = s[i].calculateTotalScore();
        if(total > kristen_score){
            count++;
        }
    }

    // print result
    cout << count;
    
    return 0;
}
