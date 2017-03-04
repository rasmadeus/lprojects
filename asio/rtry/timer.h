#ifndef TIMER_H
#define TIMER_H

namespace timer
{
    void wait(long seconds)
    {
        boost::asio::io_service io;
        boost::asio::deadline_timer timer{io, boost::posix_time::seconds(seconds)};
        timer.wait();
    }

    void test()
    {
        const long seconds = 2;
        wait(seconds);
        std::cout << "Wait for " << seconds << std::endl;
    }
}

#endif // TIMER_H
