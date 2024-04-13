
#ifndef COMMON_H
#define COMMON_H

#include "asio.hpp"
#include <string>

const static char SOCKET_EOF_DELIMETER = '\0';
const static int PORT = 8080;
const static std::string URL = "127.0.0.1";
const static char DISPLAY_REQUEST = 'D';
const static char SEARCH_REQUEST = 'S';
const static char PURCHASE_REQUEST = 'U';
const static char PAY_REQUEST = 'A';
const static char EXIT_REQUEST = 'X';

std::string readFromSocket(asio::ip::tcp::socket &socket);
std::string readFromSocket(asio::ip::tcp::socket &socket,
                           asio::error_code &errorCode);
void writeToSocket(std::string message, asio::ip::tcp::socket &socket);
void writeToSocket(char message, asio::ip::tcp::socket &socket);

#endif // COMMON_H
