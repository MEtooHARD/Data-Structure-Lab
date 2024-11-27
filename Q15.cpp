#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SuffixTreeNode {
  friend class SuffixTree;
  vector<SuffixTreeNode *> children;
  int start, end, count;
  char text;

 public:
  SuffixTreeNode(int start, int end, char text)
      : start(start), end(end), text(text), count(0) {}

  int find(char ch) {
    for (int i = 0; i < children.size(); i++)
      if (children[i]->text == ch) return i;

    return -1;
  }
};

class SuffixTree {
 private:
  SuffixTreeNode *root;
  std::string text;
  int size;

  void insertSuffix(int &suffixStart) {
    SuffixTreeNode *node = root;

    for (int idx = suffixStart; idx < text.length(); idx++) {
      char ch = text[idx];
      int chPos = node->find(ch);
      if (chPos == -1) {
        node->children.push_back(new SuffixTreeNode(idx, text.length(), ch));
        chPos = node->children.size() - 1;
      }

      node = node->children[chPos];
      node->count++;
    }
  }

 public:
  SuffixTree(const std::string &text) : text(text), size(text.size()) {
    root = new SuffixTreeNode(-1, -1, '\u200b');
    for (int i = 0; i < text.length(); i++) insertSuffix(i);
  }

  bool exist(const std::string &substring) {
    SuffixTreeNode *current = root;

    for (int i = 0; i < substring.length(); i++) {
      char ch = substring[i];
      int index = current->find(ch);
      if (index == -1) return false;

      current = current->children[index];
    }

    return true;
  }

  int count(const std::string &substring) {
    SuffixTreeNode *current = root;

    for (int i = 0; i < substring.length(); i++) {
      char ch = substring[i];
      int index = current->find(ch);
      if (index == -1) return 0;

      current = current->children[index];
    }

    return current->count;
  }
};

int main() {
  std::string text = "";
  while (true) {
    std::string temp;
    getline(std::cin, temp);
    if (temp == "") break;
    text += temp;
  }
  SuffixTree tree("abcabcabc");

  std::string query;
  while (true) {
    getline(std::cin, query);
    if (query == "") break;
    std::cout << "Existence of '" << query
              << "': " << (tree.exist(query) ? "Yes" : "No") << std::endl;
    std::cout << "Count of '" << query << "': " << tree.count(query)
              << std::endl;
  }
  return 0;
}