
#ifndef BOOK_H
#define BOOK_H

#include <vector>
#include <string>

class Book {
public:
    std::string title;
    std::vector<std::string> authors;
    unsigned long long int isbn;
    std::string publisher;
    std::string dateOfPublication;
    unsigned long long int price;
    unsigned long long int quantity;

    Book(std::string title, std::vector<std::string> authors,
         unsigned long long int isbn, std::string publisher,
         std::string dateOfPublication, unsigned long long int price,
         unsigned long long int count);

    std::string toString() const;
};

#endif // BOOK_H
