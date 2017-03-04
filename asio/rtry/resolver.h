#ifndef RESOLVER_H
#define RESOLVER_H

namespace resolver
{
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

    void test()
    {
        const std::vector<std::pair<std::string, std::string>> addresses{
            {{"rambler.ru"}, {"8080"}},
            {{"mail.ru"},{"8080"}},
            {{"rambler.ru"}, {"1000"}},
            {{"rasmadeus.ru"}, {"8080"}},
            {{"sadf.df"}, {"8080"}}
        };

        for(const auto address : addresses)
        {
            std::cout << "Host " << address.first << ":" << address.second << std::endl;
            resolve(address.first, address.second);
        }
    }
}

#endif // RESOLVER_H
