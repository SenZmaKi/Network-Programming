#include "../common/cli.hpp"
#include "asio.hpp"
#include "common.hpp"
#include <iostream>
#include <string>
#include <utility>

asio::ip::tcp::socket connectToServer(asio::io_context &context) {
  asio::error_code errorCode;
  asio::ip::tcp::endpoint endpoint(asio::ip::make_address(URL, errorCode),
                                   PORT);
  asio::ip::tcp::socket socket(context);
  // For whatever reason socket.connect() still returns an error even though we
  // pass errorCode the variable to write the error into, this temporary _
  // variable is here to stop my LSP from complaining
  auto _ = socket.connect(endpoint, errorCode);
  if (errorCode) {
    std::cerr << "Failed to connect to address: " << errorCode.message()
              << "\n";
    exit(1);
  }
  std::cout << "Connected to " << URL << ":" << PORT << "\n";
  return std::move(socket);
}

std::string packageRequestMessage(char request, std::string message) {
  return message + request;
}

int main() {
  asio::io_context context;
  auto socket = connectToServer(context);
  auto display = [&] {
    writeToSocket(DISPLAY_REQUEST, socket);
    return readFromSocket(socket);
  };
  auto search = [&](std::string query) {
    writeToSocket(packageRequestMessage(SEARCH_REQUEST, query), socket);
    return readFromSocket(socket);
  };
  auto purchaseBook = [&] {
    writeToSocket(PURCHASE_REQUEST, socket);
    return readFromSocket(socket);
  };
  auto payForBook = [&](int bookNumber) {
    writeToSocket(
        packageRequestMessage(PAY_REQUEST, std::to_string(bookNumber)), socket);
    return readFromSocket(socket);
  };
  auto exit = [&] { writeToSocket(EXIT_REQUEST, socket); };
  cli(display, search, purchaseBook, payForBook, exit);
}
