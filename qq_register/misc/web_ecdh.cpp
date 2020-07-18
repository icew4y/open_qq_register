#include "web_ecdh.h"

std::string webecdh::get_sharedkey_fromweb() {
	std::string result;
	result = net::http_post("http://localhost:9999/api/qqecdh", "accept: */*", "nothing", NULL, "");
	return result;
}

std::string webecdh::calShareKeyMd5ByPeerPublicKey(std::string publickey, std::string private_key) {
	std::string result;
	result = net::http_post("http://localhost:9999/api/calShareKey", "accept: */*", publickey + "|" + private_key, NULL, "");
	return result;
}