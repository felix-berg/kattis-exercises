#include <print>

void countingSort(std::vector<int>& vec, int min, int max) {
  std::vector<int> inp = vec;
  std::vector<int> counts(max - min);


  for (int i = 0; i < vec.size(); ++i) {
    counts[inp[i] - min]++;
  }
  
  for (int i = 1; i < max - min; ++i) {
    counts[i] = counts[i - 1] + counts[i];
  }

  int k = 0;
  for (int i = 0; i < max - min; ++i) {
    while (k <= counts[i]) {
      vec[k++] = i;
    }
  }
}

int main(int argc, char** argv)
{
  
  return 0;
}
