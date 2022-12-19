#pragma once

#include <atomic>

template <typename T>
class counter
{
public:
    void inc() { ++cnt; }
    void inc_by(T val) { cnt += val; }
    T get() const { return cnt.load(std::memory_order::memory_order_acquire);}
    void reset() { cnt.store(T(), std::memory_order::memory_order_release);}
    
    using Type = T;
private:
    std::atomic<T> cnt;
};

using uconter = counter<unsigned int>;