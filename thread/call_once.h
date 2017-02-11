#ifndef CALL_ONCE_H
#define CALL_ONCE_H


class CallOnce
{
public:
    static void test();

public:
    CallOnce(int a);
    void info() const;

private:
    int a;
};

#endif // CALL_ONCE_H
