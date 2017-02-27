struct Session
{
    std::shared_ptr<boost::asio::ip::tcp::socket> sock;
    std::string buf;
    std::size_t total_bytes_written{ 0 };
};

void callback(const boost::system::error_code& ec, std::size_t bytes_transfered, const std::shared_ptr<Session>& s)
{
    if (ec != 0)
    {
        std::cerr << "Error: " << ec.value() << std::endl;
        return;
    }

    s->total_bytes_written += bytes_transfered;
    if (s->total_bytes_written == s->buf.length())
        return;

    s->sock->async_write_some(
        boost::asio::buffer(s->buf.c_str() + s->total_bytes_written, s->buf.length() - s->total_bytes_written),
        std::bind(callback, std::placeholders::_1, std::placeholders::_2, s)
    );
}

void write_to_socket(const std::shared_ptr<boost::asio::ip::tcp::socket>& sock)
{
    const auto s = std::make_shared<Session>();
    s->buf = std::string{"Hello world!"};
    s->total_bytes_written = 0;
    s->sock = sock;
    s->sock->async_write_some(
        boost::asio::buffer(s->buf),
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
        write_to_socket(sock);
        ios.run();
    }
    catch(const boost::system::system_error& ex)
    {
        std::cerr << "Error: " << ex.code() << ". " << ex.what() << std::endl;
    }
}
