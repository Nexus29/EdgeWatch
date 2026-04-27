#include "AlertLogger.hpp"
#include <iostream>

void AlertLogger::onAlert(const Alert& event) {
	std::cout << "[ALERT] Device " << event.deviceId
			  << " -> " << event.message << "\n";
}
