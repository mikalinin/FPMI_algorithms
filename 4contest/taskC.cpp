#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Pair {
  std::string first;
  std::string second;
};

struct Nodee {
  Pair key;
  int height;
  Nodee* left;
  Nodee* right;

  Nodee() = default;

  Nodee(Pair key, Nodee* left, Nodee* right)
      : key(std::move(key)), height(1), left(left), right(right) {}
};

class AVLtree {
  std::vector<Nodee*> nodes_;

 public:
  Nodee* root = nullptr;

  int static Height(Nodee* node) { return node != nullptr ? node->height : 0; }

  int static BalanceFactor(Nodee* node) {
    return Height(node->right) - Height(node->left);
  }

  void static FixHeight(Nodee* node) {
    if (node != nullptr) {
      int h_left = Height(node->left);
      int h_right = Height(node->right);
      node->height = (h_left > h_right ? h_left : h_right) + 1;
    }
  }

  static Nodee* RotateRight(Nodee* node) {
    Nodee* new_node = node->left;
    if (new_node != nullptr) {
      node->left = new_node->right;
      new_node->right = node;
    }
    FixHeight(node);
    FixHeight(new_node);
    return new_node;
  }

  static Nodee* RotateLeft(Nodee* node) {
    Nodee* new_node = node->right;
    if (new_node != nullptr) {
      node->right = new_node->left;
      new_node->left = node;
    }
    FixHeight(node);
    FixHeight(new_node);
    return new_node;
  }

  static Nodee* Rotate(Nodee* node) {
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

  Nodee* Insert(Nodee* node, const Pair& key) {
    if (node == nullptr) {
      Nodee* new_node = new Nodee(key, nullptr, nullptr);
      nodes_.push_back(new_node);
      return new_node;
    }
    if (key.first < node->key.first) {
      node->left = Insert(node->left, key);
    } else {
      node->right = Insert(node->right, key);
    }
    return Rotate(node);
  }

  Nodee* Find(Nodee* node, const std::string& key) {
    if (node == nullptr || node->key.first == key) {
      return node;
    }
    if (node->key.first > key) {
      return Find(node->left, key);
    }
    return Find(node->right, key);
  }

  ~AVLtree() {
    for (auto& node : nodes_) {
      delete node;
    }
  }
};

int main() {
  AVLtree mans;
  AVLtree cars;
  int num;
  std::cin >> num;
  std::string man;
  std::string car;
  for (int i = 0; i < num; ++i) {
    std::cin >> man >> car;
    mans.root = mans.Insert(mans.root, Pair(man, car));
    cars.root = cars.Insert(cars.root, Pair(car, man));
  }
  int query_num;
  std::cin >> query_num;
  std::string query;
  for (int i = 0; i < query_num; ++i) {
    std::cin >> query;
    Nodee* ans = mans.Find(mans.root, query);
    if (ans == nullptr) {
      ans = cars.Find(cars.root, query);
    }
    std::cout << ans->key.second << '\n';
  }
  return 0;
}
