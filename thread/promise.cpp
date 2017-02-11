#include "promise.h"


void Promise::test()
{
    Promise promise;
    std::promise<int> res_promise;
    auto res_future = res_promise.get_future();
    std::thread res_thread{&Promise::calc, &promise, std::vector<int>{1, 3, 4, 5}, std::move(res_promise)};
    std::cout << "Result: " << res_future.get() << std::endl;
    res_thread.join();

    std::promise<int> res_exception;
    auto res_exception_future = res_exception.get_future();
    std::thread res_exception_thread{&Promise::calc_exception, &promise, std::move(res_exception)};
    try
    {
        std::cout << "Promise exception res: " << res_exception_future.get() << std::endl;
    }
    catch(const std::runtime_error& ex)
    {
        std::cout << "Promise exception caught: " << ex.what() << std::endl;
    }

    res_exception_thread.join();
}

void Promise::calc(const std::vector<int>& data, std::promise<int> res_promise) const
{
    const auto res = accumulate(data);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    res_promise.set_value(res);
}

void Promise::calc_exception(std::promise<int> res) const
{
    try
    {
        res.set_value(exception_test());
    }
    catch(...)
    {
        res.set_exception(std::current_exception());
    }
}

int Promise::accumulate(const std::vector<int>& data) const
{
    return std::accumulate(data.begin(), data.end(), 0);
}

int Promise::exception_test() const
{
    throw std::runtime_error("Promise exception test");
    return 0;
}

