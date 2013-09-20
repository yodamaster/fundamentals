#define _WIN32_WINDOWS 0x0501

#include <boost/asio.hpp>
#include <iostream>

namespace asio = boost::asio;
using asio::ip::tcp;
typedef boost::system::error_code error_code;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <host> <port>" << std::endl;
    return 0;
  }
  std::cout << "Executing " << argv[0] << " " << argv[1] << " " << argv[2] << std::endl;

  asio::io_service io_service;
  tcp::resolver resolver(io_service);
  resolver.async_resolve(tcp::resolver::query(argv[1], argv[2]),
    [](const error_code &ec, tcp::resolver::iterator it) {
      if (!ec) {
        for (; it != tcp::resolver::iterator(); ++it) {
          tcp::endpoint ep = *it;
          std::cout << "Endpoint: " << ep << std::endl;
        }
      }
    });
  io_service.run();
  return 0;
}
