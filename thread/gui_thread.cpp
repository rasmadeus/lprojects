#include "gui_thread.h"


void GuiThread::test()
{
    GuiThread guiThread;
    for(int i = 0; i < 10; ++i)
    {
        auto res = guiThread.post([i]{ std::cout << "Task " << i << std::endl;});
        res.get();
    }
}

GuiThread::GuiThread()
    : thread(&GuiThread::gui_thread, this)
{
}

GuiThread::~GuiThread()
{
    m_run = false;
    thread.join();
}

void GuiThread::gui_thread()
{
    while(m_run)
    {
        std::packaged_task<void()> task;
        {
            std::lock_guard<std::mutex> guard(mutex);
            if (tasks.empty())
                continue;
            task = std::move(tasks.front());
            tasks.pop_front();
        }
        task();
    }
}
