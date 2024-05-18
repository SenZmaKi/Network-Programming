#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "Book.hpp"
#include "misc.hpp"
#include <vector>

class Catalogue {
public:
  std::vector<Book> books;

  Catalogue(std::vector<Book> books);

  std::string display();

  std::string search(std::string query);

  static Catalogue loadFromDB();

  std::string purchaseBook(User *user);
  std::string payForBook(int bookNumber, User *user, Store *store);
};

#endif
