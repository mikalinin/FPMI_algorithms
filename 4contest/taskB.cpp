#include <iostream>
#include <vector>

#define MOD 1000000000

class AVLtree {
  struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node() = default;

    Node(int key, Node* left, Node* right)
        : key(key), height(1), left(left), right(right) {}
  };

  std::vector<Node*> nodes_;

 public:
  Node* root = nullptr;

  int static Height(Node* node) { return node != nullptr ? node->height : 0; }

  int static BalanceFactor(Node* node) {
    return Height(node->right) - Height(node->left);
  }

  void static FixHeight(Node* node) {
    if (node != nullptr) {
      int h_left = Height(node->left);
      int h_right = Height(node->right);
      node->height = (h_left > h_right ? h_left : h_right) + 1;
    }
  }

  static Node* RotateRight(Node* node) {
    Node* new_node = node->left;
    if (new_node != nullptr) {
      node->left = new_node->right;
      new_node->right = node;
    }
    FixHeight(node);
    FixHeight(new_node);
    return new_node;
  }

  static Node* RotateLeft(Node* node) {
    Node* new_node = node->right;
    if (new_node != nullptr) {
      node->right = new_node->left;
      new_node->left = node;
    }
    FixHeight(node);
    FixHeight(new_node);
    return new_node;
  }

  static Node* Rotate(Node* node) {
    FixHeight(node);
    if (BalanceFactor(node) == -2) {
      if (node->left != nullptr && BalanceFactor(node->left) > 0) {
        node->left = RotateLeft(node->left);
      }
      return RotateRight(node);
    }
    if (BalanceFactor(node) == 2) {
      if (node->right != nullptr && BalanceFactor(node->right) < 0) {
        node->right = RotateRight(node->right);
      }
      return RotateLeft(node);
    }
    return node;
  }

  Node* Insert(Node* node, int key) {
    if (node == nullptr) {
      Node* new_node = new Node(key, nullptr, nullptr);
      nodes_.push_back(new_node);
      return new_node;
    }
    if (key < node->key) {
      node->left = Insert(node->left, key);
    } else {
      node->right = Insert(node->right, key);
    }
    return Rotate(node);
  }

  int FindLeastGreatest(Node* node, int key) {
    if (node == nullptr) {
      return -1;
    }
    if (node->key < key) {
      return FindLeastGreatest(node->right, key);
    }
    if (node->key == key) {
      return key;
    }
    int value = FindLeastGreatest(node->left, key);
    if (value == -1) {
      return node->key;
    }
    return value;
  }

  ~AVLtree() {
    for (auto& node : nodes_) {
      delete node;
    }
  }
};

int main() {
  AVLtree avl;
  int num;
  std::cin >> num;
  char query;
  int query_num;
  char last_query = '+';
  int last_ans = 0;
  for (int i = 0; i < num; ++i) {
    std::cin >> query;
    if (query == '+') {
      std::cin >> query_num;
      if (last_query == '+') {
        avl.root = avl.Insert(avl.root, query_num);
      } else {
        avl.root = avl.Insert(avl.root, (query_num + last_ans) % MOD);
      }
      last_query = '+';
      last_ans = 0;
    } else {
      std::cin >> query_num;
      int ans = avl.FindLeastGreatest(avl.root, query_num);
      std::cout << ans << '\n';
      last_query = '?';
      last_ans = ans;
    }
  }
  return 0;
}
