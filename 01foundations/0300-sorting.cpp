#include <vector>
#include <string>
#include <iostream>
#include <algorithm> // for sort
using std::cout;
using std::string;
using std::vector;
using std::sort;


bool Compare(const int a, const int b) {
    return a > b;
  }

void VectorSort(vector<int> *v) {
    sort(v->begin(), v->end(), Compare);
  }

void PrintVector(vector<int> *v){
  cout << "printing!" << "\n";
    for (int j : *v){
      cout << j << " ";
    }
    cout << "\n";
  }

int main(){
  vector<int> v {5, 6, 1, 3, 2};
  PrintVector(&v);
  VectorSort(&v);
  PrintVector(&v); // 6 5 3 2 1

  /* an implementation of it in the project one code

  bool Compare(RouteModel::Node* node1, RouteModel::Node* node 2){
    float f1 = node1->h_value + node1->g_value;
    float f2 = node2->h_value + node2->h_value;
    return f1>f2;
  }

  void NodeSort(std::vector<RouteModel::Node*> open){
    sort(open.begin(), open.end(), Compare);
  }*/
}


