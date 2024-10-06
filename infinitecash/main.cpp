#include <print>
#include <cassert>

static constexpr size_t LEN = 1000;
struct Number {
  std::array<bool, LEN> data;
  size_t front, back;
};

bool& get(Number& num, size_t i) {
  return num.data[(num.front + i) % LEN];
}

const bool& get(Number const& num, size_t i) {
  return get(num, i);
}

void push_back(Number& num, bool b) {
  int old = num.back;
  num.back = (num.back + 1) % LEN;
  num.data[old] = b;
}

void push_front(Number& num, bool b) {
  num.front = (num.front + LEN - 1) % LEN;
  num.data[num.front] = b;
}

void pop_back(Number& num) {
  num.back = (num.back + LEN - 1) % LEN;
}

size_t num_bits(Number const& n) {
  if (n.front <= n.back)
    return n.back - n.front;
  else 
    return n.back + LEN - n.front;
} 

void decr(Number& num) {
  for (int i = num_bits(num) - 1; i >= 0; --i) {
    if (get(num, i) == 0) {
      get(num, i) = 1;
    } else {
      get(num, i) = 0;
      break;
    }
  }
}

void shiftr(Number& num) {
  pop_back(num);
}

void add(Number& a, Number const& b) {
  for (int i = 0; i < 1 + num_bits(b) - num_bits(a); ++i) {
    push_front(a, 0);
  }

  bool carr = 0;
  for (int i = num_bits(a) - 1; i >= 0; --i) {
    int tal = carr + get(a, i) + get(b, i);
  }
}

int main(int argc, char** argv)
{
  return 0;
}
