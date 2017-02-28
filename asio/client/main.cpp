std::string buffer_to_string(const boost::asio::streambuf& buffer)
{
  using boost::asio::buffers_begin;

  auto bufs = buffer.data();
  std::string result(buffers_begin(bufs), buffers_begin(bufs) + buffer.size());
  return result;
}

void communicate(boost::asio::ip::tcp::socket& sock)
{
    const char request_buf[] = {0x48, 0x65, 0x0, 0x6c, 0x6c, 0x6f};

    boost::asio::write(sock, boost::asio::buffer(request_buf));
    sock.shutdown(boost::asio::socket_base::shutdown_send);
    boost::asio::streambuf response_buf;
    boost::system::error_code ec;
    boost::asio::read(sock, response_buf, ec);
    if (ec == boost::asio::error::eof)
    {
        std::cout << "Response came: " << buffer_to_string(response_buf) << std::endl;
    }
    else
    {
        std::cerr << "Error happened: " << ec.value() << std::endl;
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
    }
    catch(const boost::system::system_error& ex)
    {
        std::cerr << "Error: " << ex.code() << ". " << ex.what() << std::endl;
    }
}
