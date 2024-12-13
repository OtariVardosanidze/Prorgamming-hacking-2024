#include <mutex>
#include <condition_variable>
#include <queue>
#include <optional>
#include <chrono>

template <typename T> 
class Queue {
    private:
    std::queue<T> queue;
    std::mutex locker; // synchronization point
    std::condition_variable element_added;

    public:
    std::optional<T> Wait(bool blocking = true){
        std::unique_lock l(locker);
        
        if (blocking) {
            element_added.wait(l, [this]() { return !queue.empty();});
        } else {
            element_added.wait_for(l, std::chrono::milliseconds(1), [this]() { return !queue.empty();});
        }

        if (queue.empty()) {
            return std::nullopt;
        }

        auto element = std::move(queue.front()); // task_queue.front() = *begin()
        queue.pop(); // task_queue.pop()
        return element;
    }

    void Push(T&& element) { // move element
        std::unique_lock l(locker);
        queue.push(std::move(element));
        element_added.notify_all();
    }

    void Push(const T& element) { // copy element
        std::unique_lock l(locker);
        queue.push(element);
        element_added.notify_all();
    }

    // rvalue именнованный анонимный объект
    // ссылка на ссылку
    // объект без имени

};