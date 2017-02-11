#include "asynch.h"


void BigCalc::test()
{
    BigCalc big_calc;
    std::cout << big_calc.calc() << std::endl;
    try
    {
        std::cout << big_calc.big_calc() << std::endl;
    }
    catch(const std::runtime_error& ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

int BigCalc::calc() const
{
    auto res = std::async(std::launch::async, &BigCalc::second_step, this);
    const auto first = first_step();
    return first + res.get();
}

int BigCalc::big_calc() const
{
    auto res = std::async(std::launch::async, &BigCalc::big_step, this);
    const auto first = first_step();
    return first + res.get();
}

int BigCalc::first_step() const
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 10;
}

int BigCalc::second_step() const
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 5;
}

int BigCalc::big_step() const
{
    throw std::runtime_error("Big exception");
    return 7;
}
