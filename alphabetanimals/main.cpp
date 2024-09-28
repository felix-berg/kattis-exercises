#include <print>
#include <iostream>
#include <vector>
#include <unordered_map>

auto readInput() {
  struct {
    char wordEnd;
    std::vector<std::string> remainingWords;
  } result;

  std::string s;
  int N;
  std::cin >> s >> N;
  result.wordEnd = s.back();

  result.remainingWords.resize(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> result.remainingWords[i];
  }
  return result;
}

int main(int argc, char** argv)
{
  auto [ wordEnd, remainingWords ] = readInput();


  std::unordered_map<char, std::string> startingLetters;
  for (auto const& word: remainingWords) {
    startingLetters[word.front()] = word;
  }
  
  std::optional<std::string> candidate = std::nullopt, killer = std::nullopt;

  for (size_t i = 0; i < remainingWords.size(); ++i) {
    auto const& word = remainingWords[i];
    bool const startsCorrectly = word.front() == wordEnd;

    if (!startsCorrectly) continue;
    candidate = candidate.has_value() ? candidate : word;

    char end = word.back();
    if (not startingLetters.contains(end) || startingLetters.at(end) == word) {
      killer = word;
      break;
    }
  }

  if (killer.has_value()) {
    std::println("{}!", *killer);
  } else if (candidate.has_value()) {
    std::println("{}", *candidate);
  } else {
    std::println("?");
  }

  return 0;
}
