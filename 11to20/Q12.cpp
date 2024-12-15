#include <cctype>
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
using namespace std;

class ExpressionTree {
 private:
  struct Node {
    std::string value;
    Node* left;
    Node* right;

    Node(const std::string& val) : value(val), left(nullptr), right(nullptr) {}
  };

  Node* root;

  static bool isOp(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
  }

  static bool isNum(char ch) { return (ch >= '0' && ch <= '9'); }

  static bool isNum(const string& n) {
    return !n.empty() &&
           (isdigit(n[0]) || (n[0] == '-' && n.size() > 1 && isdigit(n[1])));
  }

  static string getNumStr(int& index, const string& exp) {
    string num;
    if (exp[index] == '-') {
      num += exp[index];
      index++;
    }
    while (index < exp.size() && isNum(exp[index])) {
      num += exp[index];
      index++;
    }
    return num;
  }

  static int priority(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%") return 2;
    return 0;
  }

  static void add_op(const string& op, stack<string>& ops, queue<string>& out) {
    while (!ops.empty() && ops.top() != "(" &&
           priority(ops.top()) >= priority(op)) {
      out.push(ops.top());
      ops.pop();
    }
    ops.push(op);
  }

  static queue<string> RPN(const string& expression) {
    int index = 0;
    stack<string> ops;
    queue<string> out;

    while (index < expression.size()) {
      if (isNum(expression[index])) {
        out.push(getNumStr(index, expression));
      } else if (expression[index] == '-') {
        if (index < expression.size() - 1 && isNum(expression[index + 1])) {
          out.push(getNumStr(index, expression));
        } else {
          add_op(expression.substr(index, 1), ops, out);
          index++;
        }
      } else if (isOp(expression[index])) {
        add_op(expression.substr(index, 1), ops, out);
        index++;
      } else if (expression[index] == '(') {
        ops.push("(");
        index++;
      } else if (expression[index] == ')') {
        while (!ops.empty() && ops.top() != "(") {
          out.push(ops.top());
          ops.pop();
        }
        if (!ops.empty()) ops.pop();  // the '('
        index++;
      } else {
        index++;
      }
    }
    while (!ops.empty()) {
      out.push(ops.top());
      ops.pop();
    }

    return out;
  }

  void buildTree(queue<string>& out) {
    stack<Node*> tree;

    while (!out.empty()) {
      if (isNum(out.front())) {
        tree.push(new Node(out.front()));
      } else if (isOp(out.front()[0])) {
        Node* node = new Node(out.front());
        if (tree.size() < 2) throw runtime_error("Invalid expression");
        node->right = tree.top();
        tree.pop();
        node->left = tree.top();
        tree.pop();
        tree.push(node);
      }
      out.pop();
    }

    root = tree.empty() ? nullptr : tree.top();
  }

  void InOrder(Node* node) {
    if (node == nullptr) return;
    if (node->left) cout << "(";
    InOrder(node->left);
    cout << node->value << " ";
    InOrder(node->right);
    if (node->right) cout << ")";
  }

  void PreOrder(Node* node) {
    if (node == nullptr) return;
    cout << node->value << " ";
    PreOrder(node->left);
    PreOrder(node->right);
  }

  void PostOrder(Node* node) {
    if (node == nullptr) return;
    PostOrder(node->left);
    PostOrder(node->right);
    cout << node->value << " ";
  }

  int evaluate(Node* node) {
    if (isNum(node->value)) return stoi(node->value);

    int leftEval = evaluate(node->left);
    int rightEval = evaluate(node->right);

    if (node->value == "+") return leftEval + rightEval;
    if (node->value == "-") return leftEval - rightEval;
    if (node->value == "*") return leftEval * rightEval;
    if (node->value == "/") return leftEval / rightEval;
    if (node->value == "%") return leftEval % rightEval;
  }

 public:
  ExpressionTree(const std::string& expression) {
    queue<string> rpnQueue = RPN(expression);
    buildTree(rpnQueue);
  }

  ~ExpressionTree() { deleteTree(root); }

  void deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }

  void printInOrder() {
    InOrder(root);
    cout << endl;
  }

  void printPreOrder() {
    PreOrder(root);
    cout << endl;
  }

  void printPostOrder() {
    PostOrder(root);
    cout << endl;
  }

  int eval() {
    if (!root) throw runtime_error("Cannot evaluate an empty expression tree.");
    return evaluate(root);
  }
};

int main() {
  std::string infix;
  getline(cin, infix);  // Use getline to allow spaces

  ExpressionTree exprTree(infix);

  cout << "Inorder: ";
  exprTree.printInOrder();
  cout << "Preorder: ";
  exprTree.printPreOrder();
  cout << "Postorder: ";
  exprTree.printPostOrder();
  cout << "Evaluated result: " << exprTree.eval() << endl;

  return 0;
}
