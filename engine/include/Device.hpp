#pragma once
#include "Data.hpp"

struct Device
{
	private:
		int deviceId;

	public:
		Device(int id);
		Data DeviceData();
};

