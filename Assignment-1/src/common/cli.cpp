
#include "./common.hpp"
#include "utils.hpp"
#include <functional>
#include <iostream>
#include <ostream>
#include <string>

void cli(std::function<std::string()> display,
         std::function<std::string(std::string)> search,
         std::function<std::string()> purchaseBook,
         std::function<std::string(int)> payForBook,
         std::function<void()> exit) {

  std::cout << "Welcome to Chambua Book Store!!!\nWhat would you like to do?\n";
  while (true) {
    std::cout << "\n";
    std::cout << "1: Display book catalogue\n";
    std::cout << "2: Search for book\n";
    std::cout << "3: Purchase a book\n";
    std::cout << "4: Exit\n";
    std::cout << "> ";
    auto request = getInput();
    std::cout << "\n";
    switch (*request.c_str()) {
    case '1': {
      auto catalogueStr = display();
      std::cout << catalogueStr;
      break;
    }
    case '2': {
      std::cout << "Enter the Title or ISBN of the book\n> ";
      auto query = getInput();
      Book *book = nullptr;
      std::cout << "\n";
      auto searchResults = search(query);
      std::cout << searchResults;
      break;
    }

    case '3': {
      auto purchaseStr = purchaseBook();
      std::cout << purchaseStr;
      auto bookNumberStr = getInput();
      auto bookNumber = std::stoi(bookNumberStr);
      auto payStr = payForBook(bookNumber);
      std::cout << payStr;
      break;
    }

    case '4': {
      exit();
      return;
    }

    default: {
      std::cout << "Invalid option. please try again.\n";
    }
    }
  }
}
