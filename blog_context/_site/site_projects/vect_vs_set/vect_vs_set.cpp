#include <algorithm>
#include <cstdint>
#include <random>
#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <assert.h>

class Timer
{
public:
    Timer() : beg{clock::now()}
    { }
    ~Timer() {
        auto diff = clock::now() - beg;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
        std::ostringstream ss;
        ss.imbue(std::locale("en_US.UTF-8"));
        ss << "Time elapsed: " << ms << " ms";
        std::cout << ss.str() << std::endl;
    }
private:
    using clock = std::chrono::high_resolution_clock;
    clock::time_point beg;
};

template<typename RndEngine>
struct DataGen
{
    RndEngine e;
    const std::size_t max_val;
    DataGen(std::size_t max_val_) : max_val{max_val_} { }
    std::size_t operator()() {
        std::size_t ret = e();
        return ret % (max_val + 1);
    }
};

std::vector<std::size_t> Generate(std::size_t amount, std::size_t max_val)
{
    DataGen<std::minstd_rand> generator{max_val};
    std::vector<std::size_t> v(amount);
    std::generate(std::begin(v), std::end(v), generator);
    return v;
}

void Generate(std::size_t amount, std::size_t max_val,
    std::vector<std::size_t>& out_v,
    std::set<std::size_t>& out_s)
{
    auto v_tmp = Generate(amount, max_val);
    out_v.swap(v_tmp);
    std::set<std::size_t> s_tmp(std::begin(out_v), std::end(out_v));
    out_s.swap(s_tmp);
}

constexpr std::size_t up_to = 1000000;

int main(int, char**)
{
    std::cout << "Lookup performance comparison between std::vector and std::set" << std::endl;
    std::cout << "Optimization flag: " << OPT_FLAG << std::endl;

    for (std::size_t i = 1; i <= up_to; i *= 10) {
        std::cout << "--------------------------------------------------------------------------" << std::endl;
        std::cout << "Checking results for " << i << " elements..." << std::endl;
        // generate collections first
        std::vector<std::size_t> v;
        std::set<std::size_t> s;
        Generate(i, 2 * i, v, s);
        // generate requests
        std::vector<std::size_t> req = Generate(2 * i, 4 * i);
        // make a test
        volatile std::size_t result; // prevent from optimizing out test code

        std::size_t inner_loop = 2 * up_to / req.size();

        if (i < 100000) // skip this test for bigger numbers
        {
            std::cout << "Testing lookup for unsorted std::vector..." << std::endl;
            Timer t;
            for (size_t j = 0; j < inner_loop; ++j) {
                for (std::size_t item : req) {
                    auto it = std::find(v.begin(), v.end(), item);
                    if (it != v.end()) {
                        result = *it;
                    }
                }
            }
        }

        {
            std::cout << "Testing lookup for sorted std::vector..." << std::endl;
            std::sort(v.begin(), v.end());
            Timer t;
            for (size_t j = 0; j < inner_loop; ++j) {
                for (std::size_t item : req) {
                    auto it = std::lower_bound(v.begin(), v.end(), item);
                    if (it != v.end() && *it == item) {
                        result = *it;
                    }
                }
            }
        }

        {
            std::cout << "Testing lookup for std::set..." << std::endl;
            Timer t;
            for (size_t j = 0; j < inner_loop; ++j) {
                for (std::size_t item : req) {
                    auto it = s.find(item);
                    if (it != s.end()) {
                        result = *it;
                    }
                }
            }
        }

        // prevent from compiler warning
        result = result;
    }

    return 0;
}
