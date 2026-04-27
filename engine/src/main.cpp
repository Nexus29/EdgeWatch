#include "Device.hpp"
#include "Process.hpp"
#include "Queue.hpp"
#include "EventManager.hpp"
#include "AlertLogger.hpp"
#include "ApiClient.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <csignal>
#include <atomic>
#include <curl/curl.h>

std::atomic<bool> running{true};

void signalHandler(int) {
	running = false;
}

// Device worker thread
void runDevice(int id, Queue& queue) {
	Device device(id);

	while (running) {
		Data data = device.deviceData();
		queue.push(data);

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

int main() {
	curl_global_init(CURL_GLOBAL_DEFAULT);

	// Handle CTRL+C
	struct sigaction sa;
	sa.sa_handler = signalHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, nullptr);
	sigaction(SIGTERM, &sa, nullptr);

	Queue queue;
	EventManager eventManager;
	ApiClient apiClient;

	// Observer
	AlertLogger logger;
	eventManager.subscribe(&logger);

	// Processor
	Process process(eventManager, apiClient);

	std::thread processorThread(&Process::printSend, &process, std::ref(queue));

	// Devices
	std::vector<std::thread> devices;
	for (int i = 1; i <= 3; i++) {
		devices.emplace_back(runDevice, i, std::ref(queue));
	}

	// Keep alive until CTRL+C
	while (running) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << "\nShutting down...\n";

	// Clean shutdown
	queue.shutdown();

	for (auto& t : devices) {
		if (t.joinable()) t.join();
	}

	if (processorThread.joinable()) {
		processorThread.join();
	}

	curl_global_cleanup();

	return 0;
}
// valgrind --tool=helgrind --log-file=report.log --history-level=none --fair-sched=yes --suppressions=helgrind.supp ./build/core
