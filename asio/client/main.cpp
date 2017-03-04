int main()
{
    const std::string server{"127.0.0.1"};

    try
    {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver{io_service};
        boost::asio::ip::tcp::resolver::query query{server, "daytime"};
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        boost::asio::ip::tcp::socket socket{io_service};
        boost::asio::connect(socket, endpoint_iterator);

        while(true)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;
            const size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof)
                std::cout << "Connection closed cleanly by peer" << std::endl;
            else if (error)
                throw boost::system::system_error{error};

            std::cout << "Data from socket: " << buf.data() << std::endl;
        }
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
