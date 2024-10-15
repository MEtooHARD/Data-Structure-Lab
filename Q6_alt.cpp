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
    Node *_ = this;
    while (_->getNext() != NULL) _ = _->getNext();
    return _;
  }

  void selfcut() {
    if (getPre()) getPre()->setNext(getNext());
    if (getNext()) getNext()->setPre(getPre());
  }

  void insert(Node *a, Node *b) {
    if (a) a->setNext(this);
    if (b) b->setPre(this);
    setPre(a);
    setNext(b);
  }

  void swapWith(Node *b) {
    if (this == b) return;
    Node *this_next = getNext(), *this_prev = getPre();
    Node *a_next = b->getNext(), *a_prev = b->getPre();

    b->selfcut();
    if (this_next == b) {
      b->insert(this_prev, this);
    } else if (this_prev == b) {
      b->insert(this, this_next);
    } else {
      selfcut();
      b->insert(this_prev, this_next);
      insert(a_prev, a_next);
    }
  }
};

class List {
 private:
  Node *list;

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

  void swapNode(Node *a, Node *b) {
    if (a == b) return;

    if (list == a)
      list == b;
    else if (list == b)
      list == a;

    a->swapWith(b);
  }

  void bubbleSort() {
    if (list == NULL) {
      return;
    }
    bool swapped;
    do {
      swapped = false;
      Node *now = list, *next;
      while (now->getNext() != NULL) {
        next = now->getNext();
        if (now->getData() > next->getData()) {
          swapNode(now, next);
          swapped = true;
        }
        now = next;  // move to the next node
      }
    } while (swapped);
  }

  void selectionSort() {
    if (list == NULL) return;

    Node *i = list;
    Node *j;
    Node *least;
    int temp;
    while (i->getNext() != NULL) {
      j = i->getNext();
      least = i;
      while (j != NULL) {
        if (least->getData() > j->getData()) least = j;
        j = j->getNext();
      }
      if (least != i) {
        temp = i->getData();
        i->setData(least->getData());
        least->setData(temp);
      }
      i = i->getNext();
    }
  }

  void insertionSort() {
    if (list == NULL) return;

    Node *sorting = list->getNext(), *comp, *next;

    while (sorting != NULL) {
      next = sorting->getNext();
      comp = sorting;

      if (list->getData() > sorting->getData()) {  // (before head)
        sorting->selfcut();
        sorting->insert(NULL, list);
        list = sorting;
      }

      while (comp != NULL && comp->getPre() != NULL) {
        comp = comp->getPre();

        if (comp->getData() > sorting->getData() &&
            comp->getPre()->getData() < sorting->getData()) {
          sorting->selfcut();
          sorting->insert(comp->getPre(), comp);
          break;
        }

        comp = comp->getPre();
      }

      sorting = next;
    }
  }

  void print() {
    Node *cur = list;
    while (cur != NULL) {
      cout << cur->getData() << " ";
      cur = cur->getNext();
    }
    cout << endl;
  }
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
