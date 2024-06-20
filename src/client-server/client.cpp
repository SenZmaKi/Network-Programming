#include "../common/cli.hpp"
#include "asio.hpp"
#include "common.hpp"
#include <iostream>
#include <string>
#include <utility>


asio::ip::udp::socket createSocket(asio::io_context &context) {
  asio::ip::udp::socket socket(context);
  socket.open(asio::ip::udp::v4());
  return std::move(socket);
}

std::string packageRequestMessage(char request, const std::string &message) {
  return message + request;
}

int main() {
  asio::io_context context;
  auto socket = createSocket(context);
  asio::ip::udp::endpoint serverEndpoint(asio::ip::make_address(URL), PORT);

  auto display = [&] {
    writeToSocket(DISPLAY_REQUEST, socket, serverEndpoint);
    return readFromSocket(socket, serverEndpoint);
  };
  auto search = [&](const std::string &query) {
    writeToSocket(packageRequestMessage(SEARCH_REQUEST, query), socket,
                  serverEndpoint);
    return readFromSocket(socket, serverEndpoint);
  };
  auto purchaseBook = [&] {
    writeToSocket(PURCHASE_REQUEST, socket, serverEndpoint);
    return readFromSocket(socket, serverEndpoint);
  };
  auto payForBook = [&](int bookNumber) {
    writeToSocket(
        packageRequestMessage(PAY_REQUEST, std::to_string(bookNumber)), socket,
        serverEndpoint);
    return readFromSocket(socket, serverEndpoint);
  };
  auto exit = [&] { writeToSocket(EXIT_REQUEST, socket, serverEndpoint); };

  cli(display, search, purchaseBook, payForBook, exit);
}
