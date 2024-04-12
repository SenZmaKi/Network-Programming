
#include "Catalogue.hpp"
#include "../utils.hpp"
#include "Book.hpp"
#include "misc.hpp"
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

Catalogue::Catalogue(std::vector<Book> books) : books(books) {}

std::string Catalogue::display() {
  std::string booksStr;
  for (const auto &book : books) {
    booksStr += "\n" + book.toString() + "\n";
  }
  return booksStr;
}

std::string Catalogue::search(std::string query) {
  if (std::all_of(query.begin(), query.end(), std::isdigit)) {
    unsigned long long int isbn = std::stoull(query);
    for (Book &book : books) {
      if (book.isbn == isbn) {
        return book.toString() + "\n";
      }
    }
  }
  // Not else incase the book's title is a number
  for (Book &book : books) {
    if (book.title == query) {
      return book.toString() + "\n";
    }
  }
  return "Book not found\n";
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

std::string Catalogue::purchaseBook(User *user) {
  std::string startPurchaseStr;
  startPurchaseStr +=
      "You currently have Ksh " + std::to_string(user->money) + "\n";
  for (int i = 0; i < books.size(); i++) {
    startPurchaseStr += std::to_string(i + 1) + ": " + books[i].title +
                        " | Ksh " + std::to_string(books[i].price) + "\n";
  };
  startPurchaseStr += "Enter the book number\n> ";
  return startPurchaseStr;
}

std::string Catalogue::payForBook(int bookNumber, User *user, Store *store) {
  auto book = books[bookNumber - 1];
  if (book.quantity <= 0) {
    return "Sorry the book is currently out of stock\n";
  }
  if (book.price > user->money) {
    std::string moreStr = std::to_string(book.price - user->money);
    return "You don't have enough money!!! You need Ksh " + moreStr + " more\n";
  }
  user->money -= book.price;
  store->money += book.price;
  book.quantity--;
  return "Successfully purchased \"" + book.title + "\"\n";
}
