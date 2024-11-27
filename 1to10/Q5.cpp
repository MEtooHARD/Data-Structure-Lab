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

  void bubbleSort() {
    if (list == NULL) return;

    Node *end = NULL;
    bool swapped;

    do {
      swapped = false;
      Node *current = list;

      while (current->getNext() != end) {
        if (current->getData() > current->getNext()->getData()) {
          int temp = current->getData();
          current->setData(current->getNext()->getData());
          current->getNext()->setData(temp);
          swapped = true;
        }
        current = current->getNext();
      }
      end = current;
    } while (swapped);
  }

  void selectionSort() {
    if (list == NULL) return;

    Node *i = list;
    Node *j, *least;
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
      comp = sorting->getPre();

      sorting->selfcut();

      if (list->getData() > sorting->getData()) {  // (before head)
        sorting->insert(NULL, list);
        list = sorting;
      } else {
        while (comp != NULL && comp->getData() > sorting->getData())
          comp = comp->getPre();

        if (comp == NULL) {
          sorting->insert(comp->getPre(), comp);
          list = sorting;
        } else {
          sorting->insert(comp, comp->getNext());
        }
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
  l->selectionSort();
  l->print();

  l = new List(10);
  l->print();
  l->insertionSort();
  l->print();
}
