std::string make_daytime_string()
{
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

int main()
{
    try
    {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor{
            io_service,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13)
        };
        while(true)
        {
            boost::asio::ip::tcp::socket socket{io_service};
            acceptor.accept(socket);
            std::string message = make_daytime_string();
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
