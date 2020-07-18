#pragma once
#include <string>
using namespace std;
namespace ecdh {
	bool GetShareKey(std::string* pubkey_gen, std::string* prikey_gen, std::string* sharekey_gen);
	bool GetShareKey2020(std::string* pubkey_gen, std::string* prikey_gen, std::string* sharekey_gen);
}
