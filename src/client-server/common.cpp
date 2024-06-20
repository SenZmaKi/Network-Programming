#include "common.hpp"
#include "asio.hpp"
#include <iostream>
#include <vector>

std::string readFromSocket(asio::ip::udp::socket &socket,
                           asio::ip::udp::endpoint &endpoint,
                           asio::error_code &errorCode) {
  std::vector<char> buf(1024);
  auto len = socket.receive_from(asio::buffer(buf), endpoint, 0, errorCode);
  if (errorCode) {
    return "";
  }
  return std::string(buf.data(), len);
}

std::string readFromSocket(asio::ip::udp::socket &socket,
                           asio::ip::udp::endpoint &endpoint) {
  asio::error_code errorCode;
  std::string data = readFromSocket(socket, endpoint, errorCode);
  if (errorCode) {
    std::cerr << "Failed to read from socket: " << errorCode.message() << "\n";
    exit(1);
  }
  return data;
}

void writeToSocket(const std::string &message, asio::ip::udp::socket &socket,
                   const asio::ip::udp::endpoint &endpoint) {
  asio::error_code errorCode;
  socket.send_to(asio::buffer(message), endpoint, 0, errorCode);
  if (errorCode) {
    std::cerr << "Failed to write to socket: " << errorCode.message() << "\n";
    exit(1);
  }
}

void writeToSocket(char request, asio::ip::udp::socket &socket,
                   const asio::ip::udp::endpoint &endpoint) {
  writeToSocket(std::string(1, request), socket, endpoint);
}
