#pragma once
#include "Data.hpp"
#include "Queue.hpp"
#include "EventManager.hpp"

class Process
{
	private:
		EventManager& eventManager;

	public:
		Process(EventManager& eventManager);
		void printProcess(const Data& deviceData);
		void printMultiProcess(Queue& queue);
		void printAlert(Queue& queue);
};
