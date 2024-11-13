/* 3., 4. */

#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

template <typename T>
class Node {
 private:
  T data;
  Node *next = nullptr;

 public:
  Node(T ini) { data = ini; }

  void setData(T val) { data = val; }

  T getData() const { return data; }

  void setNext(Node *n) { next = n; }

  Node *getNext() const { return next; }
};

template <typename T>
class List {
 private:
  // int length = 0;
  Node<T> *cursor = nullptr;

 public:
  List() {}

  ~List() {
    while (!empty()) remove();
  }

  bool empty() const { return cursor == nullptr; }

  const Node<T> *back() const {
    if (empty()) throw runtime_error("list is empty");

    return cursor;
  }

  const Node<T> *front() const {
    if (empty()) throw runtime_error("list is empty");

    return cursor->getNext();
  }

  void advance() {
    if (empty()) throw runtime_error("list is empty");

    cursor = cursor->getNext();
  }

  void add(const T &e) {
    Node<T> *n = new Node<T>(e);

    if (empty()) {
      cursor = n;
      cursor->setNext(cursor);
    } else {
      n->setNext(cursor->getNext());
      cursor->setNext(n);
    }
  }

  void remove() {
    if (empty()) return;

    Node<T> *o = cursor->getNext();
    if (o == cursor)
      cursor = nullptr;
    else
      cursor->setNext(o->getNext());

    delete o;
  }

  // the function to count number of nodes in this list
  int length() const {
    if (empty()) return 0;

    int length = 1;
    Node<T> *c = cursor->getNext();

    while (c != cursor) {
      length++;
      c = c->getNext();
    }

    return length;
  }
};

int main() {
  List<int> list;

  list.add(10);  // 10
  list.add(20);  // 10 => 20
  list.add(30);  // 10 => 30 => 20

  cout << "Front: " << list.front()->getData() << endl;  // expect: 30
  cout << "Back: " << list.back()->getData() << endl;    // expect: 10
  cout << "Length: " << list.length() << endl;           // expect: 3

  list.advance();  // 30 => 20 => 10
  cout << "Front after advance: " << list.front()->getData()
       << endl;  // expect: 20

  list.remove();                                             // 30 => 10
  cout << "Length after remove: " << list.length() << endl;  // expect: 2
  cout << "New Front: " << list.front()->getData() << endl;  // expect: 10

  return 0;
}

/* 3., 4. */