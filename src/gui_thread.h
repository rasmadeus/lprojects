#ifndef GUITHREAD_H
#define GUITHREAD_H


class GuiThread
{
public:
    static void test();

public:
    GuiThread();
    ~GuiThread();

    std::future<void> post(std::function<void()> f)
    {
        std::packaged_task<void()> task(f);
        auto res = task.get_future();
        std::lock_guard<std::mutex> guard(mutex);
        tasks.push_back(std::move(task));
        return res;
    }

private:
    void gui_thread();

private:
    std::mutex mutex;
    std::deque<std::packaged_task<void()>> tasks;
    std::atomic<bool> m_run{true};
    std::thread thread;
};

#endif // GUITHREAD_H
