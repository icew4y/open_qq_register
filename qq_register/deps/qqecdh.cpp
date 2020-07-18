
#include "qqecdh.h"
#include "md5/md5.h"
#include <iostream>   
#include <openssl/md5.h>  
#include <openssl/ssl.h>  
#include <openssl/bn.h>



#define ECDH_SIZE 67  
#define MALLOC_SIZE 0x400u

#pragma warning(disable:4996)

static int hex_value(char hex_digit)
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

static std::string hex_to_string(const std::string& input)
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

/*hex转bin*/
int String2Buffer(unsigned char* src, int srclen, unsigned char* dest) {
	int i = 0;
	if (srclen % 2 != 0) return 0;
	for (i = 0; i < srclen / 2; i++)
	{
		char tmp[3];
		tmp[0] = *(src + 2 * i);
		tmp[1] = *(src + 2 * i + 1);
		tmp[2] = 0;
		int out = 0;
		sscanf(tmp, "%x", &out);
		unsigned char ch = (unsigned char)out;
		*(dest + i) = ch;
	}
	return i;
}
/*bin转hex*/
int Buffer2String(unsigned char* src, int srclen, unsigned char* dest) {
	int i;
	for (i = 0; i < srclen; i++)
	{
		char tmp[3] = { 0 };
		sprintf(tmp, "%x", *(src + i));
		if (strlen(tmp) == 1) {
			strcat((char*)dest, "0");
			strncat((char*)dest, tmp, 1);
		}
		else if (strlen(tmp) == 2) {
			strncat((char*)dest, tmp, 2);
		}
		else {
			strcat((char*)dest, "00");
		}
	}
	return i * 2;
}
/*16进制展示数据*/
static void display(const char *tripstr, const char *src, const int src_size)
{
	int i = 0;
	if (tripstr != NULL) {
		printf("%s", tripstr);
	}
	unsigned char*tmp = (unsigned char*)malloc(MALLOC_SIZE);
	memset(tmp, 0, MALLOC_SIZE);
	Buffer2String((unsigned char*)src, src_size, tmp);
	//cout << tmp << endl;
	free(tmp);
}

static int Gen_ECDH_Key(string *s1, string *publickey, string *privatekey, string *sharedkey) {
	string str1 = *s1;
	string str2 = *publickey;
	string str3 = *privatekey;

	bool isNeed23 = false;//是否需要第2 3个参数

	if (str1.length() == 0) {
		//第一个参数不能空
		printf("第一个参数不能空\n");
		return -0x10;
	}
	if (isNeed23) {
		//检测第23个参数
		if (str2.length() == 0) {
			printf("str2 null\n");
			return -0x12;
		}
		if (str3.length() == 0) {
			printf("str3 null\n");
			return -0x13;
		}
	}
	EC_KEY *eckey = EC_KEY_new();
	eckey = EC_KEY_new_by_curve_name(NID_secp192k1);//711
	if (!eckey) {
		printf("eckey null\n");
		return -0x7;
	}
	if (str3.length() > 0) {
		//str3不为空
		printf("private key!=null gen sharekey\n");
		BIGNUM *big = BN_new();
		unsigned char *sout3 = (unsigned char*)malloc(MALLOC_SIZE);
		memset(sout3, 0, MALLOC_SIZE);
		int len3 = String2Buffer((unsigned char*)str3.c_str(), str3.length(), sout3);
		BN_mpi2bn(sout3, len3, big);
		if (!big) {
			printf("big null");
			return -0x5;
		}
		char *p = BN_bn2hex(big);
		if (p)
		{
			printf("set prikey is 0x%s\n", p);
			OPENSSL_free(p);//释放p
			free(sout3);//释放 sout3
		}
		int r = EC_KEY_set_private_key(eckey, big);
		printf("r=%d\n", r);
		BN_free(big);//释放
		if (r != 1) {
			printf("EC_KEY_set_private_key Failed~\n");
			return -0x1;
		}
		const EC_GROUP *group = EC_KEY_get0_group(eckey);
		EC_POINT *point = EC_POINT_new(group);
		if (str2.length() > 0) {
			unsigned char *str2bin = (unsigned char*)malloc(MALLOC_SIZE);
			memset(str2bin, 0, MALLOC_SIZE);
			int len22 = String2Buffer((unsigned char*)str2.c_str(), str2.length(), str2bin);
			int r1 = EC_POINT_oct2point(group, point, str2bin, len22, NULL);
			free(str2bin);
			if (r1 != 1) {
				printf("set pubkey EC_POINT_oct2point Failed~");
				return -0x11;
			}
		}
		else
		{
			int r2 = EC_POINT_mul(group, point, NULL, NULL, NULL, NULL);
			if (r2 != 1) {
				printf("r2 failed=%d\n", r2);
				return -0x2;
			}
		}

		int r3 = EC_KEY_set_public_key(eckey, point);
		if (r3 != 1) {
			printf("set pubkeyfailed ret=%d\n", r3);
			return -0x3;
		}
	}
	else
	{
		printf("private key==null gen all key\n");
		int r5 = EC_KEY_generate_key(eckey);
		if (r5 != 1) {
			printf("genkey failed%d\n", r5);
			return -0x55;
		}
	}
	const EC_GROUP *group1 = EC_KEY_get0_group(eckey);
	const EC_POINT *point1 = EC_KEY_get0_public_key(eckey);
	//get pubkey
	unsigned char *pubkey = (unsigned char*)malloc(MALLOC_SIZE);
	memset(pubkey, 0, MALLOC_SIZE);
	int publen = EC_POINT_point2oct(group1, point1, POINT_CONVERSION_COMPRESSED, pubkey, ECDH_SIZE, NULL);
	printf("pubkey len=%d\n", publen);
	display("pubkey:", (char*)pubkey, publen);

	unsigned char*pubhex = (unsigned char*)malloc(MALLOC_SIZE);
	memset(pubhex, 0, MALLOC_SIZE);
	Buffer2String(pubkey, publen, pubhex);

	*publickey = (char*)pubhex;//返回pubk
	free(pubkey);//释放pubkey
	free(pubhex);

	//get privatekey
	const BIGNUM *pribig = EC_KEY_get0_private_key(eckey);
	unsigned char *pout = (unsigned char*)malloc(MALLOC_SIZE);
	memset(pout, 0, MALLOC_SIZE);
	int lenpri = BN_bn2mpi(pribig, pout);
	display("prik:", (char*)pout, lenpri);
	unsigned char*ppout = (unsigned char*)malloc(MALLOC_SIZE);
	memset(ppout, 0, MALLOC_SIZE);
	Buffer2String(pout, lenpri, ppout);
	*privatekey = (char*)ppout;//返回prik
	free(pout);
	free(ppout);


	//set str1
	unsigned char *str1bin = (unsigned char*)malloc(MALLOC_SIZE);
	memset(str1bin, 0, MALLOC_SIZE);
	int len11 = String2Buffer((unsigned char*)str1.c_str(), str1.length(), str1bin);
	EC_POINT *point2 = EC_POINT_new(group1);
	int r4 = EC_POINT_oct2point(group1, point2, str1bin, len11, NULL);
	free(str1bin);//释放str1bin
	if (r4 != 1) {
		printf("r4 failed=%d\n", r4);
		return -0x4;
	}
	//get sharedkey
	unsigned char *shared = (unsigned char *)malloc(MALLOC_SIZE);
	memset(shared, 0, MALLOC_SIZE);
	int len = ECDH_compute_key(shared, 512, point2, eckey, NULL);
	printf("share len:%d\n", len);
	if (len <= 0) {
		printf("gen sharedk failed");
		return -0x9;
	}
	unsigned char md5share[MD5_DIGEST_LENGTH];
	MD5(shared, len, md5share);
	display("sharekey:", (char*)md5share, MD5_DIGEST_LENGTH);

	unsigned  char* sharehex = (unsigned char*)malloc(MALLOC_SIZE);
	memset(sharehex, 0, MALLOC_SIZE);
	Buffer2String(md5share, MD5_DIGEST_LENGTH, sharehex);

	*sharedkey = (char*)sharehex;//返回sharekey
	free(shared);//释放shaedkey
	free(sharehex);
	EC_KEY_free(eckey);//释放eckey
	return 1;
}



/* Hook 数据
I/qqhook  (11871): GenECDHKeyEx参数1 len=50:020e14a939661cadbdaa0b177b6e8d2b067c310bdeadc09804
I/qqhook  (11871): GenECDHKeyEx参数2 len=50:021348bccdb2621c2a302bf4d6bbb349c907509b8fd527bd75
I/qqhook  (11871): GenECDHKeyEx参数3 len=56:000000187eaed20dd5d153ed2b0e93bf695f5c6700fd87cbd150a85f
I/qqhook  (11871): set_c_pub_key param len=25:021348BCCDB2621C2A302BF4D6BBB349C907509B8FD527BD75
I/qqhook  (11871): set_c_pri_key param len=28:000000187EAED20DD5D153ED2B0E93BF695F5C6700FD87CBD150A85F
I/qqhook  (11871): set_g_share_key param len=16:2FF60FFDD54A4DEAB26D0A85E8B9573D
*/
int main111()
{
	string s1 = "020e14a939661cadbdaa0b177b6e8d2b067c310bdeadc09804";
	string pubkey = "021348bccdb2621c2a302bf4d6bbb349c907509b8fd527bd75";
	string prikey = "000000187eaed20dd5d153ed2b0e93bf695f5c6700fd87cbd150a85f";
	string sharekey = "";

	if (Gen_ECDH_Key(&s1, &pubkey, &prikey, &sharekey) != 1) {
		//cout << "get shared key failed" << endl;
		return 0;
	}
	/*
	通过hook数据 以上几个参数最后计算的sharekey为:2FF60FFDD54A4DEAB26D0A85E8B9573D
	验证通过算法ok
	*/
	//cout << endl << "根据 pubkey prik计算sharek" << endl;
	//cout << "pubkey len=" << pubkey.length() / 2 << ":" << pubkey << endl;
	//cout << "prikey len=" << prikey.length() / 2 << ":" << prikey << endl;
	//cout << "sharekey len=" << sharekey.length() / 2 << ":" << sharekey << endl << endl;


	string s1_gen = "04928D8850673088B343264E0C6BACB8496D697799F37211DEB25BB73906CB089FEA9639B4E0260498B51A992D50813DA8";
	string pubkey_gen = "";
	string prikey_gen = "";
	string sharekey_gen = "";

	if (Gen_ECDH_Key(&s1_gen, &pubkey_gen, &prikey_gen, &sharekey_gen) != 1) {
		//cout << "gen all key failed" << endl;
		return 0;
	}

    
	//cout << endl << "生成 pubk prik sharek" << endl;
	//cout << "pubkey len=" << pubkey_gen.length() / 2 << ":" << pubkey_gen << endl;
	//cout << "prikey len=" << prikey_gen.length() / 2 << ":" << prikey_gen << endl;
	//cout << "sharekey len=" << sharekey_gen.length() / 2 << ":" << sharekey_gen << endl << endl;

	//cin.get();6
	return 0;
}



int GetShareKey_(std::string* pubkey_gen, std::string* prikey_gen, std::string* sharekey_gen) {

	char  tk[] = { 0x04, 0x92, 0x8D, 0x88, 0x50, 0x67, 0x30, 0x88, 0xB3, 0x43, 0x26, 0x4E, 0x0C, 0x6B, 0xAC, 0xB8, 0x49, 0x6D, 0x69, 0x77, 0x99, 0xF3, 0x72, 0x11, 0xDE, 0xB2, 0x5B, 0xB7, 0x39, 0x06, 0xCB, 0x08, 0x9F, 0xEA, 0x96, 0x39, 0xB4, 0xE0, 0x26, 0x04, 0x98, 0xB5, 0x1A, 0x99, 0x2D, 0x50, 0x81, 0x3D, 0xA8 };

	char pubkey[67] = { 0 };
	char sharekey[512] = { 0 };




	EC_KEY* key = NULL;
	const EC_POINT* ec_point = NULL;
	const EC_GROUP* ec_group = NULL;
	key = EC_KEY_new();
	if (key == NULL) {
		printf("EC_KEY_new 失败\n");
		return -1;
	}


	key = EC_KEY_new_by_curve_name(NID_secp192k1);
	if (key == NULL) {
		printf("EC_KEY_new_by_curve_name 失败\n");
		return -1;
	}

	int ret = -1;
	ret = EC_KEY_generate_key(key);
	if (ret == 0) {
		printf("EC_KEY_generate_key 失败\n");
		return -1;
	}

	ec_point = EC_KEY_get0_public_key(key);
	if (ec_point == NULL) {
		printf("EC_KEY_get0_public_key 失败\n");
		return -1;
	}
	ec_group = EC_KEY_get0_group(key);
	if (ec_group == NULL) {
		printf("EC_KEY_get0_group 失败\n");
		return -1;
	}

	size_t point2OctLen = EC_POINT_point2oct(ec_group, ec_point, POINT_CONVERSION_COMPRESSED, (unsigned char*)&pubkey, 67, NULL);
	if (point2OctLen <= 0) {
		printf("EC_POINT_point2oct 失败\n");
		return -1;
	}

	const EC_GROUP* ec_group1 = EC_KEY_get0_group(key);
	if (ec_group1 == NULL) {
		printf("EC_KEY_get0_group 失败\n");
		return -1;
	}


	EC_POINT* new_point = EC_POINT_new(ec_group1);
	if (new_point == NULL) {
		printf("EC_POINT_new 失败\n");
		return -1;
	}

	ret = EC_POINT_oct2point(ec_group1, new_point, (const unsigned char*)tk, sizeof(tk), NULL);
	if (ret <= 0) {
		printf("EC_POINT_oct2point 失败\n");
		return -1;
	}

	ret = ECDH_compute_key(&sharekey, 512, new_point, key, NULL);
	if (ret <= 0) {
		printf("ECDH_compute_key 失败\n");
		return -1;
	}


	char _public_key[25] = { 0 };
	char _share_key[24] = { 0 };

	memcpy(_public_key, pubkey, 25);
	memcpy(_share_key, sharekey, 24);

	std::string strshared = std::string((const char*)_share_key, 24);
	*sharekey_gen = getmd5bytes(strshared);
	*pubkey_gen = std::string((char*)_public_key, 25);
	EC_KEY_free(key);

	return 1;
}

int GetShareKey_2020(std::string* pubkey_gen, std::string* prikey_gen, std::string* sharekey_gen) {

	//char  tk[] = { 0x04, 0x92, 0x8D, 0x88, 0x50, 0x67, 0x30, 0x88, 0xB3, 0x43, 0x26, 0x4E, 0x0C, 0x6B, 0xAC, 0xB8, 0x49, 0x6D, 0x69, 0x77, 0x99, 0xF3, 0x72, 0x11, 0xDE, 0xB2, 0x5B, 0xB7, 0x39, 0x06, 0xCB, 0x08, 0x9F, 0xEA, 0x96, 0x39, 0xB4, 0xE0, 0x26, 0x04, 0x98, 0xB5, 0x1A, 0x99, 0x2D, 0x50, 0x81, 0x3D, 0xA8 };

	std::string pbkey = hex_to_string("04928D8850673088B343264E0C6BACB8496D697799F37211DEB25BB73906CB089FEA9639B4E0260498B51A992D50813DA8");

	char pubkey[67] = { 0 };
	char sharekey[512] = { 0 };




	EC_KEY* key = NULL;
	const EC_POINT* ec_point = NULL;
	const EC_GROUP* ec_group = NULL;
	key = EC_KEY_new();
	if (key == NULL) {
		printf("EC_KEY_new 失败\n");
		return -1;
	}


	key = EC_KEY_new_by_curve_name(NID_secp192k1);
	if (key == NULL) {
		printf("EC_KEY_new_by_curve_name 失败\n");
		return -1;
	}

	int ret = -1;
	ret = EC_KEY_generate_key(key);
	if (ret == 0) {
		printf("EC_KEY_generate_key 失败\n");
		return -1;
	}

	ec_group = EC_KEY_get0_group(key);
	if (ec_group == NULL) {
		printf("EC_KEY_get0_group 失败\n");
		return -1;
	}

	ec_point = EC_KEY_get0_public_key(key);
	if (ec_point == NULL) {
		printf("EC_KEY_get0_public_key 失败\n");
		return -1;
	}


	size_t point2OctLen = EC_POINT_point2oct(ec_group, ec_point, POINT_CONVERSION_COMPRESSED, (unsigned char*)&pubkey, 67, NULL);
	if (point2OctLen <= 0) {
		printf("EC_POINT_point2oct 失败\n");
		return -1;
	}

	const BIGNUM* private_key = EC_KEY_get0_private_key(key);
	int private_len = BN_bn2mpi(private_key, NULL);
	unsigned char privatekey[555] = { 0 };
	private_len = BN_bn2mpi(private_key, privatekey);

// 	const EC_GROUP* ec_group1 = EC_KEY_get0_group(key);
// 	if (ec_group1 == NULL) {
// 		printf("EC_KEY_get0_group 失败\n");
// 		return -1;
// 	}


	EC_POINT* new_point = EC_POINT_new(ec_group);
	if (new_point == NULL) {
		printf("EC_POINT_new 失败\n");
		return -1;
	}

	ret = EC_POINT_oct2point(ec_group, new_point, (const unsigned char*)pbkey.data(), pbkey.length(), NULL);
	if (ret <= 0) {
		printf("EC_POINT_oct2point 失败\n");
		return -1;
	}


	ret = ECDH_compute_key(&sharekey, 512, new_point, key, NULL);
	if (ret <= 0) {
		printf("ECDH_compute_key 失败\n");
		return -1;
	}


	char _public_key[49] = { 0 };
	char _share_key[24] = { 0 };

	memcpy(_public_key, pubkey, 49);
	memcpy(_share_key, sharekey, 24);

	std::string strshared = std::string((const char*)_share_key, 24);
	*sharekey_gen = getmd5bytes(strshared);
	*pubkey_gen = std::string((char*)_public_key, 49);
	EC_KEY_free(key);

	return 1;
}


bool ecdh::GetShareKey(std::string *pubkey_gen, std::string *prikey_gen, std::string *sharekey_gen) {
	bool result = false;
	//生成pubkey 和 sharekey
	int cnt = 100;
	do
	{
		if (-1 == GetShareKey_(pubkey_gen, prikey_gen, sharekey_gen)) {
			cnt--;
			continue;
		}
		result = true;
		break;
	} while (cnt > 0);
	return result;
}

bool ecdh::GetShareKey2020(std::string* pubkey_gen, std::string* prikey_gen, std::string* sharekey_gen) {
	bool result = false;
	//生成pubkey 和 sharekey
	int cnt = 100;
	do
	{
		if (-1 == GetShareKey_2020(pubkey_gen, prikey_gen, sharekey_gen)) {
			cnt--;
			continue;
		}
		result = true;
		break;
	} while (cnt > 0);
	return result;
}