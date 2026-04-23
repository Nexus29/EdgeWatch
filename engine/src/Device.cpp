#include "Device.hpp"
#include <random>

Device::Device(int id) : deviceId(id) {}

Data Device::deviceData() {
	static thread_local std::random_device rd;
	static thread_local std::mt19937 gen(rd());

	static thread_local std::uniform_real_distribution<float> usage(0, 100);
	static thread_local std::uniform_real_distribution<float> temperature(20, 100);

	return Data{
		deviceId,
		usage(gen),
		temperature(gen)
	};
}
