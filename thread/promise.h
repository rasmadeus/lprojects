#ifndef PROMISE_H
#define PROMISE_H


class Promise
{
public:
    static void test();

public:
    void calc(const std::vector<int>& data, std::promise<int> res_promise) const;
    void calc_exception(std::promise<int> res) const;

private:
    int accumulate(const std::vector<int>& data) const;
    int exception_test() const;
};

#endif // PROMISE_H
