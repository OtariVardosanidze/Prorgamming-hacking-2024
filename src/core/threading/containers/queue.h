#include <mutex>
#include <condition_variable>
#include <queue>
#include <optional>

template <typename T> 
class Queue {
    private:
    std::queue<T> queue;
    std::mutex locker; // synchronization point
    std::condition_variable element_added;

    public:
    std::optional<T> Wait(){
        std::unique_lock l(locker);
        element_added.wait(l, [this]() { return !queue.empty();});
        auto element = std::move(queue.front()); // task_queue.front() = *begin()
        queue.pop(); // task_queue.pop()
        return element;

        // wait timeout {return std::nullopt;}
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