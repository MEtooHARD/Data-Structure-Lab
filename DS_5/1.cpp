#include <iostream>

using namespace std;

// circular array implementation of a sequence
template <typename T>
class ArrCirSeq {
 private:
  T* arr;
  int count;
  int head;  // inc
  int tail;  // exc
  int capacity;

  int cycle(int i) const { return (i + capacity) % capacity; }

  // iterator
  class Iterator {
   private:
    const ArrCirSeq* seq;
    int pos;

   public:
    Iterator(const ArrCirSeq* s, int p) : seq(s), pos(p) {}

    T& operator*() const { return seq->arr[seq->cycle(seq->head + pos)]; }
    Iterator& operator++() {
      pos++;
      return *this;
    }
    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }
    bool operator==(const Iterator& other) const {
      return seq == other.seq && pos == other.pos;
    }
    bool operator!=(const Iterator& other) const { return !(*this == other); }
  };

 public:
  ArrCirSeq(int cap = 10) : capacity(cap), count(0), head(0), tail(0) {
    arr = new T[capacity];
  }
  ~ArrCirSeq() { delete[] arr; }

  int size() const { return count; }

  bool empty() const { return size == 0; }

  Iterator begin() const { return Iterator(this, 0); }

  Iterator end() const { return Iterator(this, count); }

  T atIndex(int i) const {
    if (i < 0 || i >= count) throw out_of_range("Index out of bounds");
    return arr[cycle(head + i)];
  }

  int indexOf(const T& t) const {
    for (int i = 0; i < count; i++)
      if (arr[cycle(head + i)] == t) /*  */
        return i;
    return -1;
  }

  void insertBack(const T& t) {
    if (count == capacity) throw overflow_error("Sequence is full");
    arr[tail] = t;
    tail = cycle(tail + 1);
    count++;
  }

  void popBack() {
    if (count == 0) throw underflow_error("Sequence is empty");
    tail = cycle(tail - 1);
    count--;
  }

  void insertFront(const T& t) {
    if (count == capacity) throw overflow_error("Sequence is full");
    head = cycle(head - 1);
    arr[head] = t;
    count++;
  }

  void popFront() {
    if (count == 0) throw underflow_error("Sequence is empty");
    head = cycle(head + 1);
    count--;
  }

  /* 2-2 part */
  int indexOfElement(const T& t) const { return cycle(indexOf(t) - head); }

  int positionOfElement(const T& t) const { return indexOf(t); }
  /* 2-2 part */
};

int main() {
  ArrCirSeq<int> seq(5);  // Circular array with capacity of 5

  // Test 1: Basic insertions
  cout << "Inserting elements at the back..." << endl;
  seq.insertBack(10);
  seq.insertBack(20);
  seq.insertBack(30);
  cout << "Size after insertions: " << seq.size() << endl;

  // Test 2: Iterating over elements
  cout << "Elements in sequence (using iterator): ";
  for (auto it = seq.begin(); it != seq.end(); ++it) /**/
    cout << *it << " ";
  cout << endl;

  // Test 3: Insert at front and iterate again
  cout << "Inserting elements at the front..." << endl;
  seq.insertFront(5);
  seq.insertFront(1);
  try {  // Overflow test
    seq.insertFront(186746);
  } catch (const overflow_error& e) {
    cout << e.what() << endl;
  }
  cout << "Elements in sequence (using iterator): ";
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;

  // Test 4: Pop elements
  cout << "Popping elements from front and back..." << endl;
  seq.popFront();
  seq.popBack();
  cout << "Elements in sequence after pops: ";
  for (auto it = seq.begin(); it != seq.end(); ++it) /**/
    cout << *it << " ";
  cout << endl;

  // Test 5: Access specific elements
  cout << "Accessing elements by index:" << endl;
  cout << "Element at index 0: " << seq.atIndex(0) << endl;
  cout << "Element at index 1: " << seq.atIndex(1) << endl;

  // Test 6: Boundary and error cases
  try {
    cout << "Accessing out-of-bounds index: ";
    cout << seq.atIndex(10) << endl;
  } catch (const out_of_range& e) {
    cout << e.what() << endl;
  }

  try {
    cout << "Popping from an empty sequence: ";
    ArrCirSeq<int> emptySeq;
    emptySeq.popFront();
  } catch (const underflow_error& e) {
    cout << e.what() << endl;
  }

  // Test 7: Verify iteration with range-based for loop
  cout << "Elements in sequence (range-based for loop): ";
  for (const auto& elem : seq) {
    cout << elem << " ";
  }
  cout << endl;

  return 0;
}

/* expected output: */
/*
Inserting elements at the back...
Size after insertions: 3
Elements in sequence (using iterator): 10 20 30
Inserting elements at the front...
Elements in sequence (using iterator): 1 5 10 20 30
Popping elements from front and back...
Elements in sequence after pops: 5 10 20
Accessing elements by index:
Element at index 0: 5
Element at index 1: 10
Accessing out-of-bounds index: Index out of bounds
Popping from an empty sequence: Sequence is empty
Elements in sequence (range-based for loop): 5 10 20
 */