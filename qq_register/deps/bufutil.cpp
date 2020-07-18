#include "bufutil.h"
#include "md5/md5.h"
#include "../misc/EdUrlParser.h"


int hex_value(char hex_digit)
{
	switch (hex_digit) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return hex_digit - '0';

	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
		return hex_digit - 'A' + 10;

	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		return hex_digit - 'a' + 10;
	}
	throw std::invalid_argument("invalid hex digit");
}

std::string bufutil::hex_to_string(const std::string& input)
{
	const auto len = input.length();
	if (len & 1) throw std::invalid_argument("odd length");

	std::string output;
	output.reserve(len / 2);
	for (auto it = input.begin(); it != input.end(); )
	{
		int hi = hex_value(*it++);
		int lo = hex_value(*it++);
		output.push_back(hi << 4 | lo);
	}
	return output;
}

std::string bufutil::string_to_hex(const std::string& input)
{
	static const char hex_digits[] = "0123456789ABCDEF";

	std::string output;
	output.reserve(input.length() * 2);
	for (unsigned char c : input)
	{
		output.push_back(hex_digits[c >> 4]);
		output.push_back(hex_digits[c & 15]);
	}
	return output;
}
int8_t bufutil::buf_to_int8(const char* buf) {
	int8_t t = *(int8_t*)buf;
	return t;
}

int16_t bufutil::buf_to_int16(const char* buf) {
	int16_t t = *(int16_t*)buf;
	return ntohs(t);
}


int32_t bufutil::buf_to_int32(const char* buf) {
	int32_t t = *(int32_t*)buf;
	return ntohl(t);
}


int64_t bufutil::buf_to_int64(const char* buf) {
	int64_t t = *(int64_t*)buf;
	return ntohll(t);
}

int bufutil::int8_to_buf(int8_t v, string& buf)
{
	int pos = buf.length();
	buf.append((const char *)&v, sizeof(int8_t));
	return pos;
}

int bufutil::int16_to_buf(int16_t v, string& buf)
{
	int pos = buf.length();
	int16_t t = htons(v);
	buf.append((const char*)&t, sizeof(int16_t));
	return pos;
}

int bufutil::int32_to_buf(int32_t v, string& buf)
{
	int pos = buf.length();
	int32_t t = htonl(v);
	buf.append((const char*)&t, sizeof(int32_t));
	return pos;
}

int bufutil::int64_to_buf(int64_t v, string& buf)
{
	int pos = buf.length();
	int64_t t = htonll(v);
	buf.append((const char*)&t, sizeof(int64_t));
	return pos;
}

void bufutil::fix_buf_data(int pos, const char* data, int len, string& buf)
{
	for (int Index = 0; Index < len ; Index++)
	{
		buf[pos + Index] = data[Index];
	}
}

std::string bufutil::buf_to_string(const char* buf, int len) {
	return std::string(buf, len);
}

void bufutil::string_to_buf(string& data, string& buf) {
	buf.append(data);
}



int bufutil::buf_to_8struct(const char* buf, int8_struct** st, bool include_len) {
	int result = 0;
	int8_t len = buf_to_int8(buf);
	int data_len = 0;
	if (include_len) {
		*st = (int8_struct*)new char[len];
		data_len = len - sizeof(int8_t);
		result = len;
	}
	else {
		*st = (int8_struct*)new char[len + sizeof(int8_t)];
		data_len = len;
		result = len + 1;
	}
	std::string st_data = buf_to_string(buf + sizeof(int8_t), data_len);
	(*st)->len = data_len;
	memcpy((*st)->data, st_data.data(), st_data.length());
	return result;
}


int bufutil::buf_to_16struct(const char* buf, int16_struct** st, bool include_len) {
	int result = 0;
	int16_t len = buf_to_int16(buf);
	int data_len = 0;
	if (include_len) {
		*st = (int16_struct*)new char[len];
		data_len = len - sizeof(int16_t);
		result = len;
	}
	else {
		*st = (int16_struct*)new char[len + sizeof(int16_t)];
		data_len = len;
		result = len + sizeof(int16_t);
	}
	std::string st_data = buf_to_string(buf + sizeof(int16_t), data_len);
	(*st)->len = data_len;
	memcpy((*st)->data, st_data.data(), st_data.length());
	return result;
}


int bufutil::buf_to_32struct(const char* buf, int32_struct** st, bool include_len) {
	int result = 0;
	int32_t len = buf_to_int32(buf);
	int data_len = 0;
	if (include_len) {
		*st = (int32_struct*)new char[len];
		data_len = len - sizeof(int32_t);
		result = len;
	}
	else {
		*st = (int32_struct*)new char[len + sizeof(int32_t)];
		data_len = len;
		result = len + sizeof(int32_t);
	}
	std::string st_data = buf_to_string(buf + sizeof(int32_t), data_len);
	(*st)->len = data_len;
	memcpy((*st)->data, st_data.data(), st_data.length());
	return result;
}


int bufutil::int8data_to_buf(string& int8data,  string& buf, bool include_len /*= false*/)
{
	int result = 0;
	int8_t len = 0;
	if (include_len)
		len = int8data.length() + sizeof(int8_t);
	else
		len = int8data.length();
	int8_to_buf(len, buf);
	buf.append(int8data);
	return result = len + int8data.length();
}

int bufutil::int16data_to_buf(string& int16data, string& buf, bool include_len /*= false*/)
{
	int result = 0;
	int16_t len = 0;
	if (include_len)
		len = int16data.length() + sizeof(int16_t);
	else
		len = int16data.length();
	int16_to_buf(len, buf);
	buf.append(int16data);
	return result = len + int16data.length();
}

int bufutil::int32data_to_buf(string& int32data, string& buf, bool include_len /*= false*/)
{
	int result = 0;
	int32_t len = 0;
	if (include_len)
		len = int32data.length() + sizeof(int32_t);
	else
		len = int32data.length();
	int32_to_buf(len, buf);
	buf.append(int32data);
	return result = len + int32data.length();
}

std::string bufutil::tea_decrypt(const char* buf, int len, const char* key) {
	std::string result;
	TEACTX tea_ctx;
	size_t decLen = 0;
	decLen = 10000;
	unsigned char* decBuf = (unsigned char*)malloc(decLen);
	if (!decBuf)
		return "";

	memset(decBuf, 0, 10000);
	int ret = 0;
	ret = Decrypt(&tea_ctx, (uint8_t*)buf, len, (const uint8*)key, (uint8*)decBuf, (uint32*)&decLen);
	if (ret == 1) {
		result = std::string((const char*)decBuf, decLen);
	}
	free(decBuf);
	return result;
}

std::string bufutil::tea_encrypt(const char* buf, int len, const char* key)
{
	std::string result;
	TEACTX tea_ctx;
	size_t encodeLen = 0;
	encodeLen = 10000;
	unsigned char* encodeBuf = (unsigned char*)malloc(encodeLen);
	if (!encodeBuf)
		return "";

	memset(encodeBuf, 0, 10000);
	int ret = 0;
	ret = Encrypt(&tea_ctx, (uint8_t*)buf, len, (const uint8*)key, (uint8*)encodeBuf, (uint32*)&encodeLen);
	if (ret > 0) {
		result = std::string((const char*)encodeBuf, encodeLen);
	}
	free(encodeBuf);
	return result;
}

string bufutil::zlib_uncompress(string& data) {
	string result;
	int len = data.length();
	int source_len = data.length();
	int ret = Z_OK;
	char* uncompress_data = NULL;
	int retrycnt = 10;
	do
	{
		if (retrycnt > 10)
			break;
		len *= 2;
		char *new_ptr = (char*)realloc(uncompress_data, len);
		if (new_ptr == NULL)
			break;
		uncompress_data = new_ptr;
		ret = uncompress2((Bytef*)uncompress_data, (uLongf*)&len, (Bytef*)data.data(), (uLongf*)&source_len);
		if (ret == Z_DATA_ERROR || ret == Z_MEM_ERROR)
		{
			break;
		}

		retrycnt++;
	} while (ret == Z_BUF_ERROR);

	result = string((const char*)uncompress_data, len);

	if (uncompress_data) free(uncompress_data);
	return result;
}


std::string bufutil::get_loginkey(uint64_t qq, std::string psw) {
	//MD5(MD5(pass)+00 00 00 00+HEX(QQ))
	std::string pswmd5 = getmd5bytes(psw);
	std::string data;
	data.append(pswmd5);

	//zeroByytes  Ù”⁄∏ﬂŒª
	//const char zeroByytes[4] = { 0 };
	//data.append(std::string(zeroByytes, 4));
	uint64_t qq_ = htonll(qq);
	data.append(std::string((const char*)&qq_, 8));
	return getmd5bytes(data);
}


std::string toupper_str(std::string& s) {
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

std::string bufutil::to_hex_stream(int8_t n) {

	std::stringstream ss;
	ss << std::hex << (int)n;
	std::string result = std::string(ss.str());
	return toupper_str(result);
}


std::string bufutil::to_hex_stream(int16_t n) {

	std::stringstream ss;
	ss << std::hex << n;
	std::string tmp = ss.str();
	std::string result;
	if (tmp.length() < 4) {
		for (int Index = 0; Index < 4 - tmp.length(); Index++)
		{
			result.append("0");
		}
		result.append(tmp);
	}
	else {
		result = tmp;
	}
	return toupper_str(result);
}


std::string bufutil::to_hex_stream(int32_t n) {

	std::stringstream ss;
	ss << std::hex << n;
	std::string tmp = ss.str();
	std::string result;
	if (tmp.length() < 8) {
		for (int Index = 0; Index < 8 - tmp.length(); Index++)
		{
			result.append("0");
		}
		result.append(tmp);
	}
	else {
		result = tmp;
	}
	return toupper_str(result);
}

std::string bufutil::to_hex_stream(int64_t n) {

	std::stringstream ss;
	ss << std::hex << n;
	std::string tmp = ss.str();
	std::string result;
	if (tmp.length() < 16) {
		for (int Index = 0; Index < 16 - tmp.length(); Index++)
		{
			result.append("0");
		}
		result.append(tmp);
	}
	else {
		result = tmp;
	}
	return toupper_str(result);
}


std::string bufutil::spacing_string(std::string value) {
	if (value.length() % 2 != 0)
		return "";
	std::string result;
	for (int i = 0; i < value.length(); i++) {
		if (i % 2 == 0) {
			std::string tmp = value.substr(i, 2);
			result.append(tmp);
			result.append(" ");
		}
	}
	return result;
}

std::unordered_map<string, string> bufutil::crack_captcha_url(string urlstr)
{
	// parse and allocate url object.
	EdUrlParser* url = EdUrlParser::parseUrl(urlstr);
// 	cout << "scheme: " + url->scheme << endl;
// 	cout << "host name: " + url->hostName << endl;
// 	cout << "port: " + url->port << endl;
// 	cout << "path: " + url->path << endl;
// 	cout << "param: " + url->query << endl;
// 	cout << "fragment: " + url->fragment << endl;

	// parse path
	vector<string> paths;
	EdUrlParser::parsePath(&paths, url->path);
// 	for (int i = 0; i < paths.size(); i++) {
// 		cout << "path part: " + paths[i] << endl;
// 	}

	// parse query string as key-value list style
	vector<query_kv_t> kvs;
	int num = EdUrlParser::parseKeyValueList(&kvs, url->query);
// 	for (int i = 0; i < num; i++) {
// 		printf("idx:%d  key: %s, val: %s\n", i, kvs[i].key.c_str(), kvs[i].val.c_str());
// 	}

	// parse query string as key-value hash map
	unordered_map<string, string> map;
	int mapnum = EdUrlParser::parseKeyValueMap(&map, url->query);
	string name;
// 	try {
// 		name = map.at("name");
// 		printf("key name vale '%s'\n", map["name"].c_str());
// 	}
// 	catch (out_of_range err) {
// 		printf("### Error: not found...\n");
// 	};



	if (url != NULL) // ==> make sure to free url object allocated by EdUrlParser
		delete url;

	return map;
}
