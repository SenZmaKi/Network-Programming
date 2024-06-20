#include "../common/common.hpp"
#include <functional>

int main() {

  auto [user, store, catalogue] = initDefaults();
  auto display = std::bind(&Catalogue::display, &catalogue);
  auto purchaseBook = [&] { return catalogue.purchaseBook(&user); };
  auto search =
      std::bind(&Catalogue::search, &catalogue, std::placeholders::_1);
  auto payForBook = [&](int bookNumber) {
    return catalogue.payForBook(bookNumber, &user, &store);
  };
  auto exit = [] {};
  cli(display, search, purchaseBook, payForBook, exit);
}
