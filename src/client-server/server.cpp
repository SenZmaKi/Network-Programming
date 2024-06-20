#include "../common/common.hpp"
#include "asio.hpp"
#include "common.hpp"
#include <algorithm>
#include <iostream>
#include <string>

bool handleMessage(asio::ip::udp::socket &socket,
                   asio::ip::udp::endpoint &clientEndpoint, int userID,
                   User *user, Store *store, Catalogue *catalogue) {
  std::cout << "\n";
  asio::error_code errorCode;
  std::string message = readFromSocket(socket, clientEndpoint, errorCode);
  auto userIDStr = std::to_string(userID);
  if (errorCode) {
    std::cerr << "User " << userIDStr
              << ": ClientSocketError: " << errorCode.message() << "\n";
    return false;
  }
  std::cout << "User " << userIDStr << ": Received payload: " << message
            << "\n";
  auto request = message.back();
  message.pop_back();
  std::cout << "User " << userIDStr << ": Decoded message: " << message << "\n";
  switch (request) {
  case DISPLAY_REQUEST: {
    std::cout << "User " << userIDStr << ": Display request\n";
    auto catalogueStr = catalogue->display();
    writeToSocket(catalogueStr, socket, clientEndpoint);
    break;
  }
  case SEARCH_REQUEST: {
    std::cout << "User " << userIDStr << ": Search request\n";
    auto searchResult = catalogue->search(message);
    writeToSocket(searchResult, socket, clientEndpoint);
    break;
  }
  case PURCHASE_REQUEST: {
    std::cout << "User " << userIDStr << ": Purchase request\n";
    auto purchaseResult = catalogue->purchaseBook(user);
    writeToSocket(purchaseResult, socket, clientEndpoint);
    break;
  }
  case PAY_REQUEST: {
    std::cout << "User " << userIDStr << ": Pay request\n";
    auto bookNumber = std::stoi(message);
    auto payResult = catalogue->payForBook(bookNumber, user, store);
    writeToSocket(payResult, socket, clientEndpoint);
    break;
  }
  case EXIT_REQUEST: {
    std::cout << "User " << userIDStr << ": Exit Request\n";
    return false;
  }
  default: {
    std::cout << "User " << userIDStr << ": Unknown Request\n";
    break;
  }
  }
  return true;
}

int main() {
  auto [user, store, catalogue] = initDefaults();
  auto userID = 0;
  try {
    asio::io_context io_context;
    asio::ip::udp::socket socket(
        io_context, asio::ip::udp::endpoint(asio::ip::make_address(URL), PORT));
    std::cout << "Started server listening at port: " << PORT << "\n";
    for (;;) {
      auto clientEndpoint = asio::ip::udp::endpoint();
      userID++;
      auto userCopy = user;
      handleMessage(socket, clientEndpoint, userID, &userCopy, &store,
                    &catalogue);
      auto clientHandlerThread = std::thread(
          [&, clientEndpoint = std::move(clientEndpoint)]() mutable {
            for (;;) {
              if (!handleMessage(socket, clientEndpoint, userID, &userCopy,
                                 &store, &catalogue)) {
                break;
              }
            }
          });
      clientHandlerThread.detach();
    }
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
