#include "Process.hpp"
#include <iostream>

void Process::process(const Data& deviceData) {
	std::cout << "Device " << deviceData.id
			  << " | CPU: " << deviceData.usage
			  << "% | Temp: " << deviceData.temperature
			  << "°C\n";
}

void Process::multiProcess(Queue& queue) {
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
