#include <iostream>
#include <vector>

int main() {
  const int kTwo = 2;
  int elem_num;
  std::cin >> elem_num;
  std::vector<unsigned long long> elems(elem_num);
  for (int i = 0; i < elem_num; ++i) {
    std::cin >> elems[i];
  }
  const int kMax = 63;
  std::vector<std::vector<unsigned long long>> mass(
      kTwo, std::vector<unsigned long long>());
  for (int i = 0; i <= kMax; ++i) {
    for (int j = 0; j < elem_num; ++j) {
      mass[(elems[j] >> i) % kTwo].push_back(elems[j]);
    }
    elems.clear();
    for (int j = 0; j < kTwo; ++j) {
      elems.insert(elems.end(), mass[j].begin(), mass[j].end());
      mass[j].clear();
    }
  }
  for (int i = 0; i < elem_num; ++i) {
    std::cout << elems[i] << '\n';
  }
  return 0;
}
