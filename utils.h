#pragma once

class ThreadGuard
{
public:
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator = (const ThreadGuard&) = delete;
    ThreadGuard(std::thread& thread);
    ~ThreadGuard();

private:
    std::thread& _thread;
};
