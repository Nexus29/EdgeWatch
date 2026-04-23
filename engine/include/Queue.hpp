#pragma once
#include "Data.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

class Queue {
	private:
		std::queue<Data> queue;
		mutable std::mutex mtx;
		std::condition_variable cv;
		bool finished = false; ;

	public:
		void push(const Data& data);
		Data pop();
		void shutdown();
		bool isFinished() const {
			std::lock_guard<std::mutex> lock(mtx);
			return finished;
    	}
};
