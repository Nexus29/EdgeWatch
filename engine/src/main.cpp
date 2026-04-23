#include "Device.hpp"
#include "Process.hpp"
#include "Queue.hpp"

#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <atomic>
#include <csignal>
#include <condition_variable>

// Global variables for signal handling
std::atomic<bool> keepRunning{true};
std::mutex shutdownMutex;
std::condition_variable shutdownCV;

void signalHandler(int signal) {
	if (signal == SIGINT || signal == SIGTERM) {
		std::cout << "\n[MAIN] Shutdown signal received. Cleaning up...\n";
		keepRunning = false;
		shutdownCV.notify_one();
	}
}

// Device worker
void runMultiDevice(int id, Queue& queue) {
	Device device(id);
	
	std::cout << "[DEVICE " << id << "] Started\n";
	
	while (keepRunning) {
		Data data = device.deviceData();
		queue.push(data);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
	std::cout << "[DEVICE " << id << "] Stopped\n";
}

int main() {
	// Set up signal handlers for graceful shutdown
	std::signal(SIGINT, signalHandler);
	std::signal(SIGTERM, signalHandler);
	
	Queue queue;
	Process processor;

	std::cout << "[MAIN] Starting system...\n";
	std::cout << "[MAIN] Press Ctrl+C to stop\n\n";

	// Start processor thread
	std::thread processorThread(&Process::multiProcess, &processor, std::ref(queue));

	// Start multiple devices (you can increase this number)
	std::vector<std::thread> deviceThreads;
	int numDevices = 1;  // Change to desired number of devices
	
	for (int i = 1; i <= numDevices; i++) {
		deviceThreads.emplace_back(runMultiDevice, i, std::ref(queue));
	}

	// Wait for shutdown signal
	{
		std::unique_lock<std::mutex> lock(shutdownMutex);
		shutdownCV.wait(lock, [] { return !keepRunning; });
	}
	
	std::cout << "\n[MAIN] Initiating graceful shutdown...\n";
	
	// Stop device threads
	keepRunning = false;
	
	// Wait for device threads to finish
	for (auto& t : deviceThreads) {
		if (t.joinable()) {
			t.join();
		}
	}
	std::cout << "[MAIN] All devices stopped\n";
	
	// Shutdown queue to wake up processor thread
	queue.shutdown();
	
	// Wait for processor thread to finish
	if (processorThread.joinable()) {
		processorThread.join();
	}
	std::cout << "[MAIN] Processor stopped\n";
	
	std::cout << "[MAIN] Shutdown complete\n";
	return 0;
}
// valgrind --tool=helgrind --log-file=report.log --suppressions=helgrind.supp ./build/core
