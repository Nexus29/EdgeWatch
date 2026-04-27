#pragma once
#include <string>

class HttpClient {
	public:
		static void post(const std::string& url, const std::string& json);
};

