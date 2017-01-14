#include "lock_example.h"


void Book::test()
{
    Book first{"First"};
    Book second{"Second"};
    std::cout << first << second;

    const auto swap = [](Book& first, Book& second, std::chrono::milliseconds wait_time){
        for(size_t i = 0; i < 50; ++i)
        {
            std::cout << "Iteration: " << i << " of thread " << std::this_thread::get_id() << std::endl;
            first.swap(second);
            std::this_thread::sleep_for(wait_time);
        }
    };

    std::thread first_thread(swap, std::ref(first), std::ref(second), std::chrono::milliseconds{50});
    std::thread second_thread(swap, std::ref(second), std::ref(first), std::chrono::milliseconds{50});
    first_thread.join();
    second_thread.join();
}

Book::Book(const std::string& author)
    : author(author)
{
}

void Book::swap(Book& other)
{
    if (this != &other)
    {
        std::lock(author_guard, other.author_guard);

        std::lock_guard<std::mutex> this_guard{author_guard, std::adopt_lock};
        std::cout << "Thread: " << std::this_thread::get_id() << " have catched mutex of " << this << std::endl;

        std::lock_guard<std::mutex> other_guard{other.author_guard, std::adopt_lock};
        std::cout << "Thread: " << std::this_thread::get_id() << " have catched mutex of " << &other << std::endl;

        std::swap(author, other.author);
        std::cout << *this << other;
    }
}

std::ostream& operator << (std::ostream& out, const Book& book)
{
    out << "Book: " << book.author << std::endl;
    return out;
}
