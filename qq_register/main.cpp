// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "deps/pch.h"
#include "packer/packer.h"
#include "deps/md5/md5.h"
#include "net/net.h"
#include "deps/qqecdh.h"
#include "packer/pack_resolver.h"
#include "misc/sms_plaform.h"
#include "misc/tlvtype/tlv_t18.h"
#include "misc/slide_recogn.h"
#include "misc/web_ecdh.h"




void init_regctx(qq_ctx& ctx) {
	//const char this_sharedkey[16] = { 0x4D, 0xA0, 0xF6, 0x14, 0xFC, 0x9F, 0x29, 0xC2, 0x05, 0x4C, 0x77, 0x04, 0x8A, 0x65, 0x66, 0xD7 };
	ctx.regctx.isSendMsg = false;
	const char _zero_key[16] = { 0 };
	const char _ksid[] = { 0x89, 0xFA, 0x12, 0x0F, 0xEE, 0x8A, 0xD9, 0x28, 0x6B, 0x9E, 0x50, 0x88, 0xF5, 0xF4, 0x59, 0x80 };
	//const char _guid[] = { 0x0C, 0x93, 0xEF, 0xC2, 0xF8, 0xA0, 0x50, 0x08, 0x76, 0xBD, 0x1C, 0xC2, 0x82, 0xA3, 0xBE, 0x04 };

	string timestr = to_string(std::time(nullptr) + 1);

	ctx.android_id = ctx.regctx.android_id = "9bb333c59b6a1897";
	ctx.apkPackageName = ctx.regctx.apkPackageName = "com.tencent.mobileqq";
	ctx.apkVersion = ctx.regctx.apkVersion = "8.3.0";
	
	ctx.ssid = ctx.regctx.bssid = "Lobby 5G";
	
	
	ctx.imei = ctx.regctx.imei = get_rand_imei();
	ctx.imei_md5 = ctx.regctx.imei_md5 = getmd5bytes(ctx.imei);
	ctx.imsi = ctx.regctx.imsi = "460077391600546";
	ctx.imsi_md5 = getmd5bytes(ctx.imsi);
	ctx.qqimsi = ctx.regctx.qqimsi = "|" + ctx.regctx.imsi  + "|A8.3.0.a9855103";

	
	timestr = to_string(std::time(nullptr) + 2);
	//ctx.ksid = ctx.regctx.ksid = getmd5bytes(timestr);
	//ctx.guid = ctx.regctx.guid = getmd5bytes(timestr);
	ctx.ksid = ctx.regctx.ksid = string(_ksid, sizeof(_ksid));

	ctx.wifi_mac = ctx.regctx.wifi_mac = "02:00:00:00:00:00";
	ctx.model_type = ctx.regctx.model_type = "Nexus 6P";
	ctx.os_language = ctx.regctx.os_language = "zh";
	ctx.osVersion = ctx.regctx.osVersion = "6.0.1";
	ctx.phone_brand = ctx.regctx.phone_brand = "google";
	ctx.qqVersion = ctx.regctx.qqVersion = "8.3.0";
	ctx.zero_key = ctx.regctx.zero_key = string(_zero_key, sizeof(_zero_key));


	string temp = ctx.android_id + ctx.wifi_mac;
 	ctx.guid = ctx.regctx.guid = getmd5bytes(temp);
	//ctx.guid = ctx.regctx.guid = hex_to_string("3EB4A515C9EC426C9A8EE48930FE30F6");

	ctx.seq = ctx.regctx.seq = 0;
	ctx.msgcookie = ctx.regctx.msgcookie = 0;

	ctx.regctx.area_code = "86";
	ctx.regctx.nickName = "";

	
	ctx.regctx.phoneToken = "";
	

	timestr = std::to_string(time(NULL) + 2);
	ctx.regctx.unknow_randmd5 = getmd5bytes(timestr);

	

	std::string prikey_gen;
	ecdh::GetShareKey(&ctx.regctx.pubkey, &prikey_gen, &ctx.regctx.shared_key);

}

void init_qqctx(qq_ctx* ctx) {
	const char pkgSigture[] = { 0xA6, 0xB7, 0x45, 0xBF, 0x24, 0xA2, 0xC2, 0x77, 0x52, 0x77, 0x16, 0xF6, 0xF3, 0x6E, 0xB6, 0x8D };
	ctx->pkgSigture = string(pkgSigture, sizeof(pkgSigture));
	ctx->network_type = 2;
	ctx->qqid = ctx->regctx.qqid;
	ctx->qqstr = to_string(ctx->qqid);
	ctx->pwd_md5key = get_loginkey(ctx->qqid, ctx->qqpassword);
	string timestr = to_string(std::time(nullptr));
	ctx->tgtgt_key = getmd5bytes(timestr);
	ctx->phoneNumber = ctx->regctx.phoneNumber;

// 	std::string prikey_gen;
// 	ecdh::GetShareKey2020(&ctx->pubkey, &prikey_gen, &ctx->shared_key);
// 	ctx->pubkey = hex_to_string("04514df779aca8af31d5cabbcb36d8d428f74c9aac92b21ada28f2ea2df57b3134e4dc99ff6f21b8c447f009d57c934aed");
// 	ctx->shared_key = hex_to_string("db0ea175b5dcd1f427107f2d7e812818");


	std::string keys = webecdh::get_sharedkey_fromweb();
	if (keys.size() > 0) {
		vector<string> tokens;
		split_string(keys, tokens, "|");
		if (tokens.size() == 3) {
			ctx->pubkey = hex_to_string(tokens[0]);
			ctx->shared_key = hex_to_string(tokens[1]);
			ctx->private_key = hex_to_string(tokens[2]);
		}
	}



	ctx->wifi_mac_md5 = getmd5bytes(ctx->wifi_mac);
	ctx->bssid_md5 = getmd5bytes(ctx->ssid);
	ctx->android_id_md5 = getmd5bytes(ctx->android_id);
	ctx->sim_operator_name = "CMCC";
	ctx->apn_string = "wifi";
	timestr = to_string(std::time(nullptr) + 1);
	ctx->unknow_randmd5 = getmd5bytes(timestr);

	ctx->qqid = ctx->regctx.qqid;;
	ctx->qqpassword = ctx->regctx.password;
}

void init_tokenctx(qq_ctx* ctx){
	ctx->tokenctx.apkPackageName = "com.tencent.token";
	ctx->tokenctx.apkVersion = "6.9.15";
	ctx->tokenctx.pkgSigture = hex_to_string("CB746CE354D17D9BCD03F7F8C232F4C1");
	ctx->tokenctx.phoneNumber = ctx->phoneNumber;
	std::string keys = webecdh::get_sharedkey_fromweb();
	if (keys.size() > 0) {
		vector<string> tokens;
		split_string(keys, tokens, "|");
		if (tokens.size() == 3) {
			ctx->tokenctx.pubkey = hex_to_string(tokens[0]);
			ctx->tokenctx.shared_key = hex_to_string(tokens[1]);
			ctx->tokenctx.private_key = hex_to_string(tokens[2]);
		}
	}
	const char _zero_key[16] = { 0 };
	ctx->tokenctx.zero_key = string(_zero_key, sizeof(_zero_key));
}


void bind_token(qq_ctx* ctx) {
	UNIMPL_FUNCTION_EMPTY
}

void test_login(qq_ctx& ctx) {
	UNIMPL_FUNCTION_EMPTY
}

void test_login2() {
	UNIMPL_FUNCTION_EMPTY
}


static char letters[] = { "abcdefghijklmnopqrstuvwxyz" };
static char numbers[] = { "1234567890" };
std::string general_pwd()
{
	std::string newpwd;
	for (int i = 0; i < 5; i++) {
		newpwd += letters[getrand_num2(0, 25)];
	}
	for (int i = 0; i < 5; i++) {
		newpwd += numbers[getrand_num2(0, 9)];
	}
	return newpwd;
}



void register_qq(bool withProxy) {
	sms::SMSInterface smsinterface(sms::TYPE::ZHIJING, "账号", "密码", "项目ID");
	smsinterface.login();
	bool success = false;
	do
	{
		if (success) 
			break;
		qq_ctx ctx;
		init_regctx(ctx);

		std::string phone;
		smsinterface.getphone(phone);

		if (phone.length() == 0) {
			printf("获取手机号码失败了.\n");
			std::this_thread::sleep_for(5s);
			continue;
		}
		ctx.regctx.phoneNumber = phone;

		printf("shared_key: %s\n", spacing_string(bufutil::string_to_hex(ctx.regctx.shared_key)).c_str());
		printf("phone: %s\n", phone.c_str());

		

		string packdata = packer::packer_build_RegSubmitMobile(&ctx);
		
		SOCKET s;
		if (withProxy) {
			string http_host, http_port;
			do
			{
				string http_proxie = net::http_get("[自己的代理ip池]",
					"", NULL, "", false, true, false);
				vector<string> proxie;
				split_string(http_proxie, proxie, std::string(":"));
				if (proxie.size() == 2) {
					http_host = proxie[0];
					http_port = proxie[1];
					break;
				}
				std::this_thread::sleep_for(3s);
			} while (true);
			s = net::_connect_with_http_proxy(http_host, std::stod(http_port), "14.215.138.105", 8080);
		}
		else {
			s = net::_connecet("14.215.138.105", 8080);
		}



		
		int rc = net::_send(s, packdata.data(), packdata.length());
		string rsp = net::_receive(s);
		int result = resolver::resolve_pack(&ctx, rsp);

		switch (result)
		{
		case STATUS_FAILED: {
			break;
		}
		case STATUS_RECV_MSG: {
			smsinterface.getphone_msgcode(ctx.regctx.smscode);
			if (ctx.regctx.smscode.length() == 6) {
				ctx.regctx.smscode_md5key = getmd5bytes(ctx.regctx.smscode);

				printf("smscode_md5key: %s\n", spacing_string(bufutil::string_to_hex(ctx.regctx.smscode_md5key)).c_str());

				packdata = packer::packer_build_RegSubmitMsgChk(&ctx);
				rc = net::_send(s, packdata.data(), packdata.length());
				rsp = net::_receive(s);
				result = resolver::resolve_pack(&ctx, rsp);

				if (result == STATUS_RECV_MSG) {
					ctx.regctx.nickName = GBToUTF8("i_am_nickname");
					ctx.regctx.password = "i_am_qq_password";
					packdata = packer::packer_build_RegGetAccount(&ctx);
					rc = net::_send(s, packdata.data(), packdata.length());
					rsp = net::_receive(s);
					result = resolver::resolve_pack(&ctx, rsp);

					if (result == STATUS_RECV_MSG) {
						printf("注册成功QQ:%I64u, 密码:%s, 手机:%s\n", ctx.regctx.qqid, ctx.regctx.password.c_str(), ctx.regctx.phoneNumber.c_str());
						test_login(ctx);
						success = true;
					}

				}
			}
			break;
		}
		case STATUS_SEND_MSG: {
			ctx.regctx.isSendMsg = true;
			
			if (smsinterface.sendmsgcode(ctx.regctx.recv_phoneNumber, ctx.regctx.sendsms)) {
				int retry = 3;
				do
				{
					std::this_thread::sleep_for(15s);
					packdata = packer::packer_build_RegQueryClientSentMsgStatus(&ctx);
					rc = net::_send(s, packdata.data(), packdata.length());
					rsp = net::_receive(s);
					result = resolver::resolve_pack(&ctx, rsp);

					if (result == STATUS_RECV_MSG) {
						ctx.regctx.nickName = GBToUTF8("i_am_nickname");
						ctx.regctx.password = "i_am_qq_password";
						packdata = packer::packer_build_RegGetAccount(&ctx);
						rc = net::_send(s, packdata.data(), packdata.length());
						rsp = net::_receive(s);
						result = resolver::resolve_pack(&ctx, rsp);

						if (result == STATUS_RECV_MSG) {
							printf("注册成功QQ:%I64u, 密码:%s, 手机:%s\n", ctx.regctx.qqid, ctx.regctx.password.c_str(), ctx.regctx.phoneNumber.c_str());
							success = true;
							test_login(ctx);
							break;
						}
					}
					retry--;
				} while (retry > 0);

			}
			break;
		}
		default:
			break;
		}

		net::_close(s);
		smsinterface.release_phone();
		std::this_thread::sleep_for(1s);
	} while (true);
}




void login_qq() {
	test_login2();
}


void bind_tokencode() {
	UNIMPL_FUNCTION_EMPTY
}

int main()
{
	register_qq(false);
	//login_qq();
	int r;
	cin >> r;
	bind_tokencode();
	
}
