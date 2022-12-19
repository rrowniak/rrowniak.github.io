#pragma once

#include <cstdio>
#include <string>
#include <functional>
#include "counter.hpp"

constexpr size_t RespTextSize = 16384;

struct Request
{
    unsigned int id;
};

struct Response
{
    Request req;
    double result;
    size_t textSize;
    char text[RespTextSize];
};

class RequestGenerator
{
public:
    RequestGenerator(size_t N_);

    bool GetNext(Request& req);
private:
    const size_t N;
    size_t current;
};

// using IOFun =  void (*)();
using IOFun =  std::function<void ()>;

class RequestProcessor
{
public:
    RequestProcessor(const char* dataFile);
    RequestProcessor(const char* dataFile, 
        IOFun io_begin_, IOFun io_end_);
    void Process(const Request& req, Response& r) const;

    static void ResetCounter();
    static uconter::Type GetSleepTotal();
    static uconter::Type GetYieldNo();
    static uconter::Type GetRequestsNo();
private:
    std::string data;

    IOFun io_begin;
    IOFun io_end;

    static uconter cnt_sleep_total;
    static uconter cnt_yield;
    static uconter cnt_requests;

    void ReadFile(const char* dataFile);

    inline void IOBegin() const;
    inline void IOEnd() const;
};