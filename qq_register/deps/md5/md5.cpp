#include "md5.h"

void MD5Init(MY_MD5_CTX* mdContext)
{
    MD5_Init(&mdContext->ctx);
}

void MD5Update(MY_MD5_CTX* mdContext, char* inBuf, unsigned int inLen)
{
    MD5_Update(&mdContext->ctx, inBuf, inLen);
}

void MD5Final(MY_MD5_CTX *c)
{
    MD5_Final((unsigned char *)&c->digest, &c->ctx);
}



void _HexToStr(unsigned char *pbDest, unsigned char *pbSrc, int nLen)
{
	char    ddl, ddh;
	int i;

	for (i = 0; i < nLen; i++)
	{
		ddh = 48 + pbSrc[i] / 16;
		ddl = 48 + pbSrc[i] % 16;
		if (ddh > 57) ddh = ddh + 7;
		if (ddl > 57) ddl = ddl + 7;
		pbDest[i * 2] = ddh;
		pbDest[i * 2 + 1] = ddl;
	}

	pbDest[nLen * 2] = '\0';
}

void _StrToHex(char *pbDest, char *pbSrc, int nLen)
{
	char h1, h2;
	char s1, s2;
	int i;

	for (i = 0; i < nLen; i++)
	{
		h1 = pbSrc[2 * i];
		h2 = pbSrc[2 * i + 1];

		s1 = toupper(h1) - 0x30;
		if (s1 > 9)
			s1 -= 7;

		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
			s2 -= 7;

		pbDest[i] = s1 * 16 + s2;
	}
}

std::string getmd5bytes(std::string& str) {
	MD5_CTX c;
	unsigned char md5[17] = { 0 };

	MD5_Init(&c);
	MD5_Update(&c, str.data(), str.size());
	MD5_Final(md5, &c);

	return std::string((char *)md5, 16);
}



std::string getmd5(std::string& str) {
	MD5_CTX c;
	unsigned char md5[17] = { 0 };

	MD5_Init(&c);
	MD5_Update(&c, str.data(), str.size());
	MD5_Final(md5, &c);

	unsigned char szStr[33] = { 0 };

	_HexToStr(szStr, md5, 16);
	return std::string((char *)szStr);
}