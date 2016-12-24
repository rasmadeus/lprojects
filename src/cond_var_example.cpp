#include "cond_var_example.h"

void CondVarExample::test()
{
    CondVarExample condVarExample;

    std::thread producer{[&condVarExample](){
       for(int i = 0; i < 100; ++i)
       {
           condVarExample.set_data(i);
           std::this_thread::sleep_for(std::chrono::milliseconds(50));
       }
    }};

    std::thread consumer{[&condVarExample, &producer](){
            while(producer.joinable())
            {
                condVarExample.process_data();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    };

    producer.join();
    consumer.join();
}

void CondVarExample::set_data(int value)
{
    {
        std::lock_guard<std::mutex> data_guard(mutex);
        data.emplace_back(value);
    }
    data_ready.notify_all();
    log("Data pushed: " + std::to_string(value));
}

void CondVarExample::process_data()
{
    std::unique_lock<std::mutex> data_guard(mutex);
    data_ready.wait(data_guard, [this](){ return !data.empty(); });
    for(const auto value : data)
        summ += value;
    data.clear();
    log("Summ: " + std::to_string(summ));
}

void CondVarExample::log(const std::string& msg) const
{
    std::cout << "Id: " << std::this_thread::get_id() << "; " << msg << std::endl;
}
