#pragma once
#include "tasks.h"
#include "thread_pool.h"

namespace threading {

enum class Thread{
    UI,
    NETWORK,
    OTHERS
};

void InitializeThreadPool();
ThreadPool* GetThreadPool(Thread name);
ThreadPoolMain* GetMainThreadPool();


template<typename F, typename... Args> // pack
auto PostTask(Thread name, F &&f, Args &&... args) { // unpack
    InitializeThreadPool();

    auto wrapped = std::bind(std::forward<F>(f), std::forward<Args>(args)...); // f(10), f(1.1),

    switch (name) 
    {
    case Thread::UI:
        return GetMainThreadPool()->AddTask(std::make_unique<FuncTask>(wrapped));
    case Thread::OTHERS: 
        return GetThreadPool(name)->AddTask(std::make_unique<FuncTask>(wrapped));
    case Thread::NETWORK:
        return GetThreadPool(name)->AddTask(std::make_unique<FuncTask>(wrapped));
    }

}

template<typename F, typename... Args> // pack
auto PostTask(F &&f, Args &&... args) { // unpack
    return PostTask(Thread::OTHERS, std::forward<F>(f), std::forward<Args>(args)...);
}

}
