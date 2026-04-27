#include "ApiClient.hpp"
#include "HttpClient.hpp"
#include <sstream>

static const std::string BASE_URL = "http://localhost:5038";

void ApiClient::sendMetrics(const Data& data) {
	std::stringstream ss;

	ss << "{"
	   << "\"deviceId\":" << data.id << ","
	   << "\"cpu\":" << data.usage << ","
	   << "\"temperature\":" << data.temperature
	   << "}";

	HttpClient::post(BASE_URL + "/metrics", ss.str());
}

void ApiClient::sendAlert(const Alert& alert) {
	std::stringstream ss;

	ss << "{"
	   << "\"deviceId\":" << alert.deviceId << ","
	   << "\"message\":\"" << alert.message << "\""
	   << "}";

	HttpClient::post(BASE_URL + "/alerts", ss.str());
}
