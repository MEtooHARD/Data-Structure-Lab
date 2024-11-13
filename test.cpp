#include <stack>
#include <string>
#include <cctype>
#include <unordered_map>
#include <iostream>

using namespace std;

// Helper function to determine if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Helper function to get the precedence of an operator
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

// Function to convert infix to RPN
static stack<string> RPN(string& in) {
    stack<string> out;    // Stack for the output (RPN)
    stack<string> op;     // Stack for operators
    string operand = "";  // Temporary string to accumulate operands

    for (size_t i = 0; i < in.length(); ++i) {
        char c = in[i];

        // If the character is a space, skip it
        if (isspace(c)) continue;

        // If the character is an operand (number/variable), accumulate it
        if (isalnum(c)) {
            operand += c;  // Accumulate multi-character operands
        } else {
            if (!operand.empty()) {
                out.push(operand);  // Push the operand when finished
                operand.clear();    // Reset the operand
            }

            // If the character is an operator
            if (isOperator(c)) {
                // Pop operators with higher or equal precedence to the output
                while (!op.empty() && precedence(op.top()[0]) >= precedence(c)) {
                    out.push(op.top());
                    op.pop();
                }
                // Push the current operator to the operator stack
                op.push(string(1, c));
            }
            // If the character is a left parenthesis, push to operator stack
            else if (c == '(') {
                op.push(string(1, c));
            }
            // If the character is a right parenthesis, pop operators to output until '(' is found
            else if (c == ')') {
                while (!op.empty() && op.top() != "(") {
                    out.push(op.top());
                    op.pop();
                }
                op.pop(); // Pop the '('
            }
        }
    }

    // After the loop, if there¡¦s any remaining operand, push it to the output
    if (!operand.empty()) {
        out.push(operand);
    }

    // Pop all remaining operators to the output
    while (!op.empty()) {
        out.push(op.top());
        op.pop();
    }

    return out;
}

int main() {
    string expr = "(3 + 5) * (2 - 8)";
    stack<string> result = RPN(expr);

    // Print out the RPN result
    while (!result.empty()) {
        cout << result.top() << " ";
        result.pop();
    }
    cout << endl;

    return 0;
}
