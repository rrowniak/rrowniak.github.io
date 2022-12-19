#include "ReqResp.h"

#include <cmath>
#include <cstdio>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <cerrno>
#include <algorithm>

RequestGenerator::RequestGenerator(size_t N_)
    : N{N_}
    , current{0}
{ }

bool RequestGenerator::GetNext(Request& req)
{
    req.id = current++;

    if (current > N) {
        return false;
    }

    return true;
}

uconter RequestProcessor::cnt_sleep_total;
uconter RequestProcessor::cnt_yield;
uconter RequestProcessor::cnt_requests;

RequestProcessor::RequestProcessor(const char* dataFile)
    : data{}
{
    ReadFile(dataFile);
}

RequestProcessor::RequestProcessor(const char* dataFile,
        IOFun io_begin_,
        IOFun io_end_)
    : data{}
    , io_begin{io_begin_}
    , io_end{io_end_}
{
    ReadFile(dataFile);
}
    
void RequestProcessor::Process(const Request& req, Response& r) const
{
    cnt_requests.inc();
    
    auto tmp = req.id * 13;
    double tmpd = static_cast<double>(tmp);
    tmpd = sqrt(tmpd*tmpd + 3.1415 * sin(tmpd * 2 * M_1_PI));
    snprintf(r.text, RespTextSize, "Resp: %f", tmpd);
    r.result = tmpd;
    r.req = req;

    // simulate io operations
    using namespace std::chrono_literals;

    if (req.id % 10000 == 0) {
        cnt_sleep_total.inc_by(1000);
        
        IOBegin();
        std::this_thread::sleep_for(1s);
        IOEnd();
    } else if (req.id % 1000 == 0) {
        cnt_sleep_total.inc_by(88);
        
        IOBegin();
        std::this_thread::sleep_for(88ms);
        IOEnd();
    } else if (req.id % 500 == 0) {
        cnt_sleep_total.inc_by(10);
        
        IOBegin();
        std::this_thread::sleep_for(10ms);
        IOEnd();
    } else if (req.id % 2 == 0) {
        cnt_yield.inc();
        
        // IOBegin();
        std::this_thread::yield();
        // IOEnd();
    }

    // do some copying and text transformations
    r.textSize = std::min(data.size(), RespTextSize);
    std::copy_n(std::begin(data), r.textSize, r.text);
    // replace "v" with "V"
    std::replace(std::begin(r.text), std::begin(r.text) + r.textSize, 'v', 'V');
}

void RequestProcessor::ResetCounter()
{
    cnt_sleep_total.reset();
    cnt_yield.reset();
    cnt_requests.reset();
}

uconter::Type RequestProcessor::GetSleepTotal()
{
    return cnt_sleep_total.get();
}

uconter::Type RequestProcessor::GetYieldNo()
{
    return cnt_yield.get();
}

uconter::Type RequestProcessor::GetRequestsNo()
{
    return cnt_requests.get();
}

void RequestProcessor::ReadFile(const char* dataFile)
{
    std::ifstream in(dataFile, std::ios::in);
    if (in) {
        in.seekg(0, std::ios::end);
        data.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&data[0], data.size());
        in.close();

        return;
    }
  
    throw errno;
}

void RequestProcessor::IOBegin() const
{
    if (io_begin) io_begin();
}

void RequestProcessor::IOEnd() const
{
    if (io_end) io_end();
}