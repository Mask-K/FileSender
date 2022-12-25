#include "Client.h"
#include <boost/algorithm/string/replace.hpp>

Client::Client(std::string ip, boost::asio::io_context& io_context, std::string file_path) 
    : socket(io_context), file(file_path), source_file(file, std::ios_base::binary | std::ios_base::ate)
{
	size_t pos = ip.find(':');
	if (pos == std::string::npos)
		throw std::runtime_error("wrong ip with port");
    if (!source_file.is_open()) {
        socket.close();
        throw std::runtime_error("failed to open file: " + file);
    }
	server_ip = ip.substr(0, pos);
	port = ip.substr(pos + 1);

}

void Client::Send()
{

    char buf[max_length];
    
    size_t file_size = source_file.tellg();
    source_file.seekg(0);
    boost::asio::streambuf request;

    std::ostream request_stream(&request);
    size_t pos = file.find_last_of('\\');
    
    if (pos != std::string::npos)
        file = file.substr(pos + 1);

    boost::replace_all(file, " ", "_"); //change possible empties in names

    request_stream << file << "\n"
        << file_size << "\n\n";
    boost::asio::write(socket, request);
    while (1)
    {

        if (!source_file.eof())
        {
            source_file.read(buf, (std::streamsize)max_length);
            if (source_file.gcount() <= 0)
                throw std::runtime_error("failed to read file");

            boost::asio::write(socket, boost::asio::buffer(buf,
                source_file.gcount()),
                boost::asio::transfer_all(), error);
            if (error)
                throw std::runtime_error("failed to send file: " + error.message());
        }
        else
            break;
    }
    std::cout << "File " << file << " was sent successfully.\n";

}

void Client::Connect(boost::asio::io_context& io_service) {
    tcp::resolver resolver(io_service);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(server_ip, port);
    tcp::resolver::iterator end;


    error = boost::asio::error::host_not_found;
    while (error && endpoint_iterator != end)
    {
        socket.close();
        socket.connect(*endpoint_iterator++, error);
    }
    if (error)
        throw boost::system::system_error(error);
    std::cout << "Connected to server" << std::endl;

}
