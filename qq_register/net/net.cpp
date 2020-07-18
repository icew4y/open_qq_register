#include "net.h"
#include <WS2tcpip.h>


bool g_init = false;

#define PRE_INIT do {\
	if (!g_init)\
	{\
		WSADATA wsaData;\
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);\
		g_init = true;\
	}\
}while (0);

SOCKET net::_connecet(string ip, uint16_t port)
{
	PRE_INIT;
	SOCKET s;
	sockaddr_in connect_addr;

	s = -1;
	s = socket(AF_INET, SOCK_STREAM, 0);

	memset(&connect_addr, 0, sizeof(connect_addr));
	connect_addr.sin_family = AF_INET;
	connect_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	connect_addr.sin_port = htons(port);

	int ret;
	ret = connect(s, (struct sockaddr*) & connect_addr, sizeof(connect_addr));
	int nNetTimeout = 10000;//1秒，
	
	//设置发送超时
	setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, (char*)&nNetTimeout, sizeof(int));
	//设置接收超时
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&nNetTimeout, sizeof(int));
	return s;
}



int32_t net::_send(SOCKET s, const char* data, int len)
{
	PRE_INIT;
	int ret = send(s, data, len, 0);
	return ret;
}

string net::resolve_host_byname(string name) {
	PRE_INIT;
	string result;
	hostent *host = gethostbyname(name.c_str());
	if (host != NULL) {
		switch (host->h_addrtype)
		{
		case AF_INET:{
			char** pptr = host->h_addr_list;
			char str[INET_ADDRSTRLEN];
			for (; *pptr != NULL; pptr ++)
			{
				result = inet_ntop(host->h_addrtype, host->h_addr, str, sizeof(str));
				break;
			}
			break;
		}
		}
	}
	return result;
}

string net::_receive(SOCKET s)
{
	PRE_INIT;
	string result;
	char* recv_buf = new char[8000];
	memset(recv_buf, 0, sizeof(recv_buf));
	int ret = recv(s, recv_buf, 8000, 0);
	
	if (ret > 0) {
		result = string(recv_buf, ret);
	}
	delete[] recv_buf;
	return result;
}

void net::_close(SOCKET s)
{
	shutdown(s, SD_BOTH);
	closesocket(s);
}


SOCKET net::_connect_with_http_proxy(string ip, int16_t port, string dstip, int16_t dstport)
{

	SOCKET s = _connecet(ip, port);
	if (s != INVALID_SOCKET) {
		char buf[512];
		char recv_buf[512] = { 0 };
		sprintf_s(buf, sizeof(buf), "CONNECT %s:%d HTTP/1.1\r\nUser-Agent: MyApp/0.1\r\n\r\n", dstip.c_str(), dstport);
		int ret = _send(s, (char*)buf, strlen(buf));
		string result = _receive(s);
		if (result.find("HTTP/1.0 200 Connection established") != string::npos ||
			result.find("HTTP/1.1 200") != string::npos) {
			return s;
		}
		else {
			return INVALID_SOCKET;
		}
	}
	return INVALID_SOCKET;
}

static size_t _write_data(void* buffer, size_t size, size_t nmemb, void* stream)
{
	((std::string*)stream)->append((char*)buffer, size * nmemb);
	return size * nmemb;
}

std::string net::curl_escape(string data) {
	CURL* curl = curl_easy_init();
	string encode_data = curl_easy_escape(curl, data.data(), data.length());
	return encode_data;
}

std::string net::http_get(std::string url, std::string header, struct curl_slist** cookies, std::string setcookie, bool ret_header, bool follow_location, bool gzip)
{
	CURL* curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	char tmp[512];
	struct curl_slist* headers = NULL;
	if (header != "") {
		headers = curl_slist_append(headers, header.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	}
	else {
		
	}

	if (ret_header) {
		curl_easy_setopt(curl, CURLOPT_HEADER, true);
	}
	if (follow_location) {
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	}

	std::ostringstream ss;
	ss << std::this_thread::get_id();
	std::string idstr = ss.str();
	idstr += ".txt";

	if (setcookie != "") {
		std::string cookies = "Cookie: ";
		cookies += setcookie;
		headers = curl_slist_append(headers, cookies.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	}
	else {
// 		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, idstr.c_str());
// 		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, idstr.c_str());
	}
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);//设定为不验证证书和HOST 
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
	if (gzip)
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");

	//curl_easy_setopt(curl, CURLOPT_PROXY, "http://127.0.0.1:8888");
	std::string respone;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _write_data); //对返回的数据进行操作的函数地址  
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &respone); //这是write_data的第四个参数值 
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_COOKIELIST, cookies);

	curl_easy_cleanup(curl);
	if (header != "") {
		curl_slist_free_all(headers);
	}

	return respone;
}

std::string net::http_post(std::string url, std::string header, std::string postdata, struct curl_slist** cookies, std::string setcookie /*= ""*/, bool gzip /*= false*/)
{
	CURL* curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	char tmp[512];
	struct curl_slist* headers = NULL;
	if (header != "") {
		headers = curl_slist_append(headers, header.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	}
	std::ostringstream ss;
	ss << std::this_thread::get_id();
	std::string idstr = ss.str();
	idstr += ".txt";



	if (setcookie != "") {
		std::string cookies = "Cookie: ";
		cookies += setcookie;
		headers = curl_slist_append(headers, cookies.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	}
	else {
// 		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, idstr.c_str());
// 		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, idstr.c_str());
	}
	curl_easy_setopt(curl, CURLOPT_COOKIEJAR, idstr.c_str());
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, idstr.c_str());
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);//设定为不验证证书和HOST 
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
	if (gzip)
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
	std::string respone;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _write_data); //对返回的数据进行操作的函数地址  
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &respone); //这是write_data的第四个参数值 

	curl_easy_setopt(curl, CURLOPT_POST, 1);
	
	curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, postdata.c_str());

	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_COOKIELIST, cookies);

	curl_easy_cleanup(curl);
	if (header != "") {
		curl_slist_free_all(headers);
	}

	return respone;
}
