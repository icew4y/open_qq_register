#pragma once
#include <string>
#include <windows.h>
#include <algorithm>
#include <random>
#include <time.h>
using namespace std;
void split_string(const string& s, vector<string>& tokens, const string& delimiters = " ");
std::string UTF8ToGB(const char* str);
std::string GBToUTF8(const char* str);
int IsTextUTF8(char* str, ULONGLONG length);
LPWSTR asc_to_wide(const char* str);
char *wide_to_asc(LPCWSTR wstr);

std::string W2STRING(LPCWSTR wstr);
std::wstring STRING2W(const char* str);
void __ReplaceString(string & strReplace, string strOld, string strNew);
std::string __CutStr(string strSource, string strHead, string strTail);
void Hex2Str(unsigned char *pbDest, unsigned char *pbSrc, int nLen);
void Str2Hex(char *pbDest, char *pbSrc, int nLen);
std::string double_tostring(double value);
uint32_t getrand_num2(uint32_t a, uint32_t b);
std::string getrand_zw(int len);


std::string _w2a(wchar_t *w);
std::wstring _a2w(char *a);

std::string getstr(std::string& source, std::string& splitstr);
std::string unixTime2String(uint64_t n);
std::string unixTime2DateString(uint64_t n);

bool UrlEncode(const char* szSrc, char* pBuf, int cbBufLen, BOOL bUpperCase);
bool UrlDecode(const char* szSrc, char* pBuf, int cbBufLen);


bool url_decode(std::string& src, std::string& dest);

string get_rand_imei();