#include "Queue.hpp"
#include <stdexcept>

void Queue::push(const Data& data) {
	{
		std::lock_guard<std::mutex> lock(mtx);
		if (!finished) {
			queue.push(data);
		}
	}
	cv.notify_one();
}

Data Queue::pop() {
	std::unique_lock<std::mutex> lock(mtx);
	
	cv.wait(lock, [this] { 
		return !queue.empty() || finished; 
	});
	
	if (finished && queue.empty()) {
		lock.unlock();
		throw std::runtime_error("Queue has been shut down");
	}
	
	Data data = queue.front();
	queue.pop();
	
	return data;
}

void Queue::shutdown() {
	finished = true;
	cv.notify_all();
}
