#pragma once
#include "Data.hpp"
#include "Queue.hpp"

class Process
{
	public:
		void process(const Data& deviceData);
		void multiProcess(Queue& queue);
};
