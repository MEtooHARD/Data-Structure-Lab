#include <cmath>
#include <iostream>

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
  void displayInorder() {}
  void displayPreorder() {}
  void displayPostorder() {}
};

template <class T>
class BinaryTreeInLinkedList {
 private:
  class TreeNode {
   private:
   public:
    TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
    TreeNode *left, *right;
    T data;
  };
  TreeNode *root;
  int numOfElement;

 public:
  BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}
  void addElementAsCompleteTree(T data) {}
  void displayInorder() {}
  void displayPreorder() {}
  void displayPostorder() {}
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
