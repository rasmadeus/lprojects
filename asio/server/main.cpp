struct Session
{
    std::shared_ptr<boost::asio::ip::tcp::socket> sock;
    std::unique_ptr<char[]> buf;
    std::size_t total_bytes_read;
    unsigned int buf_size{ 0 };
};

void callback(const boost::system::error_code& ec, std::size_t bytes_transferred, const std::shared_ptr<Session>& s)
{
    if (ec != 0)
    {
        std::cerr << "Error: " << ec.value() << std::endl;
        return;
    }

    s->total_bytes_read += bytes_transferred;
    if (s->total_bytes_read == s->buf_size)
        return;

    s->sock->async_read_some(
        boost::asio::buffer(s->buf.get() + s->total_bytes_read, s->buf_size - s->total_bytes_read),
        std::bind(callback, std::placeholders::_1, std::placeholders::_2, s)
    );
}

void read_from_socket(const std::shared_ptr<boost::asio::ip::tcp::socket>& sock)
{
    const auto s = std::make_shared<Session>();
    const unsigned int size = 11;
    s->buf.reset(new char[size]);
    s->total_bytes_read = 0;
    s->sock = sock;
    s->buf_size = size;

    s->sock->async_read_some(
        boost::asio::buffer(s->buf.get(), s->buf_size),
        std::bind(callback, std::placeholders::_1, std::placeholders::_2, s)
    );
}


int main()
{
    const std::string address{"127.0.0.1"};
    const short port = 3333;

    try
    {
        boost::asio::ip::tcp::endpoint ep{boost::asio::ip::address::from_string(address), port};
        boost::asio::io_service ios;
        const auto sock = std::make_shared<boost::asio::ip::tcp::socket>(ios, ep.protocol());
        sock->connect(ep);
        read_from_socket(sock);
        ios.run();

    }
    catch(const boost::system::system_error& ex)
    {
        std::cerr << "Error: " << ex.code() << ". " << ex.what() << std::endl;
    }
}
