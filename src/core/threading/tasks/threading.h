#pragma once
#include "tasks.h"
#include "thread_pool.h"

namespace threading {

extern ThreadPool* tp;
void InitializeThreadPool();

template<typename F, typename... Args> // pack
auto PostTask(F &&f, Args &&... args) { // unpack
    InitializeThreadPool();

    auto wrapped = std::bind(std::forward<F>(f), std::forward<Args>(args)...); // f(10), f(1.1), 
    auto th = tp->AddTask(std::make_unique<FuncTask>(wrapped));

    return th;
}



}
