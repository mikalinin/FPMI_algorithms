#include <iostream>
#include <vector>

void LSD(std::vector<unsigned long long>& elems, int elem_num) {
  const int kMax = 63;
  std::vector<std::vector<unsigned long long>> mass(
      2, std::vector<unsigned long long>());
  for (int i = 0; i <= kMax; ++i) {
    for (int j = 0; j < elem_num; ++j) {
      mass[(elems[j] >> i) % 2].push_back(elems[j]);
    }
    elems.clear();
    for (int j = 0; j < 2; ++j) {
      elems.insert(elems.end(), mass[j].begin(), mass[j].end());
      mass[j].clear();
    }
  }
}

int main() {
  int elem_num;
  std::cin >> elem_num;
  std::vector<unsigned long long> elems(elem_num);
  for (int i = 0; i < elem_num; ++i) {
    std::cin >> elems[i];
  }
  LSD(elems, elem_num);
  for (int i = 0; i < elem_num; ++i) {
    std::cout << elems[i] << '\n';
  }
  return 0;
}
