#pragma once
#include "../pch.h"
#include <curl/curl.h>

namespace net {
	SOCKET _connecet(string ip, uint16_t port);
	int32_t _send(SOCKET s, const char* data, int len);
	string resolve_host_byname(string name);
	string _receive(SOCKET s);
	void _close(SOCKET s);


	SOCKET _connect_with_http_proxy(string ip, int16_t port, string dstip, int16_t dstport);
	std::string curl_escape(string data);
	std::string http_get(std::string url, std::string header, struct curl_slist** cookies, std::string setcookie, bool ret_header, bool follow_location, bool gzip);
	std::string http_post(std::string url, std::string header, std::string postdata, struct curl_slist** cookies, std::string setcookie = "", bool gzip = false);
}