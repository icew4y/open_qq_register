

#include "strutil.h"
#include "md5/md5.h"



void split_string(const string& s, vector<string>& tokens, const string& delimiters)
{
	string::size_type lastPos = s.find_first_not_of(delimiters, 0);
	string::size_type pos = s.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos) {
		tokens.push_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
}


std::string UTF8ToGB(const char* str)
{
	string result;
	WCHAR* strSrc;
	CHAR* szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, nullptr, 0, nullptr, nullptr);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, nullptr, nullptr);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

string GBToUTF8(const char* str)
{
	string result;
	WCHAR* strSrc;
	CHAR* szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_ACP, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, nullptr, 0, nullptr, nullptr);
	szRes = new CHAR[i + 1];
	memset(szRes, 0, i + 1);
	int j = WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, szRes, i, nullptr, nullptr);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

int IsTextUTF8(char* str, ULONGLONG length)
{
	int i;
	DWORD nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节
	UCHAR chr;
	BOOL bAllAscii = TRUE; //如果全部都是ASCII, 说明不是UTF-8
	for (i = 0; i < length; i++)
	{
		chr = *(str + i);
		if ((chr & 0x80) != 0) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
			bAllAscii = FALSE;
		if (nBytes == 0) //如果不是ASCII码,应该是多字节符,计算字节数
		{
			if (chr >= 0x80)
			{
				if (chr >= 0xFC && chr <= 0xFD)
					nBytes = 6;
				else if (chr >= 0xF8)
					nBytes = 5;
				else if (chr >= 0xF0)
					nBytes = 4;
				else if (chr >= 0xE0)
					nBytes = 3;
				else if (chr >= 0xC0)
					nBytes = 2;
				else
				{
					return FALSE;
				}
				nBytes--;
			}
		}
		else //多字节符的非首字节,应为 10xxxxxx
		{
			if ((chr & 0xC0) != 0x80)
			{
				return FALSE;
			}
			nBytes--;
		}
	}
	if (nBytes > 0) //违返规则
	{
		return FALSE;
	}
	if (bAllAscii) //如果全部都是ASCII, 说明不是UTF-8
	{
		return FALSE;
	}
	return TRUE;
}

LPWSTR asc_to_wide(const char* str)
{
	LPWSTR wstr;
	int len_0, sz;
	if (!str)
		return NULL;
	len_0 = strlen(str) + 1;
	sz = MultiByteToWideChar(CP_ACP, 0, str, len_0, NULL, 0);
	if (!sz) {
		return NULL;
	}
	wstr = (LPWSTR)malloc(sz * sizeof(wchar_t));
	if (!wstr) {
		return NULL;
	}
	if (!MultiByteToWideChar(CP_ACP, 0, str, len_0, wstr, sz)) {
		free(wstr);
		return NULL;
	}
	return wstr;
}


char *wide_to_asc(LPCWSTR wstr)
{
	char *str;
	int len_0, sz;

	if (!wstr)
		return NULL;
	len_0 = (int)wcslen(wstr) + 1; /* WideCharToMultiByte expects int */
	sz = WideCharToMultiByte(CP_ACP, 0, wstr, len_0, NULL, 0, NULL, NULL);
	if (!sz) {
		return NULL;
	}
	str = (char *)malloc(sz);
	if (!str) {
		return NULL;
	}
	if (!WideCharToMultiByte(CP_ACP, 0, wstr, len_0, str, sz, NULL, NULL)) {
		free(str);
		return NULL;
	}
	return str;
}

std::string W2STRING(LPCWSTR wstr)
{
	char *astr = wide_to_asc(wstr);
	std::string retstr = astr;
	free(astr);
	return retstr;
}

std::wstring STRING2W(const char* str)
{
	LPWSTR wstr = asc_to_wide(str);
	std::wstring retwstr = wstr;
	free(wstr);
	return retwstr;
}




/******************************************************************************
字符串替换
******************************************************************************/
void __ReplaceString(string & strReplace, string strOld, string strNew)
{
	string::size_type nFindStartPos = 0;
	string::size_type nFoundPos = string::npos;
	string::size_type nOldLen = strOld.length();
	string::size_type nNewLen = strNew.length();

	//要替换的字符串为空，没法替换
	if (strOld == ""
		|| nOldLen == 0)
	{
		return;
	}

	//源串为空，没法替换
	if (strReplace == "")
	{
		return;
	}

	//替换每一处
	while (true)
	{
		//寻找要替换的字符串位置
		nFoundPos = strReplace.find(strOld, nFindStartPos);

		if (nFoundPos == string::npos)
		{
			break;
		}

		//替换掉
		strReplace.replace(nFoundPos, nOldLen, strNew);

		//搜索起始位置下移
		nFindStartPos = nFoundPos + nNewLen;

		if (nFindStartPos >= strReplace.length())
		{
			break;
		}
	}
}

/******************************************************************************
小写字符串
******************************************************************************/
void __ToLower(string & strLower)
{
	if (strLower == "")
	{
		return;
	}

	transform(strLower.begin(), strLower.end()
		, strLower.begin(), tolower);
}

/******************************************************************************
定位字符串
******************************************************************************/
bool __PosStr(string::size_type & nPos, string::size_type & nLen,
	string strSourceLow, string strHeadLow, string strTailLow)
{
	if (strSourceLow == "")
	{
		return false;
	}

	//头定位
	string::size_type nHeadPos = strSourceLow.find(strHeadLow);

	if (nHeadPos == string::npos)
	{
		return false;
	}

	//内容定位
	string::size_type nValuePos = nHeadPos + strlen(strHeadLow.c_str());

	if (nValuePos >= strSourceLow.length())
	{
		return false;
	}

	//尾定位
	string::size_type nTailPos = strSourceLow.find(strTailLow, nValuePos);

	if (nTailPos == string::npos)
	{
		return false;
	}

	//如果尾定位字符串为空，则认为定位到源字符串最后
	if (strTailLow == "")
	{
		nTailPos = strSourceLow.length();
	}

	//返回定位结果
	nPos = nValuePos;

	if (nTailPos < nValuePos)
	{
		return false;
	}

	nLen = nTailPos - nValuePos;

	return true;
}

/******************************************************************************
截取字符串
******************************************************************************/
std::string __CutStr(string strSource, string strHead, string strTail)
{
	if (strSource == "")
	{
		return "";
	}

	//便于定位，剔除所有空格
	//__ReplaceString(strSource, " ", "");

	if (strSource == "")
	{
		return "";
	}

	//便于定位，转换成小写
	string strSourceLow = strSource;
	string strHeadLow = strHead;
	string strTailLow = strTail;

	__ToLower(strSourceLow);
	__ToLower(strHeadLow);
	__ToLower(strTailLow);

	//定位字符串
	string::size_type nPos = 0;
	string::size_type nLen = 0;

	if (strSourceLow == "")
	{
		return "";
	}

	if (!__PosStr(nPos, nLen, strSourceLow, strHeadLow, strTailLow))
	{
		return "";
	}

	if (nPos < 0
		|| nPos >= strSource.length()
		|| nLen < 0)
	{
		return "";
	}

	//截取字符串
	return strSource.substr(nPos, nLen);

}

void Hex2Str(unsigned char *pbDest, unsigned char *pbSrc, int nLen)
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

void Str2Hex(char *pbDest, char *pbSrc, int nLen)
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

std::string double_tostring(double value) {
	std::string s = std::to_string(value);

	std::string::size_type pos = s.find('.');
	if (pos != std::string::npos) {
		if ( (s.length() - (pos + 1)) > 2) {
			s = s.substr(0, pos + 3);
		}
	}

	if (s.find('.') != s.npos) {
		size_t p = s.find_last_not_of('0');
		if (p != s.npos)
			s = s.substr(0, p + 1);
	}

	if (s.at(s.length() - 1) == '.') {
		s = s.substr(0, s.length() - 1);
	}

	return s;
}

/*
** return a random integer in the interval [a, b]
*/
uint32_t getrand_num2(uint32_t a, uint32_t b) {
	static std::default_random_engine e{ std::random_device{}() }; // avoid "Most vexing parse"  
	static std::uniform_int_distribution<int> u;

	return u(e, decltype(u)::param_type(a, b));
}


/*
** return a random integer in the interval [a, b]
*/
uint32_t getrand_int(int a, int b) {
	static std::default_random_engine e{ std::random_device{}() }; // avoid "Most vexing parse"  
	static std::uniform_int_distribution<int> u;

	return u(e, decltype(u)::param_type(a, b));
}


std::string _w2a(wchar_t *w)
{
	std::string str;
	char *astr = wide_to_asc(w);
	if (astr) {
		str = astr;
		free(astr);
	}
	return str;
}

std::wstring _a2w(char *a)
{
	std::wstring wstr;
	wchar_t *w = asc_to_wide(a);
	if (w) {
		wstr = w;
		free(w);
	}
	return wstr;
}

std::string getstr(std::string& source, std::string& splitstr)
{
	std::string tmp;
	std::string::size_type position = source.find(splitstr);
	if (position == std::string::npos) {
		tmp = source;
		source.clear();
	}
	else {
		tmp = source.substr(0, position);
		source.erase(0, position + splitstr.length());
	}
	return tmp;
}

std::string unixTime2String(uint64_t n)
{
	std::string ret;
	char strTime[200] = { 0 };
	struct tm tm = *localtime((time_t *)&n);
	strftime(strTime, 200 - 1, "%H:%M:%S", &tm);
	return ret = strTime;
}


std::string unixTime2DateString(uint64_t n)
{
	std::string ret;
	char strTime[200] = { 0 };
	struct tm tm = *localtime((time_t *)&n);
	strftime(strTime, 200 - 1, "%Y%m%d", &tm);
	return ret = strTime;
}





//百分号编码
//http://zh.wikipedia.org/zh-cn/%E7%99%BE%E5%88%86%E5%8F%B7%E7%BC%96%E7%A0%81

bool UrlEncode(const char* szSrc, char* pBuf, int cbBufLen, BOOL bUpperCase)
{
	if (szSrc == NULL || pBuf == NULL || cbBufLen <= 0)
		return FALSE;

	size_t len_ascii = strlen(szSrc);
	if (len_ascii == 0)
	{
		pBuf[0] = 0;
		return TRUE;
	}

	//先转换到UTF-8
	char baseChar = bUpperCase ? 'A' : 'a';
	int cchWideChar = MultiByteToWideChar(CP_ACP, 0, szSrc, len_ascii, NULL, 0);
	LPWSTR pUnicode = (LPWSTR)malloc((cchWideChar + 1) * sizeof(WCHAR));
	if (pUnicode == NULL)
		return FALSE;
	MultiByteToWideChar(CP_ACP, 0, szSrc, len_ascii, pUnicode, cchWideChar + 1);

	int cbUTF8 = WideCharToMultiByte(CP_UTF8, 0, pUnicode, cchWideChar, NULL, 0, NULL, NULL);
	LPSTR pUTF8 = (LPSTR)malloc((cbUTF8 + 1) * sizeof(CHAR));
	if (pUTF8 == NULL)
	{
		free(pUnicode);
		return FALSE;
	}
	WideCharToMultiByte(CP_UTF8, 0, pUnicode, cchWideChar, pUTF8, cbUTF8 + 1, NULL, NULL);
	pUTF8[cbUTF8] = '\0';

	unsigned char c;
	int cbDest = 0; //累加
	unsigned char *pSrc = (unsigned char*)pUTF8;
	unsigned char *pDest = (unsigned char*)pBuf;
	while (*pSrc && cbDest < cbBufLen - 1)
	{
		c = *pSrc;
		if (isalpha(c) || isdigit(c) || c == '-' || c == '.' || c == '~')
		{
			*pDest = c;
			++pDest;
			++cbDest;
		}
		else if (c == ' ')
		{
			*pDest = '+';
			++pDest;
			++cbDest;
		}
		else
		{
			//检查缓冲区大小是否够用？
			if (cbDest + 3 > cbBufLen - 1)
				break;
			pDest[0] = '%';
			pDest[1] = (c >= 0xA0) ? ((c >> 4) - 10 + baseChar) : ((c >> 4) + '0');
			pDest[2] = ((c & 0xF) >= 0xA) ? ((c & 0xF) - 10 + baseChar) : ((c & 0xF) + '0');
			pDest += 3;
			cbDest += 3;
		}
		++pSrc;
	}
	//null-terminator
	*pDest = '\0';
	free(pUnicode);
	free(pUTF8);
	return TRUE;
}

//解码后是utf-8编码
bool UrlDecode(const char* szSrc, char* pBuf, int cbBufLen)
{
	if (szSrc == NULL || pBuf == NULL || cbBufLen <= 0)
		return FALSE;

	size_t len_ascii = strlen(szSrc);
	if (len_ascii == 0)
	{
		pBuf[0] = 0;
		return TRUE;
	}

	char *pUTF8 = (char*)malloc(len_ascii + 1);
	if (pUTF8 == NULL)
		return FALSE;

	int cbDest = 0; //累加
	unsigned char *pSrc = (unsigned char*)szSrc;
	unsigned char *pDest = (unsigned char*)pUTF8;
	while (*pSrc)
	{
		if (*pSrc == '%')
		{
			*pDest = 0;
			//高位
			if (pSrc[1] >= 'A' && pSrc[1] <= 'F')
				*pDest += (pSrc[1] - 'A' + 10) * 0x10;
			else if (pSrc[1] >= 'a' && pSrc[1] <= 'f')
				*pDest += (pSrc[1] - 'a' + 10) * 0x10;
			else
				*pDest += (pSrc[1] - '0') * 0x10;

			//低位
			if (pSrc[2] >= 'A' && pSrc[2] <= 'F')
				*pDest += (pSrc[2] - 'A' + 10);
			else if (pSrc[2] >= 'a' && pSrc[2] <= 'f')
				*pDest += (pSrc[2] - 'a' + 10);
			else
				*pDest += (pSrc[2] - '0');

			pSrc += 3;
		}
		else if (*pSrc == '+')
		{
			*pDest = ' ';
			++pSrc;
		}
		else
		{
			*pDest = *pSrc;
			++pSrc;
		}
		++pDest;
		++cbDest;
	}
	//null-terminator
	*pDest = '\0';
	++cbDest;

	int cchWideChar = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pUTF8, cbDest, NULL, 0);
	LPWSTR pUnicode = (LPWSTR)malloc(cchWideChar * sizeof(WCHAR));
	if (pUnicode == NULL)
	{
		free(pUTF8);
		return FALSE;
	}
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pUTF8, cbDest, pUnicode, cchWideChar);
	WideCharToMultiByte(CP_ACP, 0, pUnicode, cchWideChar, pBuf, cbBufLen, NULL, NULL);
	free(pUTF8);
	free(pUnicode);
	return TRUE;
}

bool url_decode(std::string& src, std::string& dest)
{
	bool bret = false;
	char szBuf[5000] = { 0 };

	bret = UrlDecode(src.c_str(), szBuf, 5000);
	dest = std::string(szBuf);
	return bret;
}


unsigned long CGIBASE_AutoChangeIMEI(char* pcSource, char* pcDest)
{
	int i, j, k;
	int iTotal, iEvenTotal, iAddTotal, iTemp, iAuth;
	char acEven[10], acAdd[10], acTemp[3], acAuth[2];

	if ((nullptr == pcSource) || (nullptr == pcDest))
	{
		return 1;
	}

	memset(acEven, 0x0, sizeof(acEven));
	memset(acAdd, 0x0, sizeof(acAdd));
	j = 0;
	k = 0;
	iTemp = 0;
	iEvenTotal = 0;
	iAddTotal = 0;
	iTotal = 0;
	iAuth = 0;

	for (i = 0; i < 14; i++)
	{
		if (0 == (i % 2))
		{
			acEven[j] = *(pcSource + i);
			memset(acTemp, 0x0, sizeof(acTemp));
			sprintf(acTemp, "%c", acEven[j]);
			iTemp = atoi(acTemp);
			iEvenTotal += iTemp;
			j += 1;
		}
		else
		{
			acAdd[k] = *(pcSource + i);
			memset(acTemp, 0x0, sizeof(acTemp));
			sprintf(acTemp, "%c", acAdd[k]);
			iTemp = atoi(acTemp) * 2;
			iAddTotal += (iTemp / 10) + (iTemp % 10);
			k += 1;
		}
	}

	iTotal = iEvenTotal + iAddTotal;
	if (iTotal >= 100)
	{
		iAuth = iTotal % 100 % 10;
		if (iAuth != 0)
		{
			iAuth = ((iTotal % 100) / 10 + 1) * 10 - iTotal % 100;
		}
	}
	else
	{
		iAuth = iTotal % 10;
		if (iAuth != 0)
		{
			iAuth = (iTotal / 10 + 1) * 10 - iTotal;
		}
	}
	memset(acAuth, 0x0, sizeof(acAuth));
	sprintf(acAuth, "%d", iAuth);
	strcat(pcDest, pcSource);
	strcat(pcDest, acAuth);

	return 0;
}

/*
** return a random integer in the interval [a, b]
*/
uint32_t getrandnum_fromrange(uint32_t a, uint32_t b) {
	static std::default_random_engine e{ std::random_device{}() }; // avoid "Most vexing parse"  
	static std::uniform_int_distribution<int> u;

	return u(e, decltype(u)::param_type(a, b));
}



std::string get_rand_imei()
{
	//895836313808217
	string result = "895836";
	
	for (int Index = 0; Index < 9 ; Index++)
	{
		result.append(std::to_string(getrandnum_fromrange(0, 9)));
	}

	//CGIBASE_AutoChangeIMEI(IMEI, _IMEI);
	return result;
}


