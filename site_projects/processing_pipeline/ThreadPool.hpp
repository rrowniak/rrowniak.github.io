#pragma once

#include <functional>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <memory>
#include <exception>
#include <future>
#include <mutex>
#include <queue>
#include <assert.h>

template <typename T>
class multithreaded_queue {
public:
    void push(T&& value) {
        std::unique_lock<std::mutex> lock(mutex);
        
        q.push(std::move(value));
    }

    bool pop(T& v) {
        std::unique_lock<std::mutex> lock(mutex);

        if (q.empty()) {
            return false;
        }

        v = q.front();
        q.pop();
        
        return true;
    }
    bool empty() {
        std::unique_lock<std::mutex> lock(mutex);

        return q.empty();
    }
private:
    std::queue<T> q;
    std::mutex mutex;
};

template <typename T>
class blocking_queue {
public:
    blocking_queue(size_t max_size_)
        : max_size{max_size_}
        , q(max_size)
    { }

    void push(T value) {
        std::unique_lock<std::mutex> lk(mutex);
        
        if (is_full()) {
            cv.wait(lk, [this]() { return !is_full(); });
        } else {
            add(std::move(value));
        }
    }

    template <typename Iter>
    Iter push_range(Iter begin, Iter end)
    {
        std::unique_lock<std::mutex> lk(mutex);

        for (; begin != end && !is_full(); ++begin) {
            add(*begin);
        }

        return begin;
    }

    bool pop(T& v) {
        std::unique_lock<std::mutex> lk(mutex);

        if (front == tail) {
            return false;
        }

        v = q[tail++];
        tail %= max_size;

        lk.unlock();
        cv.notify_one();
        
        return true;
    }

    template <typename Iter>
    Iter pop_range(Iter begin, Iter end)
    {
        std::unique_lock<std::mutex> lk(mutex);

        for (; (begin != end) && front != tail; ++begin)
        {
            *begin = q[tail++];
            tail %= max_size;
        }

        lk.unlock();
        cv.notify_one();

        return begin;
    }

    bool empty() {
        std::unique_lock<std::mutex> lock(mutex);

        return front == tail;
    }
private:
    const size_t max_size;

    std::mutex mutex;
    std::condition_variable cv;
    size_t front = 0;
    size_t tail = 0;
    std::vector<T> q;

    inline bool is_full() const
    {
        return (front + 1) % max_size == tail;
    }

    inline void add(T&& value)
    {
        q[front++] = std::move(value);
        front %= max_size;
    }

    inline void add(const T& value)
    {
        q[front++] = value;
        front %= max_size;
    }
};

template <typename TaskT, typename ResultT>
class thread_pool {
public:
    thread_pool(size_t n_threads)
    {
        threads.reserve(n_threads);

        for (size_t i = 0; i < n_threads; ++i)
        {
            threads.push_back(std::thread{&thread_pool::thread_worker, this});
        }
    }
    
    ~thread_pool()
    {
        finished.store(true);
        
        cv.notify_all();

        for (auto& t : threads) {
            t.join();
        }
    }

    size_t add_task(TaskT&& task)
    {
        std::unique_lock<std::mutex> lk(mutex);
        jobs.push(std::make_pair(task_id, std::move(task)));

        cv.notify_one();

        ++cnt_tasks;

        return task_id++;
    }

    bool consume_result(std::pair<size_t, ResultT>& result)
    {
        auto cons = results.pop(result);

        if (cons) {
            ++cnt_consumed;
        }
        return cons;
    }

    void dump()
    {
        std::cout << "cnt_tasks=" << cnt_tasks.load() << ", "
            << "cnt_tasks_exec=" << cnt_tasks_exec.load() << ", "
            << "cnt_consumed=" << cnt_consumed.load() << ","
            << "jobs.size()=" << jobs.size() << "\n";
    }
private:
    std::atomic_bool finished{false};  
    std::vector<std::thread> threads;
    size_t task_id = 0;
    
    std::condition_variable cv;
    std::mutex mutex;
    std::queue<std::pair<size_t, TaskT>> jobs;

    multithreaded_queue<std::pair<size_t, ResultT>> results;

    std::atomic<size_t> cnt_tasks{0}, cnt_tasks_exec{0}, cnt_consumed{0};

    void thread_worker()
    {
        while (!finished) {
            std::unique_lock<std::mutex> lk(mutex);

            if (!jobs.empty()) {
                auto job = jobs.front();
                jobs.pop();               
                lk.unlock();

                auto r = job.second();

                results.push(std::make_pair(job.first, r));
            } else {
                cv.wait(lk);
            }
        }
    }
};

template <typename TaskT, typename ResultT>
class thread_pool2 {
public:
    thread_pool2(size_t n_threads)
        : max_running{n_threads}
        , results{10000}
    {
        threads.reserve(n_threads);

        for (size_t i = 0; i < n_threads; ++i)
        {
            threads.push_back(std::thread{&thread_pool2::thread_worker, this});
        }
    }

    thread_pool2(size_t n_threads, size_t max_running_)
        : max_running{max_running_}
        , results{10000}
    {
        threads.reserve(n_threads);

        for (size_t i = 0; i < n_threads; ++i)
        {
            threads.push_back(std::thread{&thread_pool2::thread_worker, this});
        }
    }
    
    ~thread_pool2()
    {
        finished.store(true);

        {
            std::unique_lock<std::mutex> lk(mutex);
            running_no = 0;
        }
        
        cv.notify_all();

        for (auto& t : threads) {
            t.join();
        }
    }

    void io_begin()
    {
        assert(running_no != 0);

        std::unique_lock<std::mutex> lk(mutex);
        --running_no;
        ++io_sleeping_no;
        cv.notify_one();
    }

    void io_end()
    {
        std::unique_lock<std::mutex> lk(mutex);
        while (running_no > max_running) 
            cv.wait(lk);

        ++running_no;
        --io_sleeping_no;
    }

    size_t add_task(TaskT&& task)
    {
        std::unique_lock<std::mutex> lk(mutex);
        jobs.push(std::make_pair(task_id, std::move(task)));

        cv.notify_one();

        ++cnt_tasks;

        return task_id++;
    }

    bool consume_result(std::pair<size_t, ResultT>& result)
    {
        auto cons = results.pop(result);

        if (cons) {
            ++cnt_consumed;
        }
        return cons;
    }

    void dump()
    {
        std::cout << "cnt_tasks=" << cnt_tasks.load() << ", "
            << "cnt_tasks_exec=" << cnt_tasks_exec.load() << ", "
            << "cnt_consumed=" << cnt_consumed.load() << ","
            << "jobs.size()=" << jobs.size() << "\n";
    }
private:
    std::atomic_bool finished{false};
    const size_t max_running;    
    std::vector<std::thread> threads;
    size_t task_id = 0;
    
    std::condition_variable cv;
    std::mutex mutex;
    std::queue<std::pair<size_t, TaskT>> jobs;
    size_t running_no = 0;
    size_t io_sleeping_no = 0;

    blocking_queue<std::pair<size_t, ResultT>> results;

    std::atomic<size_t> cnt_tasks{0}, cnt_tasks_exec{0}, cnt_consumed{0};

    void thread_worker()
    {
        while (!finished) {
            std::unique_lock<std::mutex> lk(mutex);

            if (!jobs.empty()) {
                auto job = jobs.front();
                jobs.pop(); 
                ++running_no;               
                lk.unlock();    

                ++cnt_tasks_exec;

                auto r = job.second();

                results.push(std::make_pair(job.first, r));
                lk.lock();
                --running_no;
            } else {
                if (io_sleeping_no)
                    cv.notify_one();
                do {
                    cv.wait(lk);
                } while (running_no > max_running);
            }
        }
    }
};
