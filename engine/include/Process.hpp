#pragma once
#include "Data.hpp"
#include "Queue.hpp"
#include "ApiClient.hpp"
#include "EventManager.hpp"

class Process
{
	private:
		EventManager& eventManager;
		ApiClient& apiClient;

	public:
		Process(EventManager& eventManager);
		Process(EventManager& eventManager, ApiClient& apiClient);
		void printProcess(const Data& deviceData);
		void printMultiProcess(Queue& queue);
		void printAlert(Queue& queue);
		void printSend(Queue& queue);
};
