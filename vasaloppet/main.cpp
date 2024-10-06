#include <cassert>
#include <limits>
#include <print>
#include <iostream>
#include <algorithm>
#include <vector>

struct Interval {
  int from, to;
};

auto readInput() {
  struct {
    std::vector<Interval> intervals;
    int tripTime;
    int maxTime;
  } result;
  int n;
  std::cin >> n >> result.maxTime >> result.tripTime;


  result.intervals.resize(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> result.intervals[i].from;
    std::cin >> result.intervals[i].to;
  }

  return result;
}

int static constexpr NO_MATCH = -1;
std::vector<int> computeMatches(std::vector<Interval> const& intervals, int tripTime, int maxTime) {
  assert(not intervals.empty());
  std::vector<int> matches(intervals.size(), NO_MATCH);

  auto const l = [&intervals](int i) { 
    if (i >= intervals.size()) 
      return std::numeric_limits<int>::max();
    return intervals[i].from;
  };

  auto const r = [&intervals](int i) { 
    if (i >= intervals.size()) 
      return std::numeric_limits<int>::max();
    return intervals[i].to;
  };

  int i = 0, j = 0;
  // inv.: [li, li + tripTime) contains all [lj', rj') for j' = [i, j)
  while (i < intervals.size()) {
    if (l(i) + tripTime > maxTime) {
      break; // all will have no match
    }

    // if [li, li + tripTime) 
    if (l(i) + tripTime >= r(j)) { 
      // [li, li + tripTime) contains [lj, rj)
      ++j; // keep looking
    } else if (l(i) + tripTime > l(j)) {
      // [li, li + tripTime) intersects with [lj, rj) ≈ 'match'
      matches[i] = j;
      ++i;
    } else {
      // l(i) + tripTime <= l(j + 1), so pick [l(j - 1), r(j - 1))
      matches[i] = j - 1;
      ++i;
    }
  }

  return matches;
}

// compute S[i] = amount of space in [0, li) with no other interval
// S[N] = total amount of wasted space
std::vector<int> computePreceedingSpace(
  std::vector<Interval> const& intervals,
  int maxTime
) {
  assert(not intervals.empty());

  std::vector<int> space(intervals.size() + 1);
  space[0] = intervals[0].from;

  int i;
  for (i = 1; i < intervals.size(); ++i) {
    space[i] = space[i - 1] + intervals[i].from - intervals[i - 1].to;
  }

  // i is intervals.size()
  space[i] = space[i - 1] + (maxTime - intervals[i - 1].to);

  return space;
}

std::vector<int> computeWaste(
  std::vector<Interval> const& intervals,
  std::vector<int> const& matches,
  std::vector<int> const& space,
  int tripTime
) {
  std::vector<int> waste(intervals.size(), std::numeric_limits<int>::max());
  int N = intervals.size();

  for (int i = 0; i < intervals.size(); ++i) {
    int j = matches[i];
    if (j == NO_MATCH) {
      break;
    }
    assert(j < intervals.size());

    int spaceBetweenIJ = space[j] - space[i];
    // if li + tripTime > r(j), then there is some left over space
    int leftOver = std::max(0, intervals[i].from + tripTime - intervals[j].to);
    waste[i] = spaceBetweenIJ + leftOver;
  }

  return waste;
}

void insertIntervalIfDisjoint(std::vector<Interval>& intervals, Interval i) {
  assert(not intervals.empty());

  auto cmp = [](const auto& a, const auto& b) {
    return a.from < b.from;
  };

  // already exists interval with this start time
  if (std::ranges::binary_search(intervals, i, cmp))
    return;

  auto pos = std::ranges::lower_bound(intervals, i, cmp);

  if (pos == intervals.end()) {
    if (std::prev(pos)->to > i.from) 
      return;

    intervals.insert(pos, i);
    return;
  }

  if (i.to > pos->from) 
    return; // not disjoint
  
  intervals.insert(pos, i);
}

int main(int argc, char** argv)
{
  auto [ intervals, tripTime, maxTime ] = readInput();

  if (intervals.empty()) {
    std::println("{}", tripTime);
    return 0;
  }

  // make choosing [T - S, T) (as late as possible) 
  // viable by creating empty ad break [T - S, T - S)
  insertIntervalIfDisjoint(intervals, Interval {
    maxTime - tripTime, maxTime - tripTime
  });

  auto matches = computeMatches(intervals, tripTime, maxTime);
  auto space = computePreceedingSpace(intervals, maxTime);
  auto waste = computeWaste(intervals, matches, space, tripTime);

  std::println("{}", *std::ranges::min_element(waste));

  return 0;
}
