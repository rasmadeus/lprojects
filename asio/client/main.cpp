void write_to_socket(boost::asio::ip::tcp::socket& sock)
{
    const std::string buf{"Hello world!"};
    std::size_t bytes_written = 0;
    while(bytes_written != buf.length())
    {
        const auto data = boost::asio::buffer(buf.c_str() + bytes_written, buf.length() - bytes_written);
        bytes_written += sock.write_some(data);
    }
}

int main()
{
    const std::string address{"127.0.0.1"};
    const short port = 3333;

    try
    {
        boost::asio::ip::tcp::endpoint ep{boost::asio::ip::address::from_string(address), port};
        boost::asio::io_service ios;
        boost::asio::ip::tcp::socket sock{ios, ep.protocol()};
        sock.connect(ep);
        write_to_socket(sock);
    }
    catch(const boost::system::system_error& ex)
    {
        std::cerr << "Error: " << ex.code() << ". " << ex.what() << std::endl;
    }
}
