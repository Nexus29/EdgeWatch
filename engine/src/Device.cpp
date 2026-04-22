#include "Device.hpp"
#include <random>

Device::Device(int id) : deviceId(id) {}

Data Device::DeviceData() {
	static std::random_device rd;
	static std::mt19937 gen(rd());

	static std::uniform_real_distribution<float> usage(0, 100);
	static std::uniform_real_distribution<float> temperature(20, 100);

	return Data{
		deviceId,
		usage(gen),
		temperature(gen)
	};
}
