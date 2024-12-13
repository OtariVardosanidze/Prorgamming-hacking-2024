#pragma once
#include "thread_pool.h"
#include "tasks.h"

std::unique_ptr<Task> ThreadPool::WaitTask() {
  auto t = std::move(*tasks_queue.Wait());
  return t; // get value from optional
}

void ThreadPool::DoTask(size_t tn) {
  while (!quitting) {
    auto task = WaitTask();
    task->Process();
  }
}

std::shared_ptr<TaskHandle> ThreadPool::AddTask(std::unique_ptr<Task> task) {
  auto th = std::make_shared<TaskHandle>();
  auto at = std::make_unique<AwaitableTask>(std::move(task), th);
  tasks_queue.Push(std::move(at));
  return th;
}

void ThreadPool::Quit() {
  quitting = true;
  class QuitTask : public Task {
    void Process() override {}
  };

  for (size_t i = 0; i < threads.size(); i++) {
    AddTask(std::make_unique<QuitTask>());
  }

  for (auto &t : threads) {
    t.join();
  }
}

std::unique_ptr<Task> ThreadPoolMain::WaitTask() {
  auto t = tasks_queue.Wait(false);
  if (!t) {
    return nullptr;
  }
  return *std::move(t);
}

ThreadPoolMain::ThreadPoolMain() = default;
ThreadPoolMain::~ThreadPoolMain() = default;

std::shared_ptr<TaskHandle>
ThreadPoolMain::AddTask(std::unique_ptr<Task> task) {
  auto th = std::make_shared<TaskHandle>();
  auto at = std::make_unique<AwaitableTask>(std::move(task), th);
  tasks_queue.Push(std::move(at));
  return th;
}
void ThreadPoolMain::Quit() {
  quitting = true;
}

void ThreadPoolMain::Run() {
  while (!quitting) {
    auto t = WaitTask();
    if (!t) {
      on_idle();
    } else {
      t->Process();
    }
  }
}

void ThreadPoolMain::OnIdle(std::function<void()> on_idle) {
  this->on_idle = std::move(on_idle);
}