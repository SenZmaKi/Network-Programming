#include "../common/lib.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>

int main() {
  User user(1000);
  Store store(1000000);
  Catalogue catalogue = Catalogue::loadFromDB();
  std::cout << "Welcome to Chambua Book Store!!!\nWhat would you like to do?\n";

  while (true) {
    std::cout << "\n";
    std::cout << "1: Display book catalogue\n";
    std::cout << "2: Search for book\n";
    std::cout << "3: Purchase a book\n";
    std::cout << "4: Exit\n";
    std::cout << "> ";
    auto intent = getInput();
    std::cout << "\n";
    switch (*intent.c_str()) {
    case '1':
      catalogue.display();
      break;

    case '2': {
      std::cout << "Enter the title or ISBN of the book\n> ";
      auto query = getInput();
      Book *book = nullptr;
      std::cout << "\n";
      if (std::all_of(query.begin(), query.end(), std::isdigit)) {
        // If the input is a number, search by ISBN
        unsigned long long int isbn = std::stoull(query);
        book = catalogue.search(isbn);
      } else {
        // If the input is not a number, search by title
        book = catalogue.search(query);
      }
      if (book != nullptr) {
        std::cout << book->toString() << "\n";
      } else {
        std::cout << "Book not found!!!\n";
      }
      break;
    }

    case '3':
      catalogue.purchase(&user, &store);
      break;
    case '4':
      return 0;
    default:
      std::cout << "Invalid option. Please try again.\n";
    }
  }
}
