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
		std::atomic<bool> finished{false};

	public:
		void push(const Data& data);
		Data pop();
		void shutdown();

};
