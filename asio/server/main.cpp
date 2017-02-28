void process_request(boost::asio::ip::tcp::socket& sock)
{
    boost::asio::streambuf request_buf;
    boost::system::error_code ec;
    boost::asio::read(sock, request_buf, ec);
    if (ec != boost::asio::error::eof)
        throw boost::system::system_error{ec};

    const char response_buf[] = {0x48, 0x69, 0x21};
    boost::asio::write(sock, boost::asio::buffer(response_buf));
    sock.shutdown(boost::asio::socket_base::shutdown_send);
}


int main()
{
    const short port = 3333;

    try
    {
        boost::asio::ip::tcp::endpoint ep{boost::asio::ip::address_v4::any(), port};
        boost::asio::io_service ios;
        boost::asio::ip::tcp::acceptor acceptor{ios, ep};
        boost::asio::ip::tcp::socket sock{ios};
        acceptor.accept(sock);
        process_request(sock);

    }
    catch(const boost::system::system_error& ex)
    {
        std::cerr << "Error: " << ex.code() << ". " << ex.what() << std::endl;
    }
}
