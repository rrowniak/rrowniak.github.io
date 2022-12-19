#include <iostream>
#include "ReqResp.h"
#include "ThreadPool.hpp"

#include <chrono>
#include <thread>
#include <vector>
#include <future>
#include <cstring>

constexpr size_t SampleN = 100000;
constexpr char filename[] = "data.txt";

class Timer
{
public:
    Timer(const size_t sampleN_)
        : sampleN{sampleN_}
        , start{std::chrono::high_resolution_clock::now()}
    { }
    ~Timer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Waited " << elapsed.count() << " ms, avg " << sampleN * 1000.0 / elapsed.count() << " trans/sec\n";
    }
private:
    const size_t sampleN;
    std::chrono::high_resolution_clock::time_point start;
};

void PrintReqProcStats()
{
    auto sl = RequestProcessor::GetSleepTotal();
    auto yi = RequestProcessor::GetYieldNo();
    auto no = RequestProcessor::GetRequestsNo();

    std::cout << "Total sleep: " << sl << " ms, # yield: " << yi
        << ", # requests: " << no << "\n";
}

void Experiment_1_single_threaded()
{
    std::cout << "Running " << __FUNCTION__ << "\n";

    RequestGenerator gen{SampleN};
    Timer t{SampleN};
    Request r;
    double sum = 0;
    Response resp;
    RequestProcessor p{filename};
    RequestProcessor::ResetCounter();
    while (gen.GetNext(r)) {
        p.Process(r, resp);

        sum += resp.result;
    }

    std::cout << "Control result: " << sum << "\n";
    PrintReqProcStats();
}

void Experiment_2_task(const Request& r, const RequestProcessor& p, std::promise<Response>&& prom)
{
    Response resp;
    p.Process(r, resp);
    prom.set_value(resp);
}

void Experiment_2_thread_per_req()
{
    std::cout << "Running " << __FUNCTION__ << "\n";

    RequestGenerator gen{SampleN};
    Timer t{SampleN};
    Request r;
    double sum = 0;
    RequestProcessor p{filename};
    RequestProcessor::ResetCounter();

    std::vector<std::thread> tasks;
    std::vector<std::future<Response>> futures;

    bool interrupted = false;
    int thread_count = 0;

    try {
        while (gen.GetNext(r)) {
            std::promise<Response> promises;
            futures.push_back(promises.get_future());
            tasks.emplace_back(Experiment_2_task, r, p, 
                std::move(promises));

            ++thread_count;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Experiment interrupted - exception thrown: "
            << ex.what() << "\n";
        std::cerr << "Only " << thread_count << " threads created\n";
        interrupted = true;
    }

    if (interrupted) {
        for(auto& task : tasks) {
            task.join();
        }
        return;
    }

    for (auto& f : futures) {
        sum += f.get().result;
    }

    for(auto& task : tasks) {
        task.join();
    }

    std::cout << "Control result: " << sum << "\n";
    PrintReqProcStats();
}

// run MaxThreadNum workers, wait for all, then run next MaxThreadNum and so on...
void Experiment_3_thread_per_req_with_throttle(const size_t MaxThreadNum)
{
    std::cout << "Running " << __FUNCTION__ << " for " << MaxThreadNum << " threads\n";

    RequestGenerator gen{SampleN};
    Timer t{SampleN};
    Request r;
    double sum = 0;
    RequestProcessor p{filename};
    RequestProcessor::ResetCounter();

    bool in_progress = true;

    std::vector<std::thread> tasks;
    tasks.reserve(MaxThreadNum);

    std::vector<std::future<Response>> futures;
    futures.reserve(MaxThreadNum);

    while (in_progress) {
        futures.clear();
        tasks.clear();

        size_t i = 0;
        for (; i < MaxThreadNum && gen.GetNext(r); ++i) {
            std::promise<Response> promises;
            futures.push_back(promises.get_future());
            tasks.emplace_back(Experiment_2_task, r, p, std::move(promises));
        }

        in_progress = (i == MaxThreadNum);

        for (auto& f : futures) {
            sum += f.get().result;
        }

        for(auto& task : tasks) {
            task.join();
        }
    }

    std::cout << "Control result: " << sum << "\n";
    PrintReqProcStats();
}

void Experiment_4_thread_pool(const size_t MaxThreadNum)
{
    std::cout << "Running " << __FUNCTION__ << " for " << MaxThreadNum << " threads\n";

    RequestGenerator gen{SampleN};
    Timer t{SampleN};

    RequestProcessor p{filename};
    RequestProcessor::ResetCounter();

    thread_pool<std::function<Response()>, Response> pool(MaxThreadNum);

    Request r;
    while (gen.GetNext(r)) {

        auto fun = [&p, r]() {
            Response resp;
            p.Process(r, resp);
            return resp;
        };

        pool.add_task(fun);
    }

    using namespace std::chrono_literals;

    double sum = 0;
    std::pair<size_t, Response> result;
    for (size_t i = 0; i < SampleN;) {
        if (!pool.consume_result(result)) {
            std::this_thread::sleep_for(1ms);
            continue;
        }

        sum += result.second.result;
        ++i;
    }

    std::cout << "Control result: " << sum << "\n";
    PrintReqProcStats();
}

void Experiment_5_thread_pool_io_aware(const size_t MaxThreadNum, 
    const size_t RunningThreadsLimit)
{
    std::cout << "Running " << __FUNCTION__ << " for " << MaxThreadNum << " threads\n";

    RequestGenerator gen{SampleN};
    Timer t{SampleN};

    thread_pool2<std::function<Response()>, Response> 
        pool(MaxThreadNum, RunningThreadsLimit);

    RequestProcessor p{filename, 
        [&pool]() { pool.io_begin();},
        [&pool]() { pool.io_end();}};
    
    RequestProcessor::ResetCounter();

    Request r;
    while (gen.GetNext(r)) {

        auto fun = [&p, r]() {
            Response resp;
            p.Process(r, resp);
            return resp;
        };

        pool.add_task(fun);
    }

    using namespace std::chrono_literals;

    double sum = 0;
    size_t dump_cnt;
    std::pair<size_t, Response> result;
    for (size_t i = 0; i < SampleN;) {
        if (!pool.consume_result(result)) {
            std::this_thread::sleep_for(1ms);
            ++dump_cnt;
            if (dump_cnt % 5000 == 0) {
                pool.dump();
            }
            continue;
        }

        sum += result.second.result;
        ++i;
    }

    std::cout << "Control result: " << sum << "\n";
    PrintReqProcStats();
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage processing_pipeline <exp_num1> .. <exp_numN>\n";
        std::cout << "e.g. ./processing_pipeline 6 3 1\n";
        std::cout << "Available experiments:\n";
        std::cout << "1 - Experiment_1_single_threaded()\n";
        std::cout << "2 - Experiment_2_thread_per_req() (might be aborted!!!)\n";
        std::cout << "3 - Experiment_3_thread_per_req_with_throttle(100)\n";
        std::cout << "4 - Experiment_3_thread_per_req_with_throttle(50)\n";
        std::cout << "5 - Experiment_3_thread_per_req_with_throttle(16)\n";
        std::cout << "6 - Experiment_3_thread_per_req_with_throttle(std::thread::hardware_concurrency())\n";
        std::cout << "7 - Experiment_4_thread_pool(100)\n";
        std::cout << "8 - Experiment_4_thread_pool(std::thread::hardware_concurrency() * 4)\n";
        std::cout << "9 - Experiment_4_thread_pool(std::thread::hardware_concurrency() * 2)\n";
        std::cout << "10 - Experiment_4_thread_pool(std::thread::hardware_concurrency())\n";
        std::cout << "11 - Experiment_4_thread_pool(std::thread::hardware_concurrency() / 2)\n";
        std::cout << "12 - Experiment_5_thread_pool_io_aware(std::thread::hardware_concurrency() * 8, std::thread::hardware_concurrency());\n";

        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        try {

            if (strcmp(argv[i], "1") == 0) {
                Experiment_1_single_threaded();
                continue;
            }

            if (strcmp(argv[i], "2") == 0) {
                // App will crash as too many threads are created: Thread 1 "processing_pipe" received signal SIGABRT, Aborted.
                Experiment_2_thread_per_req();
                continue;
            }

            if (strcmp(argv[i], "3") == 0) {
                Experiment_3_thread_per_req_with_throttle(100);
                continue;
            }

            if (strcmp(argv[i], "4") == 0) {
                Experiment_3_thread_per_req_with_throttle(50);
                continue;
            }

            if (strcmp(argv[i], "5") == 0) {
                Experiment_3_thread_per_req_with_throttle(16);
                continue;
            }
            
            if (strcmp(argv[i], "6") == 0) {
                Experiment_3_thread_per_req_with_throttle(std::thread::hardware_concurrency());
                continue;
            }

            if (strcmp(argv[i], "7") == 0) {
                Experiment_4_thread_pool(100);
                continue;
            }
            
            if (strcmp(argv[i], "8") == 0) {
                Experiment_4_thread_pool(std::thread::hardware_concurrency() * 4);
                continue;
            }
            
            if (strcmp(argv[i], "9") == 0) {
                Experiment_4_thread_pool(std::thread::hardware_concurrency() * 2);
                continue;
            }

            if (strcmp(argv[i], "10") == 0) {
                Experiment_4_thread_pool(std::thread::hardware_concurrency());
                continue;
            }

            if (strcmp(argv[i], "11") == 0) {
                Experiment_4_thread_pool(std::thread::hardware_concurrency() / 2);
                continue;
            }

            if (strcmp(argv[i], "12") == 0) {
                Experiment_5_thread_pool_io_aware(std::thread::hardware_concurrency() * 8,
                    std::thread::hardware_concurrency());
                continue;
            }

            std::cerr << "No such experiment - skipping...\n";

        } catch (const std::exception& ex) {
            std::cerr << "Exception caught in main function: " << ex.what() << "\n";
            return 1;
        } catch (...) {
            std::cerr << "Unknown exception caught in main function\n";
        }
    }
    return 0;
}
