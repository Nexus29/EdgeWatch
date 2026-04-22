#include "Process.hpp"
#include <iostream>

void Process::process(const Data& deviceData) {
	std::cout << "Device " << deviceData.id
			  << " | CPU: " << deviceData.usage
			  << "% | Temp: " << deviceData.temperature
			  << "°C\n";
}
