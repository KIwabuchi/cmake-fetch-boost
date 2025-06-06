#include <iostream>

#include <boost/container/string.hpp>
#include <boost/json.hpp>

int main() {
  boost::container::string str("Hello, World!");
  std::cout << str << std::endl;

  boost::json::value jv = {{"key", "value"}};
  std::cout << jv << std::endl;

  return 0;
}