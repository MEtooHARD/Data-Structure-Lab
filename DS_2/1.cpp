/* 1. */

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

  T getData() { return data; }

  void setNext(Node *n) { next = n; }

  Node *getNext() { return next; }
};

template <typename T>
class List {
 private:
  int length = 0;
  Node<T> *head = nullptr;
  Node<T> *tail = nullptr;

 public:
  List() {}

  void append(T data) {
    Node<T> *newNode = new Node<T>(data);

    if (length++ == 0) {
      head = newNode;
      tail = newNode;
    } else {
      tail->setNext(newNode);
      tail = newNode;
    }
  }

  int size() { return length; }
};

int main() {
  srand(time(NULL));
  List<int> list;
  int expected_size = (rand() % 50);
  for (int i = 0; i < expected_size; i++) list.append(i);
  cout << "expect: " << expected_size << endl;
  cout << "get: " << list.size() << endl << endl;
}

/* 1. */