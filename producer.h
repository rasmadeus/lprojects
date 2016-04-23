#pragma once

class Producer
{
public:
     void push()
     {
         for(auto i = 0; i < 1000; ++i)
         {
            const auto value = rand() % 1000;
            std::lock_guard<std::mutex> guard(_mutex);
            _data.push(value);
            std::cout << "Data was pushed: " << value << " This thread id = " << std::this_thread::get_id() << std::endl;
            _condition.notify_one();
         }
         _process = false;
     }

     void read()
     {
         while(_process)
         {
             std::unique_lock<std::mutex> guard(_mutex);
             _condition.wait(guard, [this](){ return !_data.empty(); });
             const auto& value = _data.front();
             std::cout << "Value was read: " << value << "This thread id = " << std::this_thread::get_id() << std::endl;
             _data.pop();
         }
     }

private:
    std::atomic<bool> _process = true;
    std::mutex _mutex;
    std::queue<int> _data;
    std::condition_variable _condition;
};

void test_producer()
{
    auto producer = Producer();
    std::thread reader(&Producer::read, &producer);
    std::thread pusher(&Producer::push, &producer);
    pusher.join();
    reader.join();
}
