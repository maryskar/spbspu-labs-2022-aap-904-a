#include <iostream>
#include <limits>
#include <stdexcept>
#include "counter.hpp"

int main()
{
  const int minInt = std::numeric_limits< int >::min();
  int val = 0;
  zasulsky::SecondLargestFinder findSecondLargest {0, minInt};
  zasulsky::FibonacciCounter countFibonacci {0, 0, 0};
  do {
    std::cin >> val;
    if (!std::cin) {
        std::cout << "Input error\n";
        return 1;
    }
    try {
      countFibonacci(val);
      findSecondLargest(val);
    } catch (const std::overflow_error& e) {
      std::cout << e.what() << '\n';
      return 2;
    } catch (const std::logic_error& e) {
      std::cout << e.what() << '\n';
      return 3;
    }
  } while (std::cin && val != 0);
  std::cout << "Second largest value " << findSecondLargest.secondLargestVal << '\n'
            << "Fibonacci number count " << countFibonacci.count << '\n';
}
