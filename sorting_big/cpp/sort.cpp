#include <algorithm>
#include <cstdint>
#include <random>
#include <chrono>
#include <iostream>
#include <assert.h>

class Timer
{
public:
    Timer() : beg{clock::now()}
    { }
    ~Timer() {
        auto diff = clock::now() - beg;
        std::cout << "Time elapsed: " 
            << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " ms\n";
    }
private:
    using clock = std::chrono::high_resolution_clock;
    clock::time_point beg;
};

struct Data
{
    uint64_t id;
    uint64_t value;
};

template<typename RndEngine>
struct DataGen
{
    RndEngine e;
    Data operator()() {
        auto v = e();
        return {v + 10, v};
    }
};

std::vector<Data> Generate(size_t amount)
{
    std::cout << "Building " << amount << " records...\n";
    Timer t;
    DataGen<std::minstd_rand> generator;
    std::vector<Data> d(amount);
    std::generate(std::begin(d), std::end(d), generator);
    return d;
}

struct Cmp
{
    bool operator()(const Data& d1, const Data& d2) const noexcept {
        return d1.value < d2.value;
    }
};

size_t RecordsNum = 100000000;

int main(int argc, char** argv)
{
    if (argc > 1) {
        RecordsNum = atol(argv[1]);
    }
    /*auto cmp =  [](const Data& d1, const Data& d2) {
        return d1.value < d2.value;
    };*/
    Cmp cmp;

    auto data = Generate(RecordsNum);

    // assert(!std::is_sorted(std::begin(data), std::end(data), cmp));

    {
        std::cout << "Sorting " << data.size() << " elements...\n";
        Timer t;
        std::sort(std::begin(data), std::end(data), cmp);
        //std::stable_sort(std::begin(data), std::end(data), cmp);
    }

    {
        std::cout << "Checking whether the collection is sorted...\n";
        Timer t;
        bool sorted = std::is_sorted(std::begin(data), std::end(data), cmp);
        if (!sorted) {
            std::cout << "Collection is not sorted!\n";
        }
    }
    return 0;
}
