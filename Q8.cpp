#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid {
 private:
  Grid *dir[4];
  int state;

 public:
  Grid() : Grid(0) {}
  Grid(int s) {
    state = s;
    dir[UP] = NULL;
    dir[DOWN] = NULL;
    dir[LEFT] = NULL;
    dir[RIGHT] = NULL;
  }
  Grid *getDir(int d) { return dir[d]; }
  int getState() { return state; }
  void setDir(int d, Grid *g) { dir[d] = g; }
  void setState(int s) { state = s; }
};

struct List {
 private:
  Grid *data[SIZE * SIZE];
  int top;

 public:
  List() { top = 0; }
  /*
  Insert an element from top
  */
  void addElement(Grid *g) { data[top++] = g; }
  /*
  remove an element from top and return a pointer point to the element.
  If list is empty, return NULL.
  */
  Grid *removeElement() { return top == 0 ? NULL : data[--top]; }
  void printPath() {
    for (int j = top - 2; j >= 0; j--) {
      if (data[j] == data[j + 1]->getDir(UP)) {
        cout << "UP\n";
      } else if (data[j] == data[j + 1]->getDir(DOWN)) {
        cout << "DOWN\n";
      } else if (data[j] == data[j + 1]->getDir(LEFT)) {
        cout << "LEFT\n";
      } else if (data[j] == data[j + 1]->getDir(RIGHT)) {
        cout << "RIGHT\n";
      }
    }
  }
};

class Maze {
 private:
  Grid *maze;
  Grid *end;

 public:
  Maze() { initMaze(SIZE); }
  /*
  function initMaze
  Alocate a 2-D link list with s * s sizes as the map of maze.
  Inside the maze enery gird with state 0 represent empty space and 1 represent
  wall. The gird in left top is start point and right bottom is finish point.
  Randomly generate 20% wall in the maze.
  Make sure start point and finish point are 0

  動態配置一個二維的鏈結串列，大小是 s * s，用這個鏈結串列表示迷宮的地圖
  節點中 0 的值表示可以移動的空間， 1 表示牆壁
  左上角的位置表示起點，右下角的位置表示終點
  請在迷宮中加入 20% 的牆壁
  然後確定起點跟終點都是可以移動的位置
  */
  void initMaze(int s) {
    Grid *temp[s][s];

    for (int x = 0; x < s; x++) {
      for (int y = 0; y < s; y++) {
        temp[x][y] = new Grid();

        if (x > 0) {
          temp[x - 1][y]->setDir(RIGHT, temp[x][y]);
          temp[x][y]->setDir(LEFT, temp[x - 1][y]);
        }
        if (y > 0) {
          temp[x][y - 1]->setDir(DOWN, temp[x][y]);
          temp[x][y]->setDir(UP, temp[x][y - 1]);
        }
      }
    }
    maze = temp[0][0];
    end = temp[s - 1][s - 1];

    srand(time(0));
    int totalCells = s * s;
    int numWalls = totalCells * 0.2;
    while (numWalls-- > 0) {
      int x = std::rand() % s;
      int y = std::rand() % s;

      if ((x != 0 || y != 0) && (x != s - 1 || y != s - 1) &&
          temp[x][y]->getState() == 0)
        temp[x][y]->setState(1);
    }
  }
  bool markPath(Grid *target, List *path) {
    if (target == end) {
      target->setState(-1);
      path->addElement(target);
      return true;
    }

    if (target == NULL) return false;

    if (target->getState() != 0) return false;

    target->setState(-1);
    if (markPath(target->getDir(UP), path) ||
        markPath(target->getDir(RIGHT), path) ||
        markPath(target->getDir(DOWN), path) ||
        markPath(target->getDir(LEFT), path)) {
      path->addElement(target);
      return true;
    }

    target->setState(0);
    if (target != end) path->removeElement();

    return false;
  }

  List *getPath() {
    List *path = new List();
    if (maze == NULL) return path;

    markPath(maze, path);
    return path;
  }

  void printMaze() {
    Grid *j = maze, *k;
    while (j != NULL) {
      k = j;
      while (k != NULL) {
        cout << k->getState();
        k = k->getDir(RIGHT);
      }
      cout << endl;
      j = j->getDir(DOWN);
    }
  }
};

int main() {
  Maze *maze = new Maze();
  maze->printMaze();
  maze->getPath()->printPath();
}
