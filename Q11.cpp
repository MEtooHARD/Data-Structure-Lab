#include <iostream>
#include <string>

using namespace std;

template <class T>
class BinarySearchTree {
 private:
  struct Node {
    T data;
    Node *left, *right;
    Node(T d) : data(d) {}
  };
  void inorder(Node *cur) {
    if (!cur) return;
    inorder(cur->left);
    cout << cur->data << " ";
    inorder(cur->right);
  }
  Node *root;

 public:
  BinarySearchTree() : root(nullptr) {}
  void insertElement(T d) {
    if (root == nullptr) {
      root = new Node(d);
      return;
    }
    Node *mani = root;  // manipulating
    bool finish = false;

    while (true) {
      if (d == mani->data) break;

      if (d < mani->data) {
        if (mani->left == nullptr) {
          mani->left = new Node(d);
          break;
        } else
          mani = mani->left;
      } else {
        if (mani->right == nullptr) {
          mani->right = new Node(d);
          break;
        } else
          mani = mani->right;
      }
    }
  }

  void print() {
    inorder(root);
    cout << endl;
  }

  bool search(T d) {
    Node *mani = root;

    while (mani == nullptr) {
      if (d == mani->data) return true;
      mani = (d < mani->data) ? mani->left : mani->right;
    }

    return false;
  }

  int height(Node *n = nullptr, int depth = -1) {
    if (n == nullptr)
      return depth == -1 ? height(root, root != nullptr) : depth;
    else
      return max(height(n->left, depth + 1), height(n->right, depth + 1));
  }
  /*
      first call case at L69
      depth is -1 by default for the first call
      depth is 0 if root doesn't exist
      depth is 1 if root exists
      and 1+X will be the height
   */
};

int main() {
  int data;
  string command;
  BinarySearchTree<int> *bst = new BinarySearchTree<int>();
  while (true) {
    cin >> command;
    if (command == "insert") {
      cin >> data;
      bst->insertElement(data);
    } else if (command == "search") {
      cin >> data;
      if (bst->search(data))
        cout << "true" << endl;
      else
        cout << "false" << endl;
    } else if (command == "height") {
      cout << bst->height() << endl;
    } else if (command == "print") {
      bst->print();
    } else if (command == "exit") {
      break;
    }
  }
}
