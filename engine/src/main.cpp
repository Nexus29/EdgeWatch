#include "Device.hpp"
#include "Process.hpp"
#include "Queue.hpp"
#include "EventManager.hpp"
#include "AlertLogger.hpp"

#include <thread>
#include <vector>
#include <chrono>

void runDevice(int id, Queue& queue) {
	Device device(id);

	while (true) {
		queue.push(device.deviceData());
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

int main() {
	Queue queue;
	EventManager eventManager;

	// Observer
	AlertLogger logger;
	eventManager.subscribe(&logger);

	Process processor(eventManager);

	std::thread processorThread(&Process::printAlert, &processor, std::ref(queue));

	std::vector<std::thread> devices;

	for (int i = 1; i <= 3; i++) {
		devices.emplace_back(runDevice, i, std::ref(queue));
	}

	for (auto& t : devices) t.join();
	processorThread.join();

	return 0;
}
// valgrind --tool=helgrind --log-file=report.log --suppressions=helgrind.supp ./build/core
