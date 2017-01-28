#include "future.h"


void Future::test()
{
    Future{5, std::launch::deferred}();
    Future{6, std::launch::async}();
}

Future::Future(int n, std::launch launch)
    : n{n}
    , launch{launch}
{
}

int Future::operator () () const
{
    auto summ = std::async(launch, &Future::summ, this);
    auto mult = std::async(launch, &Future::mult, this);
    return summ.get() + mult.get();
}

int Future::summ() const
{
    show_thread();
    int summ = 0;
    for(int i = 0; i < n; ++i)
        summ += i;
    return summ;
}

int Future::mult() const
{
    show_thread();
    int mult = 1;
    for(int i = 1; i < n; ++i)
        mult *= i;
    return mult;
}

void Future::show_thread() const
{
    std::cout << "This thread: " << std::this_thread::get_id() << std::endl;
}
