#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <sstream>
#include <memory>
#include <thread>
#include <functional>

using boost::asio::ip::tcp;

const int max_length = 1024;

class Server {
public:
    Server(unsigned port, boost::asio::io_context& io_context);


private:
    void Read(std::shared_ptr<tcp::socket> socket);
    void WriteFile(std::istream& request_stream, size_t file_size, std::shared_ptr<tcp::socket> socket);


	unsigned port;
    char buf[max_length];
    std::string file_path;
	boost::system::error_code error;

};
