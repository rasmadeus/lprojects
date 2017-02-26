std::string read_from(boost::asio::ip::tcp::socket& sock)
{
    const unsigned char size = 13;
    char buf[size];
    size_t bytes_read = 0;
    while(bytes_read != size)
    {
        const auto data = boost::asio::buffer(buf + bytes_read, size - bytes_read);
        bytes_read = sock.read_some(data);
    }
    return std::string{buf, bytes_read};
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
        const std::string data = read_from(sock);
        std::cout << "Get: " << data << std::endl;
    }
    catch(const boost::system::system_error& ex)
    {
        std::cerr << "Error: " << ex.code() << ". " << ex.what() << std::endl;
    }
}
