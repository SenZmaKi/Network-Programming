#include "common.hpp"
#include "asio.hpp"
#include <iostream>

std::string readFromSocket(asio::ip::tcp::socket &socket,
                           asio::error_code &errorCode) {
  asio::streambuf buf;
  asio::read_until(socket, buf, SOCKET_EOF_DELIMETER, errorCode);
  std::string data;
  if (!errorCode) {
    data = asio::buffer_cast<const char *>(buf.data());
  }
  return data;
}
std::string readFromSocket(asio::ip::tcp::socket &socket) {
  asio::error_code errorCode;
  std::string data = readFromSocket(socket, errorCode);
  if (errorCode) {
    std::cerr << "Failed to read from socket: " << errorCode.message() << "\n";
    exit(1);
  }
  return data;
}

void writeToSocket(std::string message, asio::ip::tcp::socket &socket) {
  asio::error_code errorCode;
  asio::write(socket, asio::buffer(message + SOCKET_EOF_DELIMETER), errorCode);
  if (errorCode) {
    std::cerr << "Failed to write to socket: " << errorCode.message() << "\n";
    exit(1);
  }
}

void writeToSocket(char request, asio::ip::tcp::socket &socket) {
  writeToSocket(std::string(1, request), socket);
}
