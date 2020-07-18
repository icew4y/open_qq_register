#ifndef _WEB_ECDH_
#define _WEB_ECDH_


#pragma once
#include <iostream>
#include <string>
#include <json/json.h>
#include "../net/net.h"

namespace webecdh {
	std::string get_sharedkey_fromweb();

	std::string calShareKeyMd5ByPeerPublicKey(std::string publickey, std::string private_key);

}

#endif