#pragma once
#include "tasks.h"
#include "thread_pool.h"
#include "threading.h"

namespace threading {

ThreadPool* tp_others = nullptr;
ThreadPool* tp_network = nullptr;
ThreadPoolMain* tp_main = nullptr;

void InitializeThreadPool(){
    if (!tp_others){
        tp_others = new ThreadPool(4);
    }
    if (!tp_network){
        tp_network = new ThreadPool(1);
    }
    if (!tp_main) {
        tp_main = new ThreadPoolMain();
    }
}

ThreadPool* GetThreadPool(Thread name) {
    switch (name)
    {
    case Thread::OTHERS:
        return tp_others;
    case Thread::NETWORK:
        return tp_network;
    case Thread::UI:
        return nullptr;
    }
}

ThreadPoolMain* GetMainThreadPool(){
    return tp_main;
}
}