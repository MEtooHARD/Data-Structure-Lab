#include <iostream>
#include <numeric>  // Optional for accumulate
#include <vector>

using namespace std;

// Templated sum function
template <typename T>
T sum(const vector<T>& v) {
  T total = T();
  for (T item : v) total += item;

  return total;
}

int main() {
  // Integer vector
  vector<int> intVec = {1, 2, 3, 4, 5};
  cout << "Sum of intVec: " << sum(intVec) << endl;

  // Double vector
  vector<double> doubleVec = {1.1, 2.2, 3.3, 4.4};
  cout << "Sum of doubleVec: " << sum(doubleVec) << endl;

  // Empty vector
  vector<int> emptyVec;
  cout << "Sum of emptyVec: " << sum(emptyVec) << endl;

  return 0;
}
