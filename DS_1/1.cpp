#include <ctime>
#include <iostream>

using namespace std;

class A {
 public:
  int x;
};

class B : public A {
 public:
  int x;
};

class C : B {
 public:
  int x;
  void change_A_x() { A::x = rand(); };
  void showX() { cout << A::x << ' ' << B::x << ' ' << C::x << '\n'; }
};

int main() {
  srand(time(NULL));

  C c;

  c.showX();
  c.change_A_x();
  c.showX();
};
