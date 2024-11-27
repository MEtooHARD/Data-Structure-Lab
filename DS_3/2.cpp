#include <iostream>
#include <stdexcept>

using namespace std;

class DequeEmpty : public runtime_error {
 public:
  DequeEmpty(const string &err) : runtime_error(err) {}
};

class DequeFull : public runtime_error {
 public:
  DequeFull(const string &err) : runtime_error(err) {}
};

class CircularDeque {
 private:
  int *arr;
  int capacity;
  int _front;
  int _rear;
  int _size;

  bool full() const { return _size == capacity; }

 public:
  CircularDeque(int cap) : capacity(cap), _front(-1), _rear(-1), _size(0) {
    arr = new int[capacity];
  }

  ~CircularDeque() { delete[] arr; }

  bool empty() const { return _size == 0; }

  void pushFront(int value) {
    if (full()) throw DequeFull("Deque is full");

    if (empty())
      _front = _rear = 0;
    else
      _front = (_front - 1 + capacity) % capacity;

    arr[_front] = value;
    ++_size;
  }

  void insertBack(int value) {
    if (full()) throw DequeFull("Deque is full");

    if (empty())
      _front = _rear = 0;
    else
      _rear = (_rear + 1) % capacity;

    arr[_rear] = value;
    ++_size;
  }

  int eraseFront() {
    if (empty()) throw DequeEmpty("Deque is empty");

    int value = arr[_front];
    if (_front == _rear)
      _front = _rear = -1;
    else
      _front = (_front + 1) % capacity;

    --_size;
    return value;
  }

  int eraseBack() {
    if (empty()) throw DequeEmpty("Deque is empty");

    int value = arr[_rear];
    if (_front == _rear)
      _front = _rear = -1;
    else
      _rear = (_rear - 1 + capacity) % capacity;

    --_size;
    return value;
  }

  int front() const {
    if (empty()) throw DequeEmpty("Deque is empty");

    return arr[_front];
  }

  int back() const {
    if (empty()) throw DequeEmpty("Deque is empty");

    return arr[_rear];
  }

  int size() const { return _size; }
};

int main() {
  try {
    CircularDeque deque(5);

    deque.insertBack(10);
    deque.insertBack(20);
    deque.pushFront(5);
    deque.pushFront(1);

    cout << "Front element: " << deque.front() << "\n";  // 1
    cout << "Rear element: " << deque.back() << "\n";    // 20

    deque.eraseFront();
    cout << "Front after pop: " << deque.front() << "\n";  // 5

    deque.eraseBack();
    cout << "Rear after pop: " << deque.back() << "\n";  // 10

    cout << "Current _size: " << deque.size() << "\n";  // 2

  } catch (const exception &e) {
    cerr << e.what() << "\n";
  }

  return 0;
}
