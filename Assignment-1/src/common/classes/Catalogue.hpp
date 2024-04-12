#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "Book.hpp"
#include "misc.hpp"
#include <vector>


class Catalogue {
public:
  std::vector<Book> books;

  Catalogue(std::vector<Book> books);

  void display();

  Book *search(std::string title);

  Book *search(unsigned long long int &isbn);

  static Catalogue loadFromDB();

  void purchase(User *user, Store *store);
};

#endif 
