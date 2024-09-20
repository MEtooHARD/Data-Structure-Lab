#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
class Memory {
 public:
  static T **allocArray(int m, int n) {
    T **array = new T *[m];

    T *data = new T[m * n];

    for (int i = 0; i < m; i++) array[i] = &data[i * n];

    return array;
  }
};

int main() {
  int **array;
  array = Memory<int>::allocArray(5, 10);
  int j, k;
  for (j = 0; j < 5; j++)
    for (k = 0; k < 10; k++) array[j][k] = j * 10 + k;
  for (j = 0; j < 5; j++)
    for (k = 0; k < 10; k++) cout << array[j][k] << " ";
}