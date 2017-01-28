#ifndef FUTURE_H
#define FUTURE_H


class Future
{
public:
    static void test();

public:
    Future(int n);
    int operator () () const;

private:
    int summ() const;
    int mult() const;

private:
    void show_thread() const;

private:
    int n;
};

#endif // FUTURE_H
