
#pragma once
#include "pch.h"
namespace bufutil {
	struct int8_struct
	{
		int8_t len;
		char data[0];
	};

	struct int16_struct
	{
		int16_t len;
		char data[0];
	};


	struct int32_struct
	{
		int32_t len;
		char data[0];
	};


	std::string hex_to_string(const std::string& input);
	std::string string_to_hex(const std::string& input);
	int8_t buf_to_int8(const char* buf);
	int16_t buf_to_int16(const char* buf);
	int32_t buf_to_int32(const char* buf);
	int64_t buf_to_int64(const char* buf);

	int int8_to_buf(int8_t v, string& buf);
	int int16_to_buf(int16_t v, string& buf);
	int int32_to_buf(int32_t v, string& buf);
	int int64_to_buf(int64_t v, string& buf);

	void fix_buf_data(int pos, const char* data, int len, string& buf);


	std::string buf_to_string(const char* buf, int len);
	void string_to_buf(string& data, string& buf);
	int buf_to_8struct(const char* buf, int8_struct** st, bool include_len = false);
	int buf_to_16struct(const char* buf, int16_struct** st, bool include_len = false);
	int buf_to_32struct(const char* buf, int32_struct** st, bool include_len = false);

	int int8data_to_buf(string& int8data, string& buf, bool include_len = false);
	int int16data_to_buf(string& int16data, string& buf, bool include_len = false);
	int int32data_to_buf(string& int32data, string& buf, bool include_len = false);

	std::string tea_decrypt(const char* buf, int len, const char* key);
	std::string tea_encrypt(const char* buf, int len, const char* key);
	string zlib_uncompress(string& data);
	std::string get_loginkey(uint64_t qq, std::string psw);
	std::string to_hex_stream(int8_t n);
	std::string to_hex_stream(int16_t n);
	std::string to_hex_stream(int32_t n);
	std::string to_hex_stream(int64_t n);
	std::string spacing_string(std::string value);
	unordered_map<string, string> crack_captcha_url(string url);
}
