#include "pack_task.h"


void PackTask::test()
{
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
    PackTask pack_task{{1, 2, 3, 4, 5}};

    std::packaged_task<int()> summ(std::bind(&PackTask::summ, &pack_task));
    auto summ_future = summ.get_future();
    summ();
    std::cout << "Summ result: " << summ_future.get() << std::endl;

    std::packaged_task<int()> mult(std::bind(&PackTask::mult, &pack_task));
    auto mult_future = mult.get_future();
    std::thread mult_thread(std::move(mult));
    std::cout << "Mult result: " << mult_future.get() << std::endl;
    mult_thread.join();

    std::packaged_task<void()> exception(std::bind(&PackTask::exception, &pack_task));
    auto exception_example = exception.get_future();
    std::thread exception_thread(std::move(exception));
    try
    {
        exception_example.get();
    }
    catch(const std::runtime_error& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    exception_thread.join();
}

PackTask::PackTask(const std::vector<int>& data)
    : data(data)
{
}

int PackTask::summ() const
{
    std::cout << "Summ thread id: " << std::this_thread::get_id() << std::endl;
    return std::accumulate(data.begin(), data.end(), 0);
}

int PackTask::mult() const
{
    std::cout << "Mult thread id: " << std::this_thread::get_id() << std::endl;
    return std::accumulate(data.begin(), data.end(), 1, std::multiplies<int>());
}

void PackTask::exception() const
{
    throw std::runtime_error("Exception example");
}
