#pragma once
#include "tasks.h"
#include "thread_pool.h"

namespace threading {

ThreadPool* tp = nullptr;

void InitializeThreadPool(){
    if (!tp){
        tp = new ThreadPool(4);
    }
}


}