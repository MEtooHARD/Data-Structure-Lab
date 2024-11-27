#include <cstring>
#include <iostream>

#define SIZE 100

using namespace std;

class Queue {
 private:
  int data[SIZE];
  int top, bot;

 public:
  Queue() {
    top = 0;
    bot = -1;
  }

  int enqueue(int val) {
    if (cycle_1(top) == bot) return -1;

    data[top] = val;
    top = cycle_1(top);
    return 1;
  }

  int* dequeue() {
    if (cycle_1(bot) == top) return NULL;

    bot = cycle_1(bot);
    return &data[bot];
  }

  int cycle_1(int n) { return (n + 1) % SIZE; }
};

int main() {
  int data, *temp;
  char command[50];
  Queue* queue = new Queue();
  while (1) {
    cin >> command;
    if (strcmp(command, "exit") == 0) {
      break;
    } else if (strcmp(command, "enqueue") == 0) {
      cout << "Please input a integer data:";
      cin >> data;
      if (queue->enqueue(data) == 1) {
        cout << "Successfully enqueue data " << data << " into queue." << endl;
      } else {
        cout << "Failed to enqueue data into queue." << endl;
      }
    } else if (strcmp(command, "dequeue") == 0) {
      temp = queue->dequeue();
      if (temp == NULL) {
        cout << "Failed to dequeue a data from queue.\n";
      } else {
        cout << "Dequeue data " << *temp << " from queue." << endl;
      }
    }
  }
}