#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class Node {
 protected:
  T *data = new T;

 public:
  Node() {}
  Node(T d) { (*data) = d; }
  Node &operator=(T d) {
    (*data) = d;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &out, Node n) {
    out << *(n.data);
    return out;
  }

  friend std::ostream &operator<<(std::ostream &out, Node *n) {
    out << *(n->data);
    return out;
  }

  void setData(T d) { *data = d; }
  T &getData() const { return *data; }
};

template <class T>
class BinaryTreeNode : public Node<T> {
 public:
  BinaryTreeNode() : Node<T>() {
    left = nullptr;
    right = nullptr;
  }

  BinaryTreeNode(T d) : Node<T>(d) {
    left = nullptr;
    right = nullptr;
  }

  BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>() {
    left = l;
    right = r;
  }

  BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d) {
    left = l;
    right = r;
  }

  int height() {
    return max(left != nullptr ? left->height() : -1,
               right != nullptr ? right->height() : -1) +
           1;
  }

  BinaryTreeNode<T> *setLeft(BinaryTreeNode<T> *l) {
    left = l;
    return this;
  }
  BinaryTreeNode<T> *setRight(BinaryTreeNode<T> *r) {
    right = r;
    return this;
  }

  BinaryTreeNode<T> *&getLeft() { return left; }
  BinaryTreeNode<T> *&getRight() { return right; }

  bool operator>(BinaryTreeNode<T> n) { return *(this->data) > *(n.data); }
  bool operator==(BinaryTreeNode<T> n) { return *(this->data) == *(n.data); }

 private:
  BinaryTreeNode<T> *left, *right;
};

template <class T>
class AVLTree {
 private:
  BinaryTreeNode<T> *root;
  void inorder(BinaryTreeNode<T> *cur, int n) {
    if (cur == NULL) return;
    inorder(cur->getRight(), n + 1);
    int j;
    for (j = 0; j < n; j++) cout << "  ";
    cout << cur << endl;
    inorder(cur->getLeft(), n + 1);
  }

  BinaryTreeNode<T> *rotateL(BinaryTreeNode<T> *n) {
    BinaryTreeNode<T> *newParent = n->getRight();
    BinaryTreeNode<T> *nRL = n->getRight()->getLeft();
    newParent->setLeft(n);
    n->setRight(nRL);
    if (root == n) root = newParent;

    return newParent;
  }

  BinaryTreeNode<T> *rotateR(BinaryTreeNode<T> *n) {
    BinaryTreeNode<T> *newParent = n->getLeft();
    BinaryTreeNode<T> *nLR = n->getLeft()->getRight();

    newParent->setRight(n);
    n->setLeft(nLR);
    if (root == n) root = newParent;

    return newParent;
  }

  BinaryTreeNode<T> *insert(BinaryTreeNode<T> *cur, T d) {
    BinaryTreeNode<T> *newNode = new BinaryTreeNode<T>(d);
    if (cur == NULL) return newNode;

    if (d > cur->getData())
      cur->setRight(insert(cur->getRight(), d));
    else if (d < cur->getData())
      cur->setLeft(insert(cur->getLeft(), d));
    else
      return cur;

    int balance = (cur->getLeft() != nullptr ? cur->getLeft()->height() : 0) -
                  (cur->getRight() != nullptr ? cur->getRight()->height() : 0);
    // LL
    if (balance > 1 && d < cur->getLeft()->getData()) cur = rotateR(cur);
    // RR
    if (balance < -1 && d > cur->getRight()->getData()) cur = rotateL(cur);
    // LR
    if (balance > 1 && d > cur->getLeft()->getData())
      cur = rotateR(cur->setLeft(rotateL(cur->getLeft())));
    // RL
    if (balance < -1 && d < cur->getRight()->getData())
      cur = rotateL(cur->setRight(rotateR(cur->getRight())));

    return cur;
  }

 public:
  AVLTree() { root = nullptr; };
  void insert(T d) { root = insert(root, d); };
  void inorder() { inorder(root, 0); }
};

int main() {
  AVLTree<int> *tree = new AVLTree<int>();
  srand(0);
  int j, k, i;
  for (j = 0; j < 20; j++) {
    tree->insert(rand() % 100);
    tree->inorder();
  }
}
