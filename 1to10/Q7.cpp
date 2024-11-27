#include <cstdlib>
#include <ctime>
#include <iostream>

#define SIZE 10

using namespace std;

void allocArray(int ***p, int m, int n) {
  *p = (int **)malloc(m * sizeof(int *));

  int *data = (int *)malloc(m * n * sizeof(int));

  for (int i = 0; i < m; i++) (*p)[i] = &data[i * n];
}

class Node {
 private:
  int col, row;

 public:
  Node() : Node(0, 0) {};
  Node(int r, int c) {
    row = r;
    col = c;
  }
  int getRow() { return row; }
  int getCol() { return col; }
  void setRow(int r) {
    if (r >= 0 && r < SIZE) row = r;
  }
  void setCol(int c) {
    if (c >= 0 && c < SIZE) col = c;
  }
};

class List {
 private:
  Node data[SIZE * SIZE];
  int top;

 public:
  List() { top = 0; }
  /*
  function addElement
  Insert an element from list
  */
  void addElement(int r, int c) { data[top++] = Node(r, c); }
  /*
  function removeElement
  remove an element from list and return a pointer point to the element.
  If list is empty, return NULL.
  */
  Node *removeElement() { return top == 0 ? NULL : &data[--top]; }
  void printList() {
    for (int j = 0; j < top; j++) {
      cout << "(" << data[j].getRow() << ", " << data[j].getCol() << ")"
           << endl;
    }
  }
  int getTop() { return top; }

  void reset() { top = 0; }
};

class Maze {
 private:
  int **maze;
  int size = SIZE;

 public:
  Maze() { initMaze(SIZE); }
  /*
  function initMaze
  Alocate a 2-D array with s * s sizes as the map of maze.
  Inside the maze where 0 represent empty space and 1 represent wall.
  [0][0] is start point and [s - 1][s - 1] is finish point.
  Randomly generate 20% wall in the maze.
  Make sure [0][0] and [s - 1][s - 1] are 0

  動態配置一個二維的陣列，大小是 s * s ，用這個陣列表示迷宮的地圖
  陣列中 0 的值表示可以移動的空間， 1 表示牆壁
  [0][0] 的位置表示起點 [s - 1][s - 1] 的位置表示終點
  請在迷宮中加入 20% 的牆壁
  然後確定起點跟終點都是可以移動的位置
  */
  void initMaze(int s) {
    allocArray(&maze, s, s);

    for (int i = 0; i < s; ++i)
      for (int j = 0; j < s; ++j) maze[i][j] = 0;

    srand(time(0));

    int totalCells = s * s;
    int numWalls = totalCells * 0.2;

    while (numWalls-- > 0) {
      int x = std::rand() % s;
      int y = std::rand() % s;

      if ((x != 0 || y != 0) && (x != s - 1 || y != s - 1) && maze[x][y] == 0)
        maze[x][y] = 1;
    }
  }

  bool markPath(int row, int col) {
    // Check if we reached the end of the maze
    if (row == size - 1 && col == size - 1) {
      maze[row][col] = -1;  // Mark the end point
      return true;
    }
    // Check if the current position is valid
    if (row < 0 || row >= size || col < 0 || col >= size ||
        maze[row][col] != 0) {
      return false;  // Out of bounds or wall
    }
    // Mark the current cell as part of the path
    maze[row][col] = -1;

    // Try to move in each direction: up, right, down, left
    if (markPath(row - 1, col)) return true;  // Up
    if (markPath(row, col + 1)) return true;  // Right
    if (markPath(row + 1, col)) return true;  // Down
    if (markPath(row, col - 1)) return true;  // Left

    // Unmark the cell if no path was found from here (backtrack)
    maze[row][col] = 0;
    return false;  // No path found
  }

  List *getPath() {
    List *path = new List();
    if (maze == NULL) {
      return path;
    }
    bool has_route = markPath(0, 0);
    // cout << "==================================\n";
    // printMaze();
    if (has_route) {
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          if (maze[i][j] == -1) {
            path->addElement(i, j);
          }
        }
      }
    }
    return path;
  }

  void printMaze() {
    int j, k;
    // int **temp[10];
    // temp = &maze;
    for (j = 0; j < SIZE; j++) {
      for (k = 0; k < SIZE; k++) {
        if (maze[j][k] == 0)
          cout << " ";
        else if (maze[j][k] == 1)
          cout << "*";
      }
      cout << "\n";
    }
  }
};

int main() {
  Maze *maze = new Maze();
  maze->printMaze();
  maze->getPath()->printList();
}
