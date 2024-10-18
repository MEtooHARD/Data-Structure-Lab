#include <ctime>
#include <iostream>

using namespace std;

void printArray(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    cout << arr[i] << ' ';
  }
}

void sort(int *arr, int n) {
  if (arr == nullptr || n <= 1) return;

  int i = n;
  bool swapped;

  do {
    swapped = false;
    int j = 0;

    while (j < i - 1) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        swapped = true;
      };
      j++;
    }
    i = j;
  } while (swapped);
}

int main() {
  int arr[10];
  srand(time(NULL));
  for (int i = 0; i < 10; i++) arr[i] = rand();

  printArray(arr, 10);
  cout << '\n';
  sort(arr, 10);
  printArray(arr, 10);
}
