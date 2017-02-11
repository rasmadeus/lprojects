#include "call_once.h"


void CallOnce::test()
{
    CallOnce callOnce{5};
    std::once_flag once;
    const auto showOneTime = [&callOnce, &once]{
        std::call_once(once, [&callOnce]{ callOnce.info(); });
        std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
    };

    std::vector<std::thread> threads;
    for(size_t i = 0; i < 10; ++i)
        threads.emplace_back(std::thread(showOneTime));

    for(auto& thread : threads)
        thread.join();
}

CallOnce::CallOnce(int a)
    : a{a}
{
}

void CallOnce::info() const
{
    std::cout << "Info Thread id: " << std::this_thread::get_id() << " a = " << a << std::endl;
}
