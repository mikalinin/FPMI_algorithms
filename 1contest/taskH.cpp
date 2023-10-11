#include <iostream>
#include <vector>

int Partition(std::vector<int>& elems, int left, int right);
void QuickSort(std::vector<int>& elems, int left, int right);

void QuickSort(std::vector<int>& elems, int left, int right) {
  if (left < right) {
    int middle = 0;
    middle = Partition(elems, left, right);
    QuickSort(elems, left, middle);
    QuickSort(elems, middle + 1, right);
  }
}

int Partition(std::vector<int>& elems, int left, int right) {
  int x = elems[(left + right) / 2];
  int first_uk = left;
  int second_uk = right;
  while (first_uk <= second_uk) {
    while (elems[first_uk] < x) {
      first_uk++;
    }
    while (elems[second_uk] > x) {
      second_uk--;
    }
    if (first_uk >= second_uk) {
      break;
    }
    int buffer_elem;
    buffer_elem = elems[second_uk];
    elems[second_uk] = elems[first_uk];
    elems[first_uk] = buffer_elem;
    first_uk++;
    second_uk--;
  }
  return second_uk;
}

int main() {
  int elem_num;
  std::cin >> elem_num;
  std::vector<int> elems(elem_num);
  int new_elem;
  for (int i = 0; i < elem_num; i++) {
    std::cin >> new_elem;
    elems[i] = new_elem;
  }
  QuickSort(elems, 0, elem_num - 1);
  for (int i = 0; i < elem_num; i++) {
    std::cout << elems[i] << " ";
  }
  return 0;
}
