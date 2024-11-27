#include <iostream>
#include <stdexcept>

using namespace std;

class QueueEmpty : public runtime_error {
 public:
  QueueEmpty(const string& err) : runtime_error(err) {}
};

template <typename T>
class Queue {
 private:
  T* arr;
  int capacity;
  int _front;
  int rear;
  int _size;

  void resize(int newCapacity) {
    T* newArr = new T[newCapacity];
    for (int i = 0; i < _size; ++i) newArr[i] = arr[(_front + i) % capacity];

    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
    _front = 0;
    rear = _size - 1;
  }

 public:
  explicit Queue(int cap = 10) : capacity(cap), _front(0), rear(-1), _size(0) {
    arr = new T[capacity];
  }

  ~Queue() { delete[] arr; }

  bool empty() const { return _size == 0; }

  int size() const { return _size; }

  void enqueue(const T& value) {
    if (_size == capacity) resize(capacity * 2);

    rear = (rear + 1) % capacity;
    arr[rear] = value;
    _size++;
  }

  T dequeue() {
    if (empty()) throw QueueEmpty("Queue is empty");

    T value = arr[_front];
    _front = (_front + 1) % capacity;
    _size--;

    if (_size > 0 && _size == capacity / 4) resize(capacity / 2);

    return value;
  }

  T& front() const {
    if (empty()) throw QueueEmpty("Queue is empty");

    return arr[_front];
  }
};

int main() {
  try {
    Queue<int> q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Front: " << q.front() << "\n";  // 10
    cout << "Size: " << q.size() << "\n";    // 3

    cout << "Dequeued: " << q.dequeue() << "\n";  // 10
    cout << "Front: " << q.front() << "\n";       // 20
    cout << "Size: " << q.size() << "\n";         // 2

    q.enqueue(40);
    q.enqueue(50);

    while (!q.empty())
      cout << "Dequeued: " << q.dequeue() << "\n";  // 20 30 40 50

  } catch (const exception& e) {
    cerr << e.what() << "\n";
  }

  return 0;
}
