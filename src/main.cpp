#include <iostream>
#include <neither/either.hpp>

int main() {

  std::cout << "This is an example of Buck's cells feature. " << std::endl;

  auto i = neither::Either<int, std::string>::leftOf(21);
  auto j = i.leftMap([](auto x) { return x * 2; })
    .rightMap([](auto x) { return x.size(); })
    .join();

  std::cout << j << std::endl;

  return 0;
}
