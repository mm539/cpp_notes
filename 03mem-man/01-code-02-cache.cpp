#include <chrono>
#include <iostream>

/*
Observe execution time as it varies with:
  i. std::cout
  ii. array size

think about how memory is stored:
  column vs rows
*/

int main()
{
  const int size = 4;
  static int x[size][size];

  // 1. TIME START
  auto t1 = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      x[i][j] = i + j; // 1028 ms
      std::cout << &x[i][j] << ": i=" << i << ", j=" << j << std::endl; // 9972 ms
      // from this output, you can see memory is continguously allocated

      //x[j][i] = i + j; // 971 ms
      //std::cout << &x[j][i] << ": i=" << i << ", j=" << j << std::endl; // 12966 ms
    }
    std::cout << std::endl;
  }

    // 2. TIME STOP
    auto t2 = std::chrono::high_resolution_clock::now(); // stop time measurement
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Execution TIME: " << duration << " microseconds" << "\n";//std::endl;

    return 0;
}