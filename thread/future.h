#ifndef FUTURE_H
#define FUTURE_H


class Future
{
public:
    static void test();

public:
    Future(int n, std::launch launch);
    int operator () () const;

private:
    int summ() const;
    int mult() const;

private:
    void show_thread() const;

private:
    int n;
    std::launch launch;
};

#endif // FUTURE_H
