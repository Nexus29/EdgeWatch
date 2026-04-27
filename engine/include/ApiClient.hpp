#pragma once
#include "Data.hpp"
#include "Alert.hpp"

class ApiClient {
	public:
		void sendMetrics(const Data& data);
		void sendAlert(const Alert& alert);
};