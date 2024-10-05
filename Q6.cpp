#include <cstdlib>
#include <ctime>
#include <iostream>

#define SIZE 100

using namespace std;

class Node {
 private:
  int data;
  Node *next, *pre;

 public:
  Node() {
    next = NULL;
    pre = NULL;
  }
  Node(int n) {
    data = n;
    next = NULL;
    pre = NULL;
  }
  int getData() { return data; }
  Node *getNext() { return next; }
  Node *getPre() { return pre; }
  void setData(int d) { data = d; }
  void setNext(Node *n) { next = n; }
  void setPre(Node *p) { pre = p; }

  Node *getEnd() {
    Node *temp = this;
    while (temp->getNext() != NULL) temp = temp->getNext();
    return temp;
  }

  void suicide() {
    if (getPre()) getPre()->setNext(getNext());
    if (getNext()) getNext()->setPre(getPre());
  }

  void insert(Node *a, Node *b) {
    if (a) a->setNext(this);
    if (b) b->setPre(this);
    setPre(a);
    setNext(b);
  }

  void swapWith(Node *a) {
    // if (this == a) return;

    // Node *thisPre = this->getPre();
    // Node *thisNext = this->getNext();
    // Node *aPre = a->getPre();
    // Node *aNext = a->getNext();

    // if (thisNext == a) {
    //   a->setPre(thisPre);
    //   a->setNext(this);
    //   setPre(a);
    //   setNext(aNext);
    //   if (thisPre) thisPre->setNext(a);
    //   if (aNext) aNext->setPre(this);
    // } else if (thisPre == a) {
    //   a->setPre(this);
    //   a->setNext(thisNext);
    //   setPre(aPre);
    //   setNext(a);
    //   if (aPre) aPre->setNext(this);
    //   if (thisNext) thisNext->setPre(a);
    // } else {
    //   setPre(aPre);
    //   setNext(aNext);
    //   a->setPre(thisPre);
    //   a->setNext(thisNext);
    //   if (aPre) aPre->setNext(this);
    //   if (aNext) aNext->setPre(this);
    //   if (thisPre) thisPre->setNext(a);
    //   if (thisNext) thisNext->setPre(a);
    // }
    if (this == a) return;  // Prevent self-swap

    // Save the neighboring nodes
    Node *thisPre = this->getPre();
    Node *thisNext = this->getNext();
    Node *aPre = a->getPre();
    Node *aNext = a->getNext();

    // If a is directly next or previous to this
    if (thisNext == a) {
      if (aPre) aPre->setNext(this);
      if (thisNext) thisNext->setPre(this);
      this->setNext(aNext);
      this->setPre(a);
      a->setNext(this);
      a->setPre(thisPre);
      if (thisPre) thisPre->setNext(a);
      if (aNext) aNext->setPre(a);
    } else if (thisPre == a) {
      // a is directly before this
      if (thisNext) thisNext->setPre(a);
      if (thisPre) thisPre->setNext(a);
      a->setNext(this);
      a->setPre(thisPre);
      this->setPre(aPre);
      this->setNext(aNext);
      if (aNext) aNext->setPre(this);
      if (aPre) aPre->setNext(this);
    } else {
      // General case where they are not adjacent
      if (aPre) aPre->setNext(this);
      if (thisPre) thisPre->setNext(a);
      if (thisNext) thisNext->setPre(a);
      if (aNext) aNext->setPre(this);

      this->setPre(aPre);
      this->setNext(aNext);
      a->setPre(thisPre);
      a->setNext(thisNext);
    }
  }
};

class List {
 public:
  List() { list = NULL; }
  List(int n) { generate(n); }

  void generate(int n) {
    int j;
    list = NULL;
    for (j = 0; j < n; j++) generate();
  }

  void generate() {
    Node *buf = new Node(rand());
    buf->setNext(list);
    if (list != NULL) list->setPre(buf);
    list = buf;
  }

  void bubbleSort() {
    if (list == NULL) return;

    Node *end = list->getEnd();
    Node *i = list;
    Node *j;
    Node *temp;
    while (i->getNext() != NULL) {
      j = end;
      while (i != j) {
        if (j->getPre()->getData() > j->getData()) {
          j->swapWith(j->getPre());
          j = j->getNext();
        }
        j = j->getPre();
      }
      i = i->getNext();
    }
  }

  void selectionSort() {
    if (list == NULL) return;

    Node *i = list;
    Node *j;
    Node *least;
    Node *temp;
    while (i->getNext() != NULL) {
      j = i->getNext();
      least = i;
      while (j != NULL) {
        if (least->getData() > j->getData()) least = j;
        j = j->getNext();
      }
      if (least != i) {
        temp = i;
        i = least;
        least = temp;
        i->swapWith(least);
      }
      i = i->getNext();
    }
  }

  void insertionSort() {
    if (list == NULL) return;

    Node *i = list->getNext();
    Node *j, *temp;
    while (i != NULL) {
      j = i->getPre();
      temp = i;

      if (list->getData() > i->getData()) {
        temp->suicide();
        temp->insert(NULL, list);
      } else if (j != NULL && j->getPre() != NULL) {
        while (j != NULL && j->getData() > i->getData()) j = j->getPre();
        if (j != temp->getPre()) {
          temp->suicide();
          temp->insert(j->getPre(), j);
        }
      }
      i = i->getNext();
    };
  }

  void print() {
    Node *cur = list;
    while (cur != NULL) {
      cout << cur->getData() << " ";
      cur = cur->getNext();
    }
    cout << endl;
  }

 private:
  Node *list;
};

int main() {
  srand(time(NULL));
  List *l = new List(10);
  l->print();
  l->bubbleSort();
  l->print();

  l = new List(10);
  l->print();
  l->insertionSort();
  l->print();

  l = new List(10);
  l->print();
  l->selectionSort();
  l->print();
}
