#ifndef RESOLVER_H
#define RESOLVER_H

void resolve(const std::string& host, const std::string& port)
{
    boost::asio::io_service ios;
    boost::asio::ip::tcp::resolver::query query{host, port, boost::asio::ip::tcp::resolver::query::numeric_service};
    boost::asio::ip::tcp::resolver resolver{ios};

    boost::system::error_code er;
    auto it = resolver.resolve(query, er);
    if (er != 0)
    {
        std::cout << "Failed to resolver a DNS name. Error" << er.value() << ":" << er.message() << std::endl;
        return;
    }

    const auto end = boost::asio::ip::tcp::resolver::iterator{};
    for(; it != end; ++it)
    {
        auto endpoint = it->endpoint();
        std::cout << "Endpoint: " << endpoint.address() << ":" << endpoint.port() << std::endl;
    }
}

#endif // RESOLVER_H
