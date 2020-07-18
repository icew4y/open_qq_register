#pragma once
#include "pch.h"


#define STATUS_FAILED -1
#define STATUS_RECV_MSG 1
#define STATUS_SEND_MSG 2

struct register_ctx
{
	uint32_t seq;
	uint32_t msgcookie;
	string area_code;
	string phoneNumber;
	string phoneToken;
	string nickName;
	string password;

	bool isSendMsg;
	//收到的短信
	string smscode;
	//腾讯收短信的号码
	string recv_phoneNumber;
	//要发的短信
	string sendsms;

	string shared_key;
	string pubkey;
	string zero_key;
	//收短信密钥
	string smscode_md5key;
	//发短信密钥
	string sendsms_md5key;


	string osVersion, qqVersion, apkPackageName, apkVersion;
	string phone_brand, model_type, wifi_mac, os_language, bssid;


	string imei;
	string imei_md5;
	string imsi;
	string qqimsi;
	string mac;
	string android_id;
	string guid;
	string ksid;

	string unknow_randmd5;

	uint64_t qqid;
};


struct captcha_ctx
{
	//识别需要的参数
	string url;
	string captcha_sig;
	//提交识别结果的参数
	string captcha_ticket;
	string tlv402;
	string tlv403;
};

struct token_ctx
{
	string phoneNumber;
	string apkPackageName, apkVersion, pkgSigture;
	string shared_key;
	string pubkey;
	string private_key;
	string zero_key;
	string tgtgt_key;
	string tlv16A, tlv106, tlv10C;
	string tlv10A_a2key;
};


struct qq_ctx
{
	register_ctx regctx;
	captcha_ctx cptctx;
	token_ctx tokenctx;

	uint64_t qqid;
	string qqstr;
	string qqpassword;
	uint32_t seq;
	uint32_t msgcookie;
	string phoneNumber;

	string shared_key;
	string pubkey;
	string private_key;
	string zero_key;
	string pwd_md5key;
	string tgtgt_key;

	string osVersion, qqVersion, apkPackageName, apkVersion, pkgSigture;
	string phone_brand, model_type, os_language;


	string imei;
	string imei_md5;
	string imsi;
	string imsi_md5;
	string qqimsi;
	string wifi_mac;
	string wifi_mac_md5;
	string ssid;
	string bssid_md5;
	string android_id;
	string android_id_md5;
	string sim_operator_name;
	//"wifi" "CMCC"
	string apn_string;
	string guid;
	string ksid;
	string unknow_randmd5;

	//2 wifi
	int16_t network_type;

	int16_t login_retcode;


	string tlv16A, tlv106, tlv10C;
};