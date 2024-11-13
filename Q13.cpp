#include <queue>
template <class T>
class MaxHeap {
 private:
  struct Node {
    T data;
    Node *left, *right, *parent;
  };

  int size;
  Node* root;

  Node* getLast() {
    if (!root) return nullptr;

    std::queue<Node*> q;
    q.push(root);
    Node* last = nullptr;

    while (!q.empty()) {
      last = q.front();
      q.pop();

      if (last->left) q.push(last->left);
      if (last->right) q.push(last->right);
    }
    return last;
  }

  void bubbleUp(Node* node) {
    while (node->parent && node->data > node->parent->data) {
      std::swap(node->data, node->parent->data);
      node = node->parent;
    }
  }

  void bubbleDown(Node* node) {
    while (node->left || node->right) {
      Node* largest = node;
      if (node->left && node->left->data > largest->data)  //
        largest = node->left;

      if (node->right && node->right->data > largest->data)
        largest = node->right;

      if (largest == node) break;

      std::swap(node->data, largest->data);
      node = largest;
    }
  }

 public:
  // Constructing aN empty heap.
  MaxHeap() {
    root = nullptr;
    size = 0;
  }

  // To add an element to the heap.
  void insert(T val) {
    if (root == nullptr) {
      root = new Node(val);
    } else {
      std::queue<Node*> q;
      q.push(root);
      while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        if (cur->left == nullptr) {
          cur->left = new Node(val);
          cur->left->parent = cur;
          bubbleUp(cur->left);
          break;
        } else if (cur->right == nullptr) {
          cur->right = new Node(val);
          cur->right->parent = cur;
          bubbleUp(cur->right);
          break;
        } else {
          q.push(cur->left);
          q.push(cur->right);
        }
      }
    }
    size++;
  }
  // To remove the root element in the heap and return it.
  T extract() {
    if (root == nullptr) throw std::runtime_error("Heap is empty");

    T max = root->data;
    if (size == 1) {
      delete root;
      root = nullptr;
    } else {
      Node* last = getLast();
      root->data = last->data;

      if (last->parent->left == last)
        last->parent->left = nullptr;
      else
        last->parent->right = nullptr;

      delete last;
      bubbleDown(root);
    }
    size--;
    return max;
  }
  // Return the number of element int the heap.
  int count() { return size; }
};