class SyncTCPCient
{
public:
    SyncTCPCient(const std::string& raw_ip_address, unsigned short port_num)
        : m_ep{boost::asio::ip::address::from_string(raw_ip_address), port_num}
        , m_sock{m_ios}
    {
        m_sock.open(m_ep.protocol());
    }

    void connect()
    {
        m_sock.connect(m_ep);
    }

    void close()
    {
        m_sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        m_sock.close();
    }

    std::string emulate_long_computation_op(unsigned int duration_sec)
    {
        const std::string request = "EMULATE_LONG_COMP_OP " + std::to_string(duration_sec) + "\n";
        send_request(request);
        return receive_response();
    }

private:
    void send_request(const std::string& request)
    {
        boost::asio::write(m_sock, boost::asio::buffer(request));
    }

    std::string receive_response()
    {
        boost::asio::streambuf buf;
        boost::asio::read_until(m_sock, buf, '\n');
        std::istream input{&buf};
        std::string response;
        std::getline(input, response);
        return response;
    }

private:
    boost::asio::io_service m_ios;
    boost::asio::ip::tcp::endpoint m_ep;
    boost::asio::ip::tcp::socket m_sock;
};


int main()
{
    const std::string address{"127.0.0.1"};
    const short port = 3333;

    try
    {
        SyncTCPCient client{address, port};
        client.connect();
        std::cout << "Sending request to server..." << std::endl;
        std::cout << "Response: " << client.emulate_long_computation_op(10);
        client.close();
    }
    catch(const boost::system::system_error& ex)
    {
        std::cerr << "Error: " << ex.code() << ". " << ex.what() << std::endl;
    }
}
