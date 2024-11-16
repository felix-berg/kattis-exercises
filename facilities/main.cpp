#include <print>
#include <queue>
#include <algorithm>
#include <vector>
#include <queue>
#include <algorithm>

namespace sr = std::ranges;

struct Interval {
  int from, to;
};

auto readInput() {
  struct {
    std::vector<Interval> intervals;
    int closingTime;
  } result;

  int n;
  std::scanf("%d %d\n", &n, &result.closingTime);

  result.intervals.reserve(n);
  for (int i = 0; i < n; ++i) {
    int b, d;
    std::scanf("%d %d\n", &b, &d);

    for (int t = b; t < result.closingTime; t += b + d) {
      result.intervals.emplace_back(
        t, 
        std::min(t + d, result.closingTime)
      );
    }
  }

  return result;
}

int main(int argc, char** argv)
{
  auto [ intervals, closingTime ] = readInput();

  const auto intervalToString = [](Interval const& i) { 
    return std::format("[{}, {})", i.from, i.to);
  };

  using MinEndTime = decltype([](auto const& a, auto const& b) {
    return a.to > b.to;
  });

  // sort intervals based on start time
  sr::sort(intervals, [](auto const& a, auto const& b) { return a.from < b.from; });

  // make a priority queue of 'current' activities, sorted on earliest end time
  std::priority_queue<Interval, std::vector<Interval>, MinEndTime> endQueue;

  int numRestroomsNeeded = 0;
  for (int i = 0; i < intervals.size(); ++i) {
    // consider ith activity
    Interval inv = intervals[i];

    bool foundRestroom = false;
    if (not endQueue.empty()) {
      // the interval with earliest end time
      Interval last = endQueue.top();
      if (inv.from >= last.to) { // if compatible, 'append' inv to restroom schedule
        endQueue.pop();
        endQueue.push(inv);
        foundRestroom = true;
      }
    }
    
    if (not foundRestroom) {
      // make new restroom for activity i
      numRestroomsNeeded++;
      endQueue.push(inv);
    }
  }

  std::println("{}", numRestroomsNeeded);

  return 0;
}
