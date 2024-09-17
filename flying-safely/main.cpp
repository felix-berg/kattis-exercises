#include <print>
#include <iostream>
#include <vector>

struct Flight {
  int start, end, day, passengers;
};



auto readInput() {
  struct {
    int numAirports, numDays;
    std::vector<Flight> flights;
    std::vector<std::vector<int>> customersLeaving;
  } result {};

  int numFlights;
  std::cin >> result.numAirports >> result.numDays >> numFlights;

  result.flights.resize(numFlights);
  result.customersLeaving.resize(result.numAirports);
  for (int i = 0; i < result.numAirports; ++i) {
    result.customersLeaving[i].resize(result.numDays);
  }
  
  for (int i = 0; i < numFlights; ++i) {
    std::cin >> result.flights[i].start
             >> result.flights[i].end
             >> result.flights[i].day
             >> result.flights[i].passengers;

    result.flights[i].start -= 1;
    result.flights[i].end -= 1;
    result.flights[i].day -= 1;
  }

  for (int i = 0; i < result.numAirports; ++i) {
    for (int j = 0; j < result.numDays; ++j) {
      int a, b;
      std::cin >> a >> b;
      a = a - 1;
      b = b - 1;
      std::cin >> result.customersLeaving[a][b];
    }
  }

  return result;
}

int main(int argc, char** argv)
{
  auto [ nAirports, nDays, flights, costumersLeaving ] = readInput();

  // for (Flight f: flights) {
  //   std::println("({}, {}, {}, {})", f.start, f.end, f.day, f.passengers);
  // }
  //
  // for (int a = 0; a < nAirports; ++a) {
  //   for (int d = 0; d < nDays; ++d) {
  //     std::println("Airport {} day {}: {} costumers", a, d, costumersLeaving[a][d]);
  //   }
  // }

  for (int a = 0; a < nAirports; ++a) {
    costumersLeaving[a].push_back(0);
  }

  bool optimal = true;
  for (int d = 0; d < nDays; ++d) {
    for (int a = 0; a < nAirports; ++a) {
      for (Flight f: flights) {
        if (f.start != a || f.day != d) continue;

        if (costumersLeaving[a][d] < f.passengers) {
          optimal = false;
          break;
        }

        costumersLeaving[a][d] -= f.passengers;
        costumersLeaving[f.end][d + 1] += f.passengers;
      }
      
      costumersLeaving[a][d + 1] += costumersLeaving[a][d];
    }
  }

  std::println("{}", optimal ? "optimal" : "suboptimal");

  return 0;
}
