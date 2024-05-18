#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "classes/classes.hpp"

std::string getInput();
std::tuple<User, Store, Catalogue> initDefaults();
std::vector<std::string> splitString(const std::string input, const std::string delimiter);

#endif // UTILS_H
