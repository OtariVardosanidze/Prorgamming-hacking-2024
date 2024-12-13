# pragma once 
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <functional>
#include "tasks.h"
#include "../containers/queue.h"

class ThreadPool {
    private:
    std::vector<std::thread> threads;
    // std::mutex locker;
    // std::condition_variable task_added;
    Queue<std::unique_ptr<Task>> tasks_queue; // use queue instead vector
    bool quitting = false;

    std::unique_ptr<Task> WaitTask();
    void DoTask(size_t tn);

    public:
    explicit ThreadPool(size_t threads_num) {
        for (size_t i = 0; i < threads_num; ++i) {
            threads.push_back(std::thread(&ThreadPool::DoTask, this, i));
        }
    }
    ~ThreadPool() {
        if (!quitting) {
            Quit();
        }
    }
    
    std::shared_ptr<TaskHandle> AddTask(std::unique_ptr<Task> task); 
    void Quit();

    const size_t GetCount(){
        return threads.size();
    }
};

class ThreadPoolMain {
    private:
    std::function<void()> on_idle;
    Queue<std::unique_ptr<Task>> tasks_queue; // use queue instead vector
    bool quitting = false;
    std::unique_ptr<Task> WaitTask();

    public:
    explicit ThreadPoolMain();
    ~ThreadPoolMain();
    
    std::shared_ptr<TaskHandle> AddTask(std::unique_ptr<Task> task); 
    void Quit();
    void Run();
    void OnIdle(std::function<void()> on_idle);
};