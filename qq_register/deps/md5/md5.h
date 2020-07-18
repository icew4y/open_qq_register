#pragma once
#include <openssl/md5.h>
#include <string>

using namespace std;


typedef struct
{
    MD5_CTX ctx;
    unsigned char digest[16]; /* actual digest after MD5Final call */
} MY_MD5_CTX;

void MD5Init(MY_MD5_CTX* mdContext);
void MD5Update(MY_MD5_CTX* mdContext, char* inBuf, unsigned int inLen);
void MD5Final(MY_MD5_CTX *c);


std::string getmd5bytes(std::string& str);
std::string getmd5(std::string& str);

