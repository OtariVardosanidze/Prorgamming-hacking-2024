#include "command_handlers/process_handler.h"
#include "../core/threading/tasks/thread_pool.h"
#include "../core/threading/tasks/threading.h"

class PrintTask : public Task {
public:
    explicit PrintTask(int id) : task_id(id) {}
    void Process() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "Task " << task_id << " is processed in thread " <<
        std::this_thread::get_id() << std::endl;
    }
private:
    int task_id;
};

void Test(int i) {
    std::cout << i << std::endl;
}

void onIdle() {
    std::cout << "Task " << " is processed in MAIN thread " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    threading::PostTask(threading::Thread::UI, Test, 5);
}

int main(){

    threading::InitializeThreadPool();


    // Doing other initialization.

    threading::GetMainThreadPool()->OnIdle(onIdle);
    threading::GetMainThreadPool()->Run();


    // ThreadPool tp(20);

    // auto time_begin = std::chrono::system_clock::now();

    // std::vector<std::shared_ptr<TaskHandle>> ths;
    // size_t n = tp.GetCount();
    // for (size_t i = 0; i < n ; i++ ){
    //     // auto th = tp.AddTask(std::make_unique<PrintTask>(i));

    //     auto th = tp.AddTask(std::make_unique<FuncTask>([i, n]() { // lambda func 
    //     std::cout << i << " done" << std::endl;
    //     }));

    //     ths.push_back(th);
    // }

    // for (auto& th : ths){
    //     th->wait();
    // }

    // auto time_end = std::chrono::system_clock::now();
    // auto gap = time_end - time_begin;
    // std::cout << "All tasks have been completed: " << std::endl;

    return 0;
}