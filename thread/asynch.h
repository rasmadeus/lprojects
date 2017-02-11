#ifndef ASYNCH_H
#define ASYNCH_H


class BigCalc
{
public:
    static void test();

public:
    int calc() const;
    int big_calc() const;

private:
    int first_step() const;
    int second_step() const;
    int big_step() const;
};

#endif // ASYNCH_H
