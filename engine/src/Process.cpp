#include "Process.hpp"
#include <iostream>

Process::Process(EventManager& em, ApiClient& api)
    : eventManager(em), apiClient(api) {}

void Process::printProcess(const Data& deviceData) {
	std::cout << "Device " << deviceData.id
			  << " | CPU: " << deviceData.usage
			  << "% | Temp: " << deviceData.temperature
			  << "°C\n";
}

void Process::printMultiProcess(Queue& queue) {
	std::cout << "[PROCESSOR] Started processing...\n";
	
	try {
		while (true) {
			Data data = queue.pop();

			std::cout << "[PROCESSOR] Device " << data.id
					  << " | CPU: " << data.usage
					  << "% | Temp: " << data.temperature
					  << "°C\n";
		}
	} catch (const std::runtime_error& e) {
		std::cout << "[PROCESSOR] Shutting down: " << e.what() << "\n";
	} catch (const std::exception& e) {
		std::cerr << "[PROCESSOR] Unexpected error: " << e.what() << "\n";
	}
	
	std::cout << "[PROCESSOR] Stopped\n";
}

void Process::printAlert(Queue& queue) {
	std::cout << "[PROCESSOR] Started processing...\n";
	
	try {
		while (true) {
			Data data = queue.pop();

			std::cout << "[PROCESSOR] Device " << data.id
					  << " | CPU: " << data.usage
					  << "% | Temp: " << data.temperature
					  << "°C\n";

			if (data.temperature > 80.0f) {
			Alert event{
				data.id,
				"High temperature detected!"
			};

			eventManager.notify(event);
		}
		}
	} catch (const std::runtime_error& e) {
		std::cout << "[PROCESSOR] Shutting down: " << e.what() << "\n";
	} catch (const std::exception& e) {
		std::cerr << "[PROCESSOR] Unexpected error: " << e.what() << "\n";
	}
	
	std::cout << "[PROCESSOR] Stopped\n";
}

void Process::printSend(Queue& queue) {
	std::cout << "[PROCESSOR] Started processing...\n";
	
	try {
		while (true) {
			Data data = queue.pop();

			std::cout << "[PROCESSOR] Device " << data.id
					  << " | CPU: " << data.usage
					  << "% | Temp: " << data.temperature
					  << "°C\n";

			apiClient.sendMetrics(data);

			if (data.temperature > 80.0f) {
			Alert event{
				data.id,
				"High temperature detected!"
			};

			eventManager.notify(event);
			apiClient.sendAlert(event);
		}
		}
	} catch (const std::runtime_error& e) {
		std::cout << "[PROCESSOR] Shutting down: " << e.what() << "\n";
	} catch (const std::exception& e) {
		std::cerr << "[PROCESSOR] Unexpected error: " << e.what() << "\n";
	}
	
	std::cout << "[PROCESSOR] Stopped\n";
}
