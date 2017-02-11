#ifndef CONDVAREXAMPLE_H
#define CONDVAREXAMPLE_H


class CondVarExample
{
public:
    static void test();

public:
    void set_data(int value);
    void process_data();

private:
    void log(const std::string& msg) const;

private:
    std::mutex mutex;
    std::condition_variable data_ready;
    std::vector<int> data;

    int summ{0};
};

#endif // CONDVAREXAMPLE_H
