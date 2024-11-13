/* 2. */

#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

template <typename T>
class DLinkedList;

template <typename T>
class DNode {
 private:
  T elem;
  DNode* prev = nullptr;
  DNode* next = nullptr;
  friend class DLinkedList<T>;

 public:
  DNode(const T& val) : elem(val) {}

  void setPrev(DNode* n) { prev = n; }

  DNode* getPrev() { return prev; }

  void setNext(DNode* n) { next = n; }

  DNode* getNext() { return next; }
};

template <typename T>
class DLinkedList {
 private:
  DNode<T>* header = nullptr;
  DNode<T>* trailer = nullptr;

 public:
  DLinkedList() {};

  ~DLinkedList() {
    while (!empty()) removeFront();
  };

  bool empty() const { return header == nullptr; };

  const T& front() const {
    if (empty()) throw "empty";
    return header->elem;
  };

  const T& back() const {
    if (empty()) throw "empty";
    return trailer->elem;
  };

  void addFront(const T& e) {
    DNode<T>* newNode = new DNode<T>(e);
    if (empty()) {
      header = newNode;
      trailer = newNode;
    } else {
      newNode->setNext(header);
      header->setPrev(newNode);
      header = newNode;
    }
  };

  void addBack(const T& e) {
    DNode<T>* newNode = new DNode<T>(e);
    if (empty()) {
      header = newNode;
      trailer = newNode;
    } else {
      newNode->setPrev(trailer);
      trailer->setNext(newNode);
      trailer = newNode;
    }
  };

  void removeFront() {
    if (empty()) return;

    DNode<T>* toDel = header;
    if (header == trailer) {
      header = trailer = nullptr;
    } else {
      header = header->getNext();
      header->setPrev(nullptr);
    }
    delete toDel;
  };

  void removeBack() {
    if (empty()) return;

    DNode<T>* toDel = trailer;
    if (header == trailer) {
      header = trailer = nullptr;
    } else {
      trailer = trailer->getPrev();
      trailer->setNext(nullptr);
    }
    delete toDel;
  };
};

int main() {
  DLinkedList<int> list;
  list.addFront(10);
  list.addBack(20);
  cout << "Front: " << list.front() << endl;
  cout << "Back: " << list.back() << endl;
  list.removeFront();
  cout << list.front() << endl;
  list.removeBack();
  cout << "empty? " << list.empty() << endl;
  return 0;
}

/* 2. */