#ifndef PACKTASK_H
#define PACKTASK_H


class PackTask
{
public:
    static void test();

public:
    PackTask(const std::vector<int>& data);
    int summ() const;
    int mult() const;
    void exception() const;

private:
    const std::vector<int> data;
};

#endif // PACKTASK_H
