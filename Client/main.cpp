#include "Client.h"



int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Wrong parameter amount\n";
        std::cerr << "Should have been <ip-port> <file path>\n";
        return 1;
    }
    try
    {
        boost::asio::io_context io_context;
        
        Client cl(argv[1], io_context, argv[2]);
        cl.Connect(io_context);
        cl.Send();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}