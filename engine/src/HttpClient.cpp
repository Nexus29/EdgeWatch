#include "HttpClient.hpp"
#include <curl/curl.h>
#include <iostream>

void HttpClient::post(const std::string& url, const std::string& json) {
	CURL* curl = curl_easy_init();

	if (!curl) {
		std::cerr << "Failed to init CURL\n";
		return;
	}

	struct curl_slist* headers = nullptr;
	headers = curl_slist_append(headers, "Content-Type: application/json");

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2L);

	CURLcode res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		std::cerr << "[HTTP ERROR] " << curl_easy_strerror(res) << "\n";
	}

	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);
}
