// перекидывание одной задачи/результата на другую
// с одного потока на другой поток 

#pragma once
#include "thread_pool.h"
#include "tasks.h"


void AwaitableTask::Process(){
    if (auto th = handle.lock()){
        task->Process();

        std::unique_lock l(th->m);
        th->task_ready = true;
        th->condition.notify_one();
    }
}


void TaskHandle::wait() {
    std::unique_lock l(m);
    condition.wait(l, [this](){return task_ready;});
    // task_ready.wait(l);
}

FuncTask::FuncTask(std::function<void()> f): fun(std::move(f)) {}

void FuncTask::Process(){
    fun();
}