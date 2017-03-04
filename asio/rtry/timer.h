#ifndef TIMER_H
#define TIMER_H

namespace timer
{
    void wait_sync(long seconds)
    {
        boost::asio::io_service io;
        boost::asio::deadline_timer timer{io, boost::posix_time::seconds(seconds)};
        timer.wait();
    }

    void test_sync(long seconds)
    {
        wait_sync(seconds);
        std::cout << "Wait for " << seconds << std::endl;
    }


    void info(long seconds, const boost::system::error_code& ec)
    {
        if (ec)
        {
            std::cout << "Error: " << ec.value() << std::endl;
        }
        else
        {
            std::cout << "Wait async for " << seconds << std::endl;
        }
    }

    void test_async(long seconds)
    {
        boost::asio::io_service io;
        boost::asio::deadline_timer timer{io, boost::posix_time::seconds(seconds)};
        timer.async_wait(std::bind(&info, seconds, std::placeholders::_1));
        io.run();
    }

}

#endif // TIMER_H
