#include "../common/common.hpp"
#include <functional>
#include <iostream>
#include <ostream>
#include <string>

void displayCatalogue(std::string booksStr) {
  std::cout << booksStr << std::endl;
}

int main() {
  User user(1000);
  Store store(1000000);
  Catalogue catalogue = Catalogue::loadFromDB();

  auto display = std::bind(&Catalogue::display, &catalogue);
  auto purchaseBook = [&] { return catalogue.purchaseBook(&user); };
  auto search =
      std::bind(&Catalogue::search, &catalogue, std::placeholders::_1);
  auto payForBook = [&](int bookNumber) {
    return catalogue.payForBook(bookNumber, &user, &store);
  };

  cli(display, search, purchaseBook, payForBook);
}
