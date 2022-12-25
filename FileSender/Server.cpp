#include "Server.h"



void Server::Read(std::shared_ptr<tcp::socket> socket) {
    boost::asio::streambuf request_buf;
    
    boost::asio::read_until(*socket, request_buf, "\n\n");

    std::istream request_stream(&request_buf);

    size_t file_size = 0;

    request_stream >> file_path;
    request_stream >> file_size;
    request_stream.read(buf, 2); 
    
    file_path = "ServerDir\\" + file_path;
    WriteFile(request_stream, file_size, socket);

}

void Server::WriteFile(std::istream& request_stream, size_t file_size, std::shared_ptr<tcp::socket> socket) {

    std::ofstream output_file(file_path.c_str(), std::ios_base::binary);
    if (!output_file)
        throw std::runtime_error("failed to open file: " + file_path);

    do
    {
        request_stream.read(buf, (std::streamsize)max_length);
        output_file.write(buf, request_stream.gcount());
    } while (request_stream.gcount() > 0);

    while (true)
    {
        size_t len = socket->read_some(boost::asio::buffer(buf), error);
        if (len > 0)
            output_file.write(buf, (std::streamsize)len);
        if (output_file.tellp() == (std::fstream::pos_type)(std::streamsize)file_size)
            break; 
        if (error)
        {
            std::cout << error << std::endl;
            break;
        }
    }
    std::cout << "The file was sucessfuly received\n";
}


Server::Server(unsigned port, boost::asio::io_context& io_context) {
    tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
    while (true) {
        try {
            std::shared_ptr<tcp::socket> socket(new tcp::socket(io_context));
            a.accept(*socket);
            std::cout << "A client connected." << std::endl;
            std::thread t([&]() {return Read(socket); });
            t.join();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}