#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class TreeInLinkedList {
 private:
  class TreeNode {
    //    private:
   public:
    TreeNode(T d, TreeNode *p) : data(d), parent(p) {}
    TreeNode *parent;
    T data;
  };
  vector<TreeNode *> *nodeList;

 public:
  TreeInLinkedList() { nodeList = new vector<TreeNode *>(); }

  void addElement(T data) {
    int j, k = nodeList->size();
    if (data == 1) {
      nodeList->clear();
      nodeList = new vector<TreeNode *>();
      //   TreeNode *newNode = new TreeNode(data, nullptr);
      nodeList->push_back(new TreeNode(data, nullptr));
    } else {
      for (j = 0; j < k; j++) {
        if (data % (*nodeList)[j]->data == 0) {
          TreeNode *newNode = new TreeNode(data, (*nodeList)[j]);
          nodeList->push_back(newNode);
        }
      }
    }
  }

  void Preorder(TreeNode *n) {
    if (!n) return;

    cout << n->data << " ";

    for (TreeNode *child : *nodeList) {
      if (child->parent == n) {
        Preorder(child);
      }
    }
  }

  void Postorder(TreeNode *n) {
    if (!n) return;

    for (TreeNode *child : *nodeList) {
      if (child->parent == n) {
        Postorder(child);
      }
    }

    cout << n->data << " ";
  }

  void displayPreorder(/* TreeNode *n = nullptr */) {
    if (!nodeList->empty()) {
      Preorder(nodeList->front());
    }
  }

  void displayPostorder() {
    if (!nodeList->empty()) {
      Postorder(nodeList->front());
    }
  }
};

int main() {
  TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();
  int j;
  int n;
  cin >> n;
  for (j = 1; j <= n; j++) tree->addElement(j);
  tree->displayPreorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;
}
