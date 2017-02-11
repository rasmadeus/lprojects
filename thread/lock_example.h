#ifndef LOCK_EXAMPLE_H
#define LOCK_EXAMPLE_H

class Book
{
public:
    static void test();

public:
    Book(const std::string& author);
    void swap(Book& other);

public:
    friend std::ostream& operator << (std::ostream& out, const Book& book);


private:
    mutable std::mutex author_guard;
    std::string author;
};


#endif // LOCK_EXAMPLE_H
