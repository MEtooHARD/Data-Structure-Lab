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

  static void key_node_persister(Node *&a, Node *&b, Node *&p) {
    if (a == p)
      p = b;
    else if (b == p)
      p = a;
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

    Node *end = NULL, *next;
    bool swapped;

    do {
      swapped = false;
      Node *current = list;

      while (current->getNext() != end) {
        next = current->getNext();

        if (current->getData() > next->getData()) {
          current->swapWith(next);
          Node::key_node_persister(current, next, list);

          swapped = true;
        } else {
          current = current->getNext();
        }
      }
      end = current;
    } while (swapped);
  }

  void selectionSort() {
    if (list == NULL) return;

    Node *i = list, *j, *least;

    while (i->getNext() != NULL) {
      j = i->getNext();
      least = i;

      while (j != NULL) {
        if (least->getData() > j->getData()) least = j;
        j = j->getNext();
      }

      if (least != i) {
        i->swapWith(least);
        Node::key_node_persister(i, least, list);
      }
      i = least->getNext();
    }
  }

  void insertionSort() {
    if (list == NULL) return;

    Node *sorting = list->getNext(), *comp, *next;

    while (sorting != NULL) {
      next = sorting->getNext();
      comp = sorting->getPre();

      sorting->selfcut();

      if (list->getData() > sorting->getData()) {
        sorting->insert(NULL, list);
        list = sorting;
      } else {
        while (comp != NULL && comp->getData() > sorting->getData())
          comp = comp->getPre();

        sorting->insert(comp, comp->getNext());
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
