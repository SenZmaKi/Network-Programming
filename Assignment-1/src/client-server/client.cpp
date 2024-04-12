#include <iostream>
#include <string>
// Need to define WIN32 because each version of windows has slightly different
// ways of handling networking*
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include "./../../include/asio-1.28.0/include/asio.hpp"
const static int PORT = 8080;
const static std::string URL = "127.0.0.1";
int main() {

  asio::error_code errorCode;
  asio::io_context context;
  asio::ip::tcp::endpoint endpoint(asio::ip::make_address(URL, errorCode),
                                   PORT);
  asio::ip::tcp::socket socket(context);
  // For whatever reason socket.connect() still returns an error even though we
  // pass erroCode the variable to write the error into, this temporary _
  // variable is here to stop my LSP from complaining
  auto _ = socket.connect(endpoint, errorCode);
  if (!errorCode) {
    std::cout << "Connected to " << URL << ":" << PORT << std::endl;
  } else {
    std::cout << "Failed to connect to address: " << errorCode.message()
              << std::endl;
  }
  return 0;
}
