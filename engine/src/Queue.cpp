#include "Queue.hpp"

void Queue::push(const Data& data) {
    std::lock_guard<std::mutex> lock(mtx);
    queue.push(data);
    cv.notify_one();
}

Data Queue::pop() {
    std::unique_lock<std::mutex> lock(mtx);

    cv.wait(lock, [this] { return !queue.empty(); });

    Data data = queue.front();
    queue.pop();

    return data;
}