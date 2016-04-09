#pragma once

class EmptyStack : public std::exception
{
public:
    const char* what() const throw() override { return "Stack is empty"; }
};

template<typename T>
class Stack
{
public:
    Stack() = default;

    Stack(const Stack& other)
    {
        std::lock_guard<std::mutex> auto_locker(other._data_guard);
        _data = other._data;
    }

    Stack& operator = (const Stack&) = delete;

    void push(T value)
    {
        std::lock_guard<std::mutex> auto_locker(_data_guard);
        _data.push(value);
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> auto_locker(_data_guard);
        if (_data.empty()) {
            throw EmptyStack();
        }
        const auto res = std::make_shared<T>(_data.top());
        _data.pop();
        return res;
    }

    void pop(T& value)
    {
        std::lock_guard<std::mutex> auto_locker(_data_guard);
        if (_data.empty()) {
            throw EmptyStack();
        }
        value = _data.pop();
        _data.pop();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> auto_locker(_data_guard);
        return _data.empty();
    }

private:
    std::stack<T> _data;
    mutable std::mutex _data_guard;
};

void _test_stack(Stack<int>& stack)
{
    const auto wait = std::chrono::milliseconds(rand() % 500);
    for(int i = 0; i < 10; ++i) {
        std::cout << "Thread id=" << std::this_thread::get_id() << ". Iteration=" << i << std::endl;
        const auto value = rand() % 500;
        stack.push(value);
        std::cout << "Thread id=" << std::this_thread::get_id() << ". Iteration=" << i << " Pushed value=" << value << std::endl;
        std::this_thread::sleep_for(wait);
        try
        {
            const auto popValue = stack.pop();
            std::cout << "Thread id=" << std::this_thread::get_id() << ". Iteration=" << i << " Poped value=" << *popValue << std::endl;
        }
        catch(const EmptyStack& ex)
        {
            std::cout << "Thread id=" << std::this_thread::get_id() << ". Iteration=" << i << " Exception=" << ex.what() << std::endl;
        }
    }
}

void test_stack()
{
    auto stack = Stack<int>();
    std::vector<std::thread> workers;
    for(int i = 0; i < 10; ++i) {
        workers.push_back(std::thread(_test_stack, std::ref(stack)));
    }
    for(auto& worker : workers) {
        worker.join();
    }
}
