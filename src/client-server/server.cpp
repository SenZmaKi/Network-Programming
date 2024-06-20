
#include "../common/common.hpp"
#include "asio.hpp"
#include "common.hpp"
#include <iostream>
#include <string>

void handleClient(asio::ip::tcp::socket &socket, int userID, User *user,
                  Store *store, Catalogue *catalogue) {
  for (;;) {
    std::cout << "\n";
    asio::error_code errorCode;
    std::string message = readFromSocket(socket, errorCode);
    auto userIDStr = std::to_string(userID);
    if (errorCode) {
      std::cerr << "User " << userIDStr
                << ": ClientSocketError: " << errorCode.message() << "\n";
      return;
    }
    std::cout << "User " << userIDStr << ": Received payload: " << message
              << "\n";
    auto request = message.back();
    message.pop_back();
    std::cout << "User " << userIDStr << ": Decoded message: " << message
              << "\n";
    switch (request) {
    case DISPLAY_REQUEST: {
      std::cout << "User " << userIDStr << ": Display request\n";
      auto catalogueStr = catalogue->display();
      writeToSocket(catalogueStr, socket);
      break;
    }
    case SEARCH_REQUEST: {
      std::cout << "User " << userIDStr << ": Search request\n";
      auto searchResult = catalogue->search(message);
      writeToSocket(searchResult, socket);
      break;
    }
    case PURCHASE_REQUEST: {
      std::cout << "User " << userIDStr << ": Purchase request\n";
      auto purchaseResult = catalogue->purchaseBook(user);
      writeToSocket(purchaseResult, socket);
      break;
    }
    case PAY_REQUEST: {
      std::cout << "User " << userIDStr << ": Pay request\n";
      auto bookNumber = std::stoi(message);
      auto payResult = catalogue->payForBook(bookNumber, user, store);
      writeToSocket(payResult, socket);
      break;
    }
    case EXIT_REQUEST: {
      std::cout << "User " << userIDStr << ": Exit Request\n";
      return;
    }
    default: {
      std::cout << "User " << userIDStr << ": Unknown Request\n";
      break;
    }
    }
  }
}

int main() {
  auto [user, store, catalogue] = initDefaults();
  try {
    asio::io_context io_context;
    asio::ip::tcp::acceptor acceptor(
        io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), PORT));
    std::cout << "Started server listening at port: " << PORT << "\n";
    auto userID = 0;
    for (;;) {
      asio::ip::tcp::socket socket(io_context);
      acceptor.accept(socket);
      std::cout << "\nConnection received\n";
      userID++;
      std::thread clientHandlerThread(
          [&, socket = std::move(socket), user]() mutable {
            handleClient(socket, userID, &user, &store, &catalogue);
          });
      clientHandlerThread.detach();
    }
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
