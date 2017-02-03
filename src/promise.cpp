#include "promise.h"


void Promise::test()
{
    Promise promise;
    std::promise<int> res_promise;
    auto res_future = res_promise.get_future();
    std::thread res_thread{&Promise::calc, &promise, std::vector<int>{1, 3, 4, 5}, std::move(res_promise)};
    std::cout << "Result: " << res_future.get() << std::endl;
    res_thread.join();
}

void Promise::calc(const std::vector<int>& data, std::promise<int> res_promise) const
{
    const auto res = accumulate(data);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    res_promise.set_value(res);
}

int Promise::accumulate(const std::vector<int>& data) const
{
    return std::accumulate(data.begin(), data.end(), 0);
}
