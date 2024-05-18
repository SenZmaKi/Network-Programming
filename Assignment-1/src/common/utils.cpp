#include "classes/classes.hpp"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

std::tuple<User, Store, Catalogue> initDefaults() {
  User user(1000);
  Store store(1000000);
  Catalogue catalogue = Catalogue::loadFromDB();
  return std::make_tuple(std::move(user), std::move(store),
                         std::move(catalogue));
}

std::string getInput() {
  std::string text;
  std::getline(std::cin, text);
  return text;
}
std::vector<std::string> splitString(const std::string input,
                                     const std::string delimiter) {
  size_t last = 0;
  size_t next = 0;
  std::vector<std::string> split;
  while ((next = input.find(delimiter, last)) != std::string::npos) {
    auto sub = input.substr(last, next - last);
    split.push_back(sub);
    last = next + delimiter.size();
  }
  auto sub = input.substr(last);
  split.push_back(sub);
  return split;
}
