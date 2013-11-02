#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <vector>

using boost::asio::ip::tcp;

int main(int argc, char** argv) {
  std::vector<std::string> args(argv, argv + argc);
  if (args.size() != 3) {
    std::cout << "Usage: mcinfo <host> <port>\n";
    return -1;
  }

  boost::asio::io_service io_service;
  tcp::resolver resolver{io_service};

  tcp::resolver::query query{argv[1], argv[2]};

  tcp::socket socket{io_service};

  try {
    auto endpoint_iterator = resolver.resolve(query);
    boost::asio::connect(socket, endpoint_iterator);
  } catch(...) {
    std::cout << "???\n";
    return 0;
  }

  unsigned char queryCmd[] = { 0xFE };
  socket.write_some(boost::asio::buffer(queryCmd));

  std::vector<unsigned char> buf(128, '\0');
  socket.read_some(boost::asio::buffer(buf));

  buf.erase(std::remove(buf.begin(), buf.end(), '\0'), buf.end());
  buf.erase(buf.begin(), std::find(buf.begin(), buf.end(), 0xA7) + 1);

  auto mid = std::find(buf.begin(), buf.end(), 0xA7);
  std::string players(buf.begin(), mid);
  std::string maxPlayers(mid + 1, buf.end());

  std::cout << players << "/" << maxPlayers << "\n";
}
