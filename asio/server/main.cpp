int main()
{
    const unsigned short server_port = 3333;

    const auto server_ip_address = boost::asio::ip::address_v6::any();
    boost::asio::ip::tcp::endpoint endpoint{server_ip_address, server_port};
}
