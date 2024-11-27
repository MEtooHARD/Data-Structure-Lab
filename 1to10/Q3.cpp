#include <cstring>
#include <iostream>

#define SIZE 100

using namespace std;

class Stack {
 private:
  int data[SIZE];
  int top;

 public:
  Stack() { top = 0; }
  int push(int data) {
    if (top > SIZE) {
      return -1;
    } else {
      this->data[top++] = data;
      return 1;
    }
  }

  int *pop() { return top == 0 ? NULL : &(this->data[top--]); }
};

int main() {
  int data, *temp;
  char command[50];
  Stack *stack = new Stack();
  while (1) {
    cin >> command;
    if (strcmp(command, "exit") == 0) {
      break;
    } else if (strcmp(command, "push") == 0) {
      cout << "Please input a integer data:";
      cin >> data;
      if (stack->push(data) == 1) {
        cout << "Successfully push data " << data << " into stack.\n";
      } else {
        cout << "Failed to push data into stack.\n";
      }
    } else if (strcmp(command, "pop") == 0) {
      temp = stack->pop();
      if (temp == NULL) {
        cout << "Failed to pop a data from stack.\n";
      } else {
        cout << "Pop data " << *temp << " from stack.\n" << endl;
      }
    }
  }
}
