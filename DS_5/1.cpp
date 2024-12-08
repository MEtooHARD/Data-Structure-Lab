#include <iostream>

using namespace std;

// circular array implementation of a sequence
template <typename T>
class ArraySeq {
 private:
  T* arr;
  int size;
  int head;
  int tail;

  int cycle(int i) { return (i + size) % size; }

 public:
  int size() { return size; }

  bool empty() { return size == 0; }

  T atIndex(int i) { return arr[cycle(head + i)]; }

  indexOf(T t) {
    for (int i = 0; i < size; i++)
      if (arr[cycle(head + i)] == t) return i;

    return -1;
  }
};