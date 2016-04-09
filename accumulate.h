#pragma once

template<typename Iterator, typename T>
struct AccumulateBlock
{
    void operator () (Iterator begin, Iterator end, T& result)
    {
        std::cout << "accumulateBlock, thread = " << std::this_thread::get_id() << std::endl;
        result = std::accumulate(begin, end, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator begin, Iterator end, T init)
{
    const auto length = std::distance(begin, end);
    if (length == 0) {
        return init;
    }

    const unsigned long minPerThreads = 25;
    const unsigned long maxThreads = (length + minPerThreads - 1) / minPerThreads;
    const unsigned long numberOfThreads = std::min(maxThreads == 0 ? 2 : maxThreads, maxThreads);
    const unsigned long blockSize = length / numberOfThreads;

    std::vector<T> results(numberOfThreads);
    std::vector<std::thread> threads(numberOfThreads - 1);

    auto blockBegin = begin;
    for(unsigned long i = 0; i < numberOfThreads - 1; ++i) {
        auto blockEnd = blockBegin;
        std::advance(blockEnd, blockSize);
        threads[i] = std::thread(AccumulateBlock<Iterator, T>(), blockBegin, blockEnd, std::ref(results[i]));
        blockBegin = blockEnd;
    }

    AccumulateBlock<Iterator, T>()(blockBegin, end, results[numberOfThreads - 1]);

    for(auto& thread : threads) {
        thread.join();
    }

    return std::accumulate(results.begin(), results.end(), init);
}

void test_parallel_accumulate()
{
    int numberOfValues = 1000;
    std::vector<int> v(numberOfValues);
    for(int i = 0; i < numberOfValues; ++i) {
        v[i] = i;
    }

    std::cout << "testParallelAccumulate, result =  " << parallel_accumulate(v.begin(), v.end(), 1) << std::endl;
}
