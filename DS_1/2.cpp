#include <cmath>
#include <iostream>

using namespace std;

class quadraticEq {
 public:
  // say ax^2 + bx + c = 0
  double a, b, c;

  quadraticEq(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {}

  quadraticEq operator+(quadraticEq eq) {
    return quadraticEq(a + eq.a, b + eq.b, c + eq.c);
  }

  quadraticEq operator-(quadraticEq eq) {
    return quadraticEq(a - eq.a, b - eq.b, c - eq.c);
  }

  bool operator==(quadraticEq eq) {
    return a == eq.a && b == eq.b && c == eq.c;
  }

  bool operator!=(quadraticEq eq) {
    return a != eq.a || b != eq.b || c != eq.c;
  }

  friend istream& operator>>(istream& input, quadraticEq& eq) {
    cout << "a: ";
    input >> eq.a;
    cout << "b: ";
    input >> eq.b;
    cout << "c: ";
    input >> eq.c;
    return input;
  }

  friend ostream& operator<<(ostream& output, const quadraticEq& eq) {
    output << eq.a << "x^2 + " << eq.b << "x + " << eq.c << " = 0";
    return output;
  }

  string type() const {
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
      return "two real roots";
    } else if (discriminant == 0) {
      return "single root";
    } else {
      return "two romplex roots";
    }
  }

  void root() {
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
      double root1 = (-b + sqrt(discriminant)) / (2 * a);
      double root2 = (-b - sqrt(discriminant)) / (2 * a);
      cout << "real and distinct: " << root1 << " and " << root2 << endl;
    } else if (discriminant == 0) {
      double root = -b / (2 * a);
      cout << "real and equal: " << root << endl;
    } else {
      double realPart = -b / (2 * a);
      double imaginaryPart = sqrt(-discriminant) / (2 * a);
      cout << "complex: " << realPart << " +- " << imaginaryPart << "i" << endl;
    }
  }
};

int main() {
  quadraticEq eq1, eq2;

  cout << "Enter coefficients for the first quadratic equation:" << endl;
  cin >> eq1;
  cout << "Enter coefficients for the second quadratic equation:" << endl;
  cin >> eq2;

  cout << endl;

  cout << "1st eq: " << eq1 << endl;
  cout << "Roots type: " << eq1.type() << endl;
  cout << "Roots: ";
  eq1.root();

  cout << endl;

  cout << "2nd eq: " << eq2 << endl;
  cout << "Roots type: " << eq2.type() << endl;
  cout << "Roots: ";
  eq2.root();

  cout << endl;

  quadraticEq sum = eq1 + eq2;
  cout << "Sum: " << sum << endl;

  quadraticEq diff = eq1 - eq2;
  cout << "Diff: " << diff << endl;

  cout << "The equations are " << (eq1 == eq2 ? "the same" : "different") << "."
       << endl;
  return 0;
}