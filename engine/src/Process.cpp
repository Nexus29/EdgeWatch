#include "Process.hpp"
#include <iostream>

void Process::process(const Data& deviceData) {
	std::cout << "Device " << deviceData.id
			  << " | CPU: " << deviceData.usage
			  << "% | Temp: " << deviceData.temperature
			  << "°C\n";
}

void Process::multiProcess(Queue& queue) {
    while (true) {
        Data data = queue.pop();

        std::cout << "[PROCESSOR] Device " << data.id
                  << " | CPU: " << data.usage
                  << "% | Temp: " << data.temperature
                  << "°C\n";
    }
}
