#include "asio.hpp"
#include <iostream>

std::string readFromSocket(asio::ip::tcp::socket& socket) {
    asio::error_code errorCode;
    asio::streambuf buf;
    std::string data;

    while (asio::read(socket, buf.prepare(1024), errorCode)) {
        buf.commit(1024);
        data += asio::buffer_cast<const char*>(buf.data());
        buf.consume(1024);
    }

    if (errorCode && errorCode != asio::error::eof) {
        std::cerr << "Failed to read data: " << errorCode.message() << std::endl;
    }

    return data;
}
