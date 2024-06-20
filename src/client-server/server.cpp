#include "../common/common.hpp"
#include "asio.hpp"
#include "common.hpp"
#include <iostream>
#include <string>

void handleClient(asio::ip::udp::socket &socket, asio::ip::udp::endpoint &clientEndpoint, User *user, Store *store, Catalogue *catalogue) {
  for (;;) {
    std::cout << "\n";
    asio::error_code errorCode;
    std::string message = readFromSocket(socket, clientEndpoint, errorCode);
    if (errorCode) {
      std::cerr << "ClientSocketError: " << errorCode.message() << "\n";
      return;
    }
    std::cout << "Received payload: " << message << "\n";
    auto request = message.back();
    message.pop_back();
    std::cout << "Decoded message: " << message << "\n";
    switch (request) {
    case DISPLAY_REQUEST: {
      std::cout << "Display request\n";
      auto catalogueStr = catalogue->display();
      writeToSocket(catalogueStr, socket, clientEndpoint);
      break;
    }
    case SEARCH_REQUEST: {
      std::cout << "Search request\n";
      auto searchResult = catalogue->search(message);
      writeToSocket(searchResult, socket, clientEndpoint);
      break;
    }
    case PURCHASE_REQUEST: {
      std::cout << "Purchase request\n";
      auto purchaseResult = catalogue->purchaseBook(user);
      writeToSocket(purchaseResult, socket, clientEndpoint);
      break;
    }
    case PAY_REQUEST: {
      std::cout << "Pay request\n";
      auto bookNumber = std::stoi(message);
      auto payResult = catalogue->payForBook(bookNumber, user, store);
      writeToSocket(payResult, socket, clientEndpoint);
      break;
    }
    case EXIT_REQUEST: {
      std::cout << "Exit Request\n";
      return;
    }
    default: {
      std::cout << "Unknown Request\n";
      break;
    }
    }
  }
}

int main() {
  auto [user, store, catalogue] = initDefaults();
  try {
    asio::io_context io_context;
    asio::ip::udp::socket socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), PORT));
    std::cout << "Started server listening at port: " << PORT << "\n";
    for (;;) {
      asio::ip::udp::endpoint clientEndpoint;
      handleClient(socket, clientEndpoint, &user, &store, &catalogue);
    }
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
