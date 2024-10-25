#include <cmath>
#include <iostream>
#include <queue>

using namespace std;

template <class T>
class BinaryTreeInArray {
 private:
  T *array;
  int height;
  int numOfElement;
  void resize(int size) {
    T *temp = new T[numOfElement];
    int j;
    for (j = 0; j < numOfElement; j++) temp[j] = array[j];
    delete array;
    array = new T[static_cast<int>(pow(2, height + 1)) - 1];
    for (j = 0; j < numOfElement; j++) array[j] = temp[j];
    height++;
    delete temp;
  }

 public:
  BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}

  void addElementAsCompleteTree(T data) {
    int cap = pow(2, height) - 1;
    if (numOfElement + 1 > cap) resize((cap + 1) * 2 - 1);
    array[numOfElement] = data;
    numOfElement++;
  }

  void displayInorder(int i = 0) {
    if (i >= numOfElement) return;
    displayInorder(i * 2 + 1);
    cout << array[i] << ' ';
    displayInorder(i * 2 + 2);
  }

  void displayPreorder(int i = 0) {
    if (i >= numOfElement) return;
    cout << array[i] << ' ';
    displayPreorder(i * 2 + 1);
    displayPreorder(i * 2 + 2);
  }

  void displayPostorder(int i = 0) {
    if (i >= numOfElement) return;
    displayPostorder(i * 2 + 1);
    displayPostorder(i * 2 + 2);
    cout << array[i] << ' ';
  }
};

template <class T>
class BinaryTreeInLinkedList {
 private:
  class TreeNode {
    //  private:
   public:
    TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
    TreeNode *left, *right;
    T data;
  };
  TreeNode *root;
  int numOfElement;

 public:
  BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}

  void addElementAsCompleteTree(T data) {
    TreeNode *newNode = new TreeNode(data);
    if (root == nullptr) {
      root = newNode;
      numOfElement++;
      return;
    }

    std::queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
      TreeNode *current = q.front();
      q.pop();

      if (current->left == nullptr) {
        current->left = newNode;
        numOfElement++;
        return;
      } else {
        q.push(current->left);
      }

      if (current->right == nullptr) {
        current->right = newNode;
        numOfElement++;
        return;
      } else {
        q.push(current->right);
      }
    }
  }

  void displayInorder(TreeNode *n = nullptr) {
    if (n == nullptr) n = root;
    if (n->left != nullptr) displayInorder(n->left);
    cout << n->data << ' ';
    if (n->right != nullptr) displayInorder(n->right);
  }

  void displayPreorder(TreeNode *n = nullptr) {
    if (n == nullptr) n = root;
    cout << n->data << ' ';
    if (n->left != nullptr) displayPreorder(n->left);
    if (n->right != nullptr) displayPreorder(n->right);
  }

  void displayPostorder(TreeNode *n = nullptr) {
    if (n == nullptr) n = root;
    if (n->left != nullptr) displayPostorder(n->left);
    if (n->right != nullptr) displayPostorder(n->right);
    cout << n->data << ' ';
  }
};

int main() {
  BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
  BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
  int j, n;
  cin >> n;
  for (j = 0; j < n; j++) {
    b->addElementAsCompleteTree(j);
    tree->addElementAsCompleteTree(j);
  }
  b->displayInorder();
  cout << endl;
  tree->displayInorder();
  cout << endl;
  b->displayPreorder();
  cout << endl;
  tree->displayPreorder();
  cout << endl;
  b->displayPostorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;
  return 0;
}
