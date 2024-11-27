#include <iostream>
#include <stdexcept>

using namespace std;

class StackEmpty : public runtime_error {
 public:
  StackEmpty(const string& err) : runtime_error(err) {}
};

template <typename T>
class Stack {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
  };

  Node* topNode;
  int _size;

 public:
  Stack() : topNode(nullptr), _size(0) {}

  ~Stack() {
    while (!empty()) pop();
  }

  int size() const { return _size; }

  bool empty() const { return topNode == nullptr; }

  T& top() const {
    if (empty()) throw StackEmpty("StackEmpty");

    return topNode->data;
  }

  void push(const T& value) {
    topNode = new Node(value, topNode);
    ++_size;
  }

  void pop() {
    if (empty()) throw StackEmpty("StackEmpty");

    Node* oldTop = topNode;
    topNode = topNode->next;
    delete oldTop;
    --_size;
  }
};

int main() {
  Stack<int> s;
  for (int i = 1; i <= 3; i++) s.push(i);

  for (int i = 1; i <= 3; i++) {
    cout << s.top() << endl;
    s.pop();
  }  // 3 2 1

  try {
    s.pop();
  } catch (const StackEmpty& e) {
    cout << e.what() << endl;  // StackEmpty
  }

  return 0;
}
