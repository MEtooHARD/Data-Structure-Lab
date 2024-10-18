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

  static void move_value_back(Node *start, Node *end) {
    int sorting_data = end->getData();

    while (start != end->getNext()) {
      int temp_data = start->getData();
      start->setData(sorting_data);
      sorting_data = temp_data;
      start = start->getNext();
    }
  }

  void insertionSort() {
    if (list == NULL) return;

    Node *sorting = list->getNext(), *comp, *next;

    while (sorting != NULL) {
      next = sorting->getNext();
      comp = sorting->getPre();

      if (list->getData() > sorting->getData()) {
        List::move_value_back(list, sorting);
      } else {
        while (comp != NULL && comp->getData() > sorting->getData())
          comp = comp->getPre();
        List::move_value_back(comp->getNext(), sorting);
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
