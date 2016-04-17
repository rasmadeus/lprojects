#include "utils.h"
#include "accumulate.h"
#include "stack.h"
#include "call_once_example.h"

using namespace std;

int main()
{
    test_parallel_accumulate();
    test_stack();
    test_singleton();
    return 0;
}
