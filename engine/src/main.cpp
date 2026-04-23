#include "Device.hpp"
#include "Process.hpp"
#include "Queue.hpp"
#include "EventManager.hpp"
#include "AlertLogger.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <csignal>
#include <atomic>

std::atomic<bool> running{true};

void signalHandler(int) {
	running = false;
}

void runDevice(int id, Queue& queue) {
	Device device(id);

	while (running) {
		queue.push(device.deviceData());
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

int main() {
	struct sigaction sa;
	sa.sa_handler = signalHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, nullptr);
	sigaction(SIGTERM, &sa, nullptr);
	
	Queue queue;
	EventManager eventManager;

	AlertLogger logger;
	eventManager.subscribe(&logger);

	Process processor(eventManager);

	std::thread processorThread(&Process::printAlert, &processor, std::ref(queue));

	std::vector<std::thread> devices;
	for (int i = 1; i <= 3; i++) {
		devices.emplace_back(runDevice, i, std::ref(queue));
	}

	while (running) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	queue.shutdown();

	for (auto& t : devices) {
		if (t.joinable()) {
			t.join();
		}
	}
	if (processorThread.joinable()) {
		processorThread.join();
	}
	
	return 0;
}
// valgrind --tool=helgrind --log-file=report.log --history-level=none --fair-sched=yes --suppressions=helgrind.supp ./build/core
