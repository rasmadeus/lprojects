class Service
{
public:
    void handle_client(boost::asio::ip::tcp::socket& sock)
    {
        try
        {
            boost::asio::streambuf request;
            boost::asio::read_until(sock, request, '\n');
            int i{0};
            while(i != 1000000)
            {
                ++i;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::string response = "Hello from Server\n";
                boost::asio::write(sock, boost::asio::buffer(response));
            }
        }
        catch(const boost::system::system_error& ex)
        {
            std::cerr << "Error in service: " << ex.code() << ". " << ex.what() << std::endl;
        }
    }
};


class Acceptor
{
public:
    Acceptor(boost::asio::io_service& ios, unsigned short port)
        : m_ios{ios}
        , m_acceptor{m_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port)}
    {
        m_acceptor.listen();
    }

    void accept()
    {
        boost::asio::ip::tcp::socket sock{m_ios};
        m_acceptor.accept(sock);
        Service svc;
        svc.handle_client(sock);
    }

private:
    boost::asio::io_service& m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
};


class Server
{
public:
    void start(unsigned short port)
    {
        m_thread = std::make_unique<std::thread>(&Server::run, this, port);
    }

    void stop()
    {
        m_stop = true;
        m_thread->join();
    }

private:
    void run(unsigned short port)
    {
        Acceptor acc{m_ios, port};
        while(!m_stop)
            acc.accept();
    }

private:
    std::unique_ptr<std::thread> m_thread;
    std::atomic<bool> m_stop{false};
    boost::asio::io_service m_ios;
};

int main()
{
    const short port = 3333;

    try
    {
        Server srv;
        srv.start(port);
        std::this_thread::sleep_for(std::chrono::minutes(1));
        srv.stop();

    }
    catch(const boost::system::system_error& ex)
    {
        std::cerr << "Error: " << ex.code() << ". " << ex.what() << std::endl;
    }
}
