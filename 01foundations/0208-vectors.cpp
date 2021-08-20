// adding data to a vector

#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

void functionA(vector<int>& vectorA)
{
  vectorA[22] = 4;
}

int main() {
  // 1. three(4) ways of declaring and initializing vectors

  vector<int> v_1{11, 22, 33}; 
  vector<int> v_2 = {4, 5, 6};
  vector<int> v_3;
  v_3 = {7};

  vector<int> {5,6,7}; // #4 = make literal vector (no variable)

  // 2. looping through a vector
  cout << "\nlooping through a vector: " << std::endl;
  vector<int> v {55, 24, 3};

  for (int i: v){
    cout << i << "\n";
  }

  v.push_back(4);

  for (int i = 0; i < v.size(); i++){
    cout << v[i] << "\n";
  }

  // 3. access vectors by position
  cout << "\n3.access vectors by position: " << std::endl;
  // recall, vectors are NON-INDEXED
  //         vectors are stored contiguously in memory
  cout << "v[0]: " << v[0] << std::endl;
  cout << "v[22]: " << v[22] << std::endl;

  functionA(v);
  cout << "will this line be seen? v[22]: " << v[22] << std::endl;

  // 4. clearing a vector
  vector<int> v0{0,1,2,3,4,5,6};
  // v0.clear(); // <-- method #1 per cplusplus.com, memory reallocation and vector resizing is not guaranteed to happen with this
  vector<int>().swap(v0); // <-- method #2 guarantees memory reallocation and vector resizing
  for(auto &i: v0) cout << i << " ";
  cout << endl;
  // so, when does method#1 resize and reallocate memory? I don't know

  return 0;
}


