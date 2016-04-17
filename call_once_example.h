#pragma once

class CallOnceExample
{
public:
    CallOnceExample() = default;

    void init(int value)
    {
        std::call_once(_data_init_flag, &CallOnceExample::init_data, this, value);
    }

    int data() const
    {
        return _data;
    }

private:
    CallOnceExample(const CallOnceExample&) = delete;
    CallOnceExample& operator = (const CallOnceExample&) = delete;

    void init_data(int value)
    {
        _data = value;
        std::cout << "Value was set by thread id = " << std::this_thread::get_id() << std::endl;
    }

private:
    std::once_flag _data_init_flag;
    int _data = 0;
};

void _init(CallOnceExample& callOnceExample)
{
    std::cout << "Thread id = " << std::this_thread::get_id() << std::endl;
    callOnceExample.init(5);
}

void test_singleton()
{
    CallOnceExample callOnceExample;

    std::list<std::thread> threads;
    for(int i = 0; i < 20; ++i) {
        threads.push_back(std::thread(_init, std::ref(callOnceExample)));
    }
    for(auto& thread : threads) {
        thread.join();
    }
}
