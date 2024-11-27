#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TrieNode {
  friend class Trie;
  vector<TrieNode*> child;
  char content;
  bool end = false;
  bool has(char ch) {
    for (TrieNode* node : child)
      if (node->content == ch) return true;
    return false;
  }

  int posOf(char ch) {
    for (int i = 0; i < child.size(); i++)
      if (child[i]->content == ch) return i;
    return -1;
  }

  TrieNode* get(char ch) {
    for (TrieNode* node : child)
      if (node->content == ch) return node;
    return nullptr;
  }

  TrieNode(char c) : content(c) {}
};

class Trie {
  TrieNode* root = nullptr;

 public:
  Trie() {};
  /*
  search trie for key, return true if exist, false if not.
  */
  bool search(string key) {
    TrieNode* node = root;
    for (int i = 0; i < key.length(); i++) {
      int pos = node->posOf(key[i]);
      if (pos == -1) return false;
      node = node->child[pos];
    }

    return node->end;
  }
  /*
  insert value into trie.
  */
  void insert(string value) {
    if (root == nullptr) root = new TrieNode('\0');

    TrieNode* node = root;
    for (int i = 0; i < value.length(); i++) {
      if (!node->has(value[i])) node->child.push_back(new TrieNode(value[i]));
      node = node->get(value[i]);
    }

    node->end = true;
  }
  /*
  display trie in pre-order, each element in a line, display space befoer
  element base on the level of 	the element. level 1 for 2 space, level 2 for 4
  space, level 3 for 6 space and so on, root is level 	0.
  */
  void preorder() {
    cout << "[]";
    for (TrieNode* n : root->child) preorder(n, 1, true);
    cout << endl;
  }

  void preorder(TrieNode* n, int level, bool next_line) {
    if (next_line) {
      cout << endl;
      for (int i = 0; i < level; i++) cout << "  ";

      next_line = false;
    }

    cout << n->content;
    if (n->child.empty()) return;

    if (n->end || n->child.size() > 1) {
      next_line = true;
      level++;
    }
    for (int i = 0; i < n->child.size(); i++)
      preorder(n->child[i], level, next_line);
  }
};

int main() {
  Trie* trie = new Trie();
  string command, key, value;
  while (1) {
    cin >> command;
    if (command == "insert") {
      cin >> value;
      trie->insert(value);
    } else if (command == "search") {
      cin >> key;
      if (trie->search(key))
        cout << "exist" << endl;
      else
        cout << "not exist" << endl;
    } else if (command == "print") {
      trie->preorder();
    } else if (command == "exit") {
      break;
    }
  }
}
