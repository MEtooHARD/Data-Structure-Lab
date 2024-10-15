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
  void SwapNode(Node *a, Node *b) {
    if (a == b) return;
    Node *a_Pre = a->getPre();
    Node *a_Next = a->getNext();
    Node *b_Pre = b->getPre();
    Node *b_Next = b->getNext();
    if (a_Next == b) {
      if (a_Pre) a_Pre->setNext(b);
      b->setPre(a_Pre);
      b->setNext(a);
      a->setPre(b);
      a->setNext(b_Next);
      if (b_Next) b_Next->setPre(a);
    } else if (b_Next == a) {
      if (b_Pre) b_Pre->setNext(a);
      a->setPre(b_Pre);
      a->setNext(b);
      b->setPre(a);
      b->setNext(a_Next);
      if (a_Next) a_Next->setPre(b);
    } else {
      if (a_Pre) a_Pre->setNext(b);
      if (a_Next) a_Next->setPre(b);
      if (b_Pre) b_Pre->setNext(a);
      if (b_Next) b_Next->setPre(a);
      b->setNext(a_Next);
      b->setPre(a_Pre);
      a->setNext(b_Next);
      a->setPre(b_Pre);
    }
    if (list == a) {
      list = b;
    } else if (list == b) {
      list = a;
    }
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
          SwapNode(now, next);
          swapped = true;
        }
        now = next;  // move to the next node
      }
    } while (swapped);
  }

  void selectionSort() {
    if (list == NULL) return;

    Node *now = list, *compare, *min, *temp;
    while (now->getNext() != NULL) {
      min = now;
      compare = now->getNext();
      do {
        if (min->getData() > compare->getData()) min = compare;
        compare = compare->getNext();
      } while (compare != NULL);
      temp = now->getNext();
      SwapNode(now, min);
      now = temp;
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
      } else
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

 private:
  Node *list;
};

int main() {
  srand(time(NULL));
  cout << "bubble";
  cout << "========================\n";
  List *l = new List(10);
  l->print();
  l->bubbleSort();
  l->print();
  cout << "insertion";
  cout << "========================\n";
  l = new List(10);
  l->print();
  l->insertionSort();
  l->print();
  cout << "selection";
  cout << "========================\n";
  l = new List(10);
  l->print();
  l->selectionSort();
  l->print();
}