#include "Book.hpp"
#include <string>
#include <vector>

Book::Book(std::string title, std::vector<std::string> authors,
           unsigned long long int isbn, std::string publisher,
           std::string dateOfPublication, unsigned long long int price,
           unsigned long long int count)
    : title(title), authors(authors), isbn(isbn), publisher(publisher),
      dateOfPublication(dateOfPublication), price(price), quantity(count){};

std::string Book::toString() const {
  std::string bookString;
  bookString += "Title: " + title + "\n";
  bookString += "Authors: ";
  for (const auto &author : authors) {
    bookString += author + " ";
  }
  bookString += "\n";
  bookString += "ISBN: " + std::to_string(isbn) + "\n";
  bookString += "Publisher: " + publisher + "\n";
  bookString += "Date of Publication: " + dateOfPublication + "\n";
  bookString += "Price: Ksh " + std::to_string(price) + "\n";
  return bookString;
}
