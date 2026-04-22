#pragma once
#include "Data.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>

class Queue {
	public:
		void push(const Data& data);
		Data pop();

	private:
		std::queue<Data> queue;
		std::mutex mtx;
		std::condition_variable cv;
};