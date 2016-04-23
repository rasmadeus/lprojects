#include "utils.h"
#include "accumulate.h"
#include "stack.h"
#include "call_once_example.h"
#include "producer.h"

using namespace std;

int main()
{
    test_parallel_accumulate();
    test_stack();
    test_singleton();
    test_producer();
    return 0;
}
