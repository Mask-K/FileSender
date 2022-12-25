#include "Server.h"


using boost::asio::ip::tcp;


int main(int argc, char* argv[])
{
    try
    {
        unsigned port = 1234;
        if (argc > 2) {
            std::cerr << "Too many parameters. The only is <port>. Default = 1234";
            return 1;
        }
        if (argc == 2)
        {
            port = atoi(argv[1]);
        }

        std::cout << argv[0] << " Listen on port " << port << std::endl;

        boost::asio::io_context io_context;

        Server server(port, io_context);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unhandled error occured\n";
    }

    return 0;
}