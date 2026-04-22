#include "Device.hpp"
#include "Process.hpp"
#include <thread>
#include <chrono>

int main() {
	Device device1(1);
	Process process;

	while (true) {
		Data sensorData = device1.DeviceData();

		process.process(sensorData);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}

/* cmake -B build -G Ninja
cmake --build build
./build/core */
