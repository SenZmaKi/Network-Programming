
#include "Catalogue.h"
#include "../utils.h"
#include "Book.h"
#include "misc.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

Catalogue::Catalogue(std::vector<Book> books) : books(books) {}

void Catalogue::display() {
  for (const auto &book : books) {
    std::cout << "\n" << book.toString() << "\n";
  }
}

Book *Catalogue::search(std::string title) {
  for (Book &book : books) {
    if (book.title == title) {
      return &book;
    }
  }
  return nullptr;
}
Book *Catalogue::search(unsigned long long int &isbn) {
  for (Book &book : books) {
    if (book.isbn == isbn) {
      return &book;
    }
  }
  return nullptr;
}

Catalogue Catalogue::loadFromDB() {
  std::ifstream file("db.txt");
  std::string line;
  std::vector<Book> books;
  bool isFirstLine = true;
  while (std::getline(file, line)) {
    if (line == "") {
      continue;
    }
    if (isFirstLine) {
      isFirstLine = false;
      continue;
    }
    auto bookData = splitString(line, "    ");
    Book book(bookData[1], {bookData[2]}, std::stoull(bookData[3]), bookData[4],
              bookData[5], std::stoul(bookData[6]), std::stoul(bookData[7]));
    books.push_back(book);
  }
  return *new Catalogue(books);
}

void Catalogue::purchase(User *user, Store *store) {
  std::cout << "You currently have Ksh " << user->money << "\n";
  for (int i = 0; i < books.size(); i++) {
    if (books[i].quantity >= 1) {
      std::cout << i + 1 << ": " << books[i].title << " | Ksh "
                << std::to_string(books[i].price) << "\n";
    }
  };
  std::cout << "Enter the book number\n"
            << "> ";
  auto bookNumStr = getInput();
  auto bookNum = std::stoi(bookNumStr);
  auto book = books[bookNum - 1];
  if (book.price > user->money) {
    std::cout << "You don't have enough money!!! You need Ksh "
              << book.price - user->money << " more\n";
    return;
  }
  user->money -= book.price;
  store->money += book.price;
  book.quantity--;
  std::cout << "Successfully purchased \"" << book.title << "\"" << std::endl;
}
