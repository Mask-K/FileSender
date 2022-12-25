#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const int max_length = 1024;

class Client {
public:
	Client(std::string ip, boost::asio::io_context& io_service, std::string file_path);

	void Send();
	void Connect(boost::asio::io_context& io_service);

private:
	std::string server_ip;
	std::string port;
	std::string file;
	std::ifstream source_file;

	tcp::socket socket;
	boost::system::error_code error;
};
