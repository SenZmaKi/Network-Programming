
#ifndef CLIENT_SERVER_COMMON_H
#define CLIENT_SERVER_COMMON_H

#include "asio.hpp"
#include <string>

inline extern const char SOCKET_EOF_DELIMETER = '\0';
inline extern const int PORT = 8080;
inline extern const std::string URL = "127.0.0.1";
inline extern const char DISPLAY_REQUEST = 'D';
inline extern const char SEARCH_REQUEST = 'S';
inline extern const char PURCHASE_REQUEST = 'U';
inline extern const char PAY_REQUEST = 'A';
inline extern const char EXIT_REQUEST = 'X';

std::string readFromSocket(asio::ip::udp::socket &socket,
                           asio::ip::udp::endpoint &endpoint,
                           asio::error_code &errorCode);

std::string readFromSocket(asio::ip::udp::socket &socket,
                           asio::ip::udp::endpoint &endpoint);

void writeToSocket(const std::string &message, asio::ip::udp::socket &socket,
                   const asio::ip::udp::endpoint &endpoint);

void writeToSocket(char request, asio::ip::udp::socket &socket,
                   const asio::ip::udp::endpoint &endpoint);

#endif // CLIENT_SERVER_COMMON_H
