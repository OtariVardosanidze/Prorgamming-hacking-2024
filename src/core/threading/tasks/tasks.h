#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <functional>
 
class TaskHandle {
    private:
    friend class AwaitableTask;

    std::mutex m;
    std::condition_variable condition;
    bool task_ready = false;

    public:
    void wait();
};
 
class Task {
    public:
    virtual ~Task() = default;
    virtual void Process() = 0;
};

class FuncTask : public Task {
    public:
    FuncTask(std::function<void()> fun);

    void Process() override;
    
    private:
    std::function<void()> fun;
};

class AwaitableTask : public Task {
    private:
    std::unique_ptr<Task> task;
    std::weak_ptr<TaskHandle> handle;
    public:
    AwaitableTask(std::unique_ptr<Task> task, std::shared_ptr<TaskHandle> handle) : task(std::move(task)), handle(handle) {};
    void Process() override;
};