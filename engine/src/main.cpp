#include "Device.hpp"
#include "Process.hpp"
#include "Queue.hpp"

#include <thread>
#include <vector>
#include <chrono>

// Device worker
void runMultiDevice(int id, Queue& queue) {
    Device device(id);

    while (true) {
        Data data = device.deviceData();

        queue.push(data);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    Queue queue;
    Process processor;

    // Start processor thread
    std::thread processorThread(&Process::multiProcess, &processor, std::ref(queue));

    // Start multiple devices
    std::vector<std::thread> deviceThreads;

    for (int i = 1; i <= 1; i++) {
        deviceThreads.emplace_back(runMultiDevice, i, std::ref(queue));
    }

    // Join threads (never ends)
    for (auto& t : deviceThreads) {
        t.join();
    }

    processorThread.join();

    return 0;
}

/* cmake -B build -G Ninja
cmake --build build
./build/core */
