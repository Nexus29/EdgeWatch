#include "AlertLogger.hpp"
#include <iostream>

void AlertLogger::onAlert(const AlertEvent& event) {
	std::cout << "[ALERT] Device " << event.deviceId
			  << " -> " << event.message << "\n";
}
