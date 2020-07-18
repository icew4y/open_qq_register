
#include "packer.h"
#include "../deps/tlv/tlv_box.h"
#include "../deps/tlv/tlv.h"
#include "../misc/tarsproto/tup/Tars.h"
#include "../misc/tarsproto/tup/tup.h"
#include "../misc/tarsproto/KQQ_ProfileService_ProfileServantObj.h"
#include "../misc/tarsproto/KQQ_ConfigService_ConfigServantObj.h"
#include "../misc/protobuf_proto/sec_trans.pb.h"
#include "../misc/tlvtype/tlv_t525.h"
#include "../misc/tlvtype/tlv_t544.h"
#include "../misc/tlvtype/tlv_t193.h"
#include "../misc/tlvtype/tlv_t104.h"
#include "../misc/tlvtype/tlv_t547.h"
#include "../misc/tlvtype/tlv_t194.h"
#include "../misc/tlvtype/tlv_t16a.h"
#include "../misc/tlvtype/tlv_t166.h"
#include "../misc/tlvtype/tlv_t401.h"


using namespace tars;
using namespace tup;
using namespace KQQ_ProfileService_ProfileServantObj;
using namespace KQQ_ProfileService_ConfigServantObj;
using namespace sec_trans;


string buile_login_header(qq_ctx* ctx, string cmd) {
	string header_msg; {

		//seq
		int32_to_buf(ctx->seq, header_msg);
		//appid
		int32_t appid1 = 0x2002F060;
		int32_t appid2 = 0x2002F060;
		int32_to_buf(appid1, header_msg);
		int32_to_buf(appid2, header_msg);


		//
		string unknow_12bytes = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };
		string_to_buf(unknow_12bytes, header_msg);


		//
		//string unknow_empty = hex_to_string("84CD3F1DD7672B596DE9E3285F65D43CF15840A767AD82246BDEE688C25398D6C19BAFEFD37B0F72336255911F53496AF1A6AB6FFD7E6A223F2E5D1340D7B0674660FFDCB23705BC");
		string unknow_empty = "";
		int32data_to_buf(unknow_empty, header_msg, true);

		//cmd
		//string cmd = "wtlogin.login";
		int32data_to_buf(cmd, header_msg, true);

		//msgcookie
		//ctx->msgcookie += 2;
		int32_t msgcookie_ = htonl(ctx->msgcookie);
		string msgcookie_str = string((const char*)&msgcookie_, sizeof(ctx->msgcookie));
		int32data_to_buf(msgcookie_str, header_msg, true);

		//imei
		int32data_to_buf(ctx->imei, header_msg, true);
		//ksid
		int32data_to_buf(ctx->ksid, header_msg, true);
		//imsi
		int16data_to_buf(ctx->qqimsi, header_msg, true);

		//
		string unknow2_empty = "";
		int32data_to_buf(unknow2_empty, header_msg, true);
	}
	return header_msg;
}

string buile_login_body(qq_ctx* ctx, int16_t CryptVersionInfo, string& tlvdata, string& pubkey, string& sharedkey) {
	string body_msg; {


		/*

	private void a(int 0x1f41, int cmd, long arg8, int 87_07, int arg11, int arg12, int arg13, int arg14) {
		int subcmd = this.j + 1;
		this.j = subcmd;
		this.c = 0;
		util.int8_to_buf(this.decode_data, this.c, 2);
		++this.c;
		util.int16_to_buf(this.decode_data, this.c, this.d + 2 + arg14);
		this.c += 2;
		util.int16_to_buf(this.decode_data, this.c, 0x1f41);
		this.c += 2;
		util.int16_to_buf(this.decode_data, this.c, cmd);
		this.c += 2;
		util.int16_to_buf(this.decode_data, this.c, subcmd);
		this.c += 2;
		util.int32_to_buf(this.decode_data, this.c, ((int)arg8));
		this.c += 4;
		util.int8_to_buf(this.decode_data, this.c, 3);
		++this.c;
		util.int8_to_buf(this.decode_data, this.c, 87_07);
		++this.c;
		util.int8_to_buf(this.decode_data, this.c, arg11);
		++this.c;
		util.int32_to_buf(this.decode_data, this.c, 2);
		this.c += 4;
		util.int32_to_buf(this.decode_data, this.c, arg12);
		this.c += 4;
		util.int32_to_buf(this.decode_data, this.c, arg13);
		this.c += 4;
	}

		*/
		//begin sign
		int8_to_buf(0x02, body_msg);
		//len
		int16_t fix_body_len = 0;
		int fix_pos = int16_to_buf(fix_body_len, body_msg);
		//pcVer: 8001(0x1F41)
		int16_t pcVer = 0x1F41;
		int16_to_buf(pcVer, body_msg);
		//cmd: 2064(0x0810)
		int16_t cmd = 0x0810;
		int16_to_buf(cmd, body_msg);
		//sub_cmd: 1(0x0001)
		int16_t sub_cmd = 0x0001;
		int16_to_buf(sub_cmd, body_msg);



		//qqnum: 0(0x00000000) 注册时为0

		int32_to_buf(ctx->qqid, body_msg);
		//CryptVersionInfo
		int16_to_buf(CryptVersionInfo, body_msg);
		//qqCryptVersionInfo: 00 00 00 00 02 00 00 00 00 00 00 00 00
		string qqCryptVersionInfo = { 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		string_to_buf(qqCryptVersionInfo, body_msg);
		//unknow: 257(0x0101)
		int16_t unknow = 0x0101;
		int16_to_buf(unknow, body_msg);

		//unknow rand md5
		string_to_buf(ctx->unknow_randmd5, body_msg);

		//unknow3: 258(0x0102)
		int16_t unknow3 = 0x0102;
		int16_to_buf(unknow3, body_msg);
		//pubkey
		int16data_to_buf(pubkey, body_msg);

		//tlv data
		string encrypt_tlvdata = bufutil::tea_encrypt(tlvdata.data(), tlvdata.length(), sharedkey.data());





		//merge trans_msg
		string_to_buf(encrypt_tlvdata, body_msg);

		//end sign
		int8_to_buf(0x03, body_msg);


		//填充大小
		fix_body_len = htons(body_msg.length());
		fix_buf_data(fix_pos, (const char*)&fix_body_len, sizeof(fix_body_len), body_msg);
	}
	return body_msg;
}

string _test_buile_login_body(qq_ctx* ctx, int16_t CryptVersionInfo, string& tlvdata) {
	string body_msg; {

		//begin sign
		int8_to_buf(0x02, body_msg);
		//len
		int16_t fix_body_len = 0;
		int fix_pos = int16_to_buf(fix_body_len, body_msg);
		//pcVer: 8001(0x1F41)
		int16_t pcVer = 0x1F41;
		int16_to_buf(pcVer, body_msg);
		//cmd: 2064(0x0810)
		int16_t cmd = 0x0810;
		int16_to_buf(cmd, body_msg);
		//sub_cmd: 1(0x0001)
		int16_t sub_cmd = 0x0001;
		int16_to_buf(sub_cmd, body_msg);



		//qqnum: 0(0x00000000) 注册时为0

		int32_to_buf(ctx->qqid, body_msg);
		//CryptVersionInfo
		int16_to_buf(CryptVersionInfo, body_msg);
		//qqCryptVersionInfo: 00 00 00 00 02 00 00 00 00 00 00 00 00
		string qqCryptVersionInfo = { 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		string_to_buf(qqCryptVersionInfo, body_msg);
		//unknow: 257(0x0101)
		int16_t unknow = 0x0101;
		int16_to_buf(unknow, body_msg);

		//unknow rand md5
		string_to_buf(ctx->unknow_randmd5, body_msg);

		//unknow3: 258(0x0102)
		int16_t unknow3 = 0x0102;
		int16_to_buf(unknow3, body_msg);
		//pubkey
		int16data_to_buf(ctx->pubkey, body_msg);

		//tlv data
		string encrypt_tlvdata = bufutil::tea_encrypt(tlvdata.data(), tlvdata.length(), ctx->shared_key.data());




		//merge trans_msg
		string_to_buf(encrypt_tlvdata, body_msg);

		//end sign
		int8_to_buf(0x03, body_msg);


		//填充大小
		fix_body_len = htons(body_msg.length());
		fix_buf_data(fix_pos, (const char*)&fix_body_len, sizeof(fix_body_len), body_msg);
	}
	return body_msg;
}

std::string packer::packer_build_RegSubmitMobile(qq_ctx* ctx)
{
	string msg;
	uint32_t fix_len = 0;
	int fix_pos = int32_to_buf(fix_len, msg);

	string header_type = { 0x00, 0x00, 0x00, 0x0A, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x05, 0x30 };

	string_to_buf(header_type, msg);

	string header_msg; {

		//seq
		int32_to_buf(ctx->regctx.seq, header_msg);
		//appid
		int32_t appid1 = 0x2002F060;
		int32_t appid2 = 0x2002F060;
		int32_to_buf(appid1, header_msg);
		int32_to_buf(appid2, header_msg);


		//
		string unknow_12bytes = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };
		string_to_buf(unknow_12bytes, header_msg);


		//
		string unknow_empty = "";
		int32data_to_buf(unknow_empty, header_msg, true);

		//cmd
		string cmd = "wtlogin.trans_emp";
		int32data_to_buf(cmd, header_msg, true);

		//msgcookie
		string msgcookie_str = string((const char*)&ctx->regctx.msgcookie, sizeof(ctx->regctx.msgcookie));
		int32data_to_buf(msgcookie_str, header_msg, true);

		//imei
		int32data_to_buf(ctx->regctx.imei, header_msg, true);
		//ksid
		int32data_to_buf(ctx->regctx.ksid, header_msg, true);
		//imsi
		int16data_to_buf(ctx->regctx.qqimsi, header_msg, true);

		//
		string unknow2_empty = "";
		int32data_to_buf(unknow2_empty, header_msg, true);
	}

	string body_msg; {
		//begin sign
		int8_to_buf(0x02, body_msg);
		//len
		int16_t fix_body_len = 0;
		int fix_pos = int16_to_buf(fix_body_len, body_msg);
		//pcVer: 8001(0x1F41)
		int16_t pcVer = 0x1F41;
		int16_to_buf(pcVer, body_msg);
		//cmd: 2066(0x0812)
		int16_t cmd = 0x0812;
		int16_to_buf(cmd, body_msg);
		//sub_cmd: 1(0x0001)
		int16_t sub_cmd = 0x0001;
		int16_to_buf(sub_cmd, body_msg);
	
		//qqnum: 0(0x00000000) 注册时为0
		int16_t qqnum = 0;
		int32_to_buf(qqnum, body_msg);
		//qqCryptVersionInfo: 03 07 00 00 00 00 02 00 00 00 00 00 00 00 00
		string qqCryptVersionInfo = { 0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		string_to_buf(qqCryptVersionInfo, body_msg);
		//unknow: 257(0x0101)
		int16_t unknow = 0x0101;
		int16_to_buf(unknow, body_msg);

		//unknow rand md5
		string_to_buf(ctx->regctx.unknow_randmd5, body_msg);
		
		//unknow3: 258(0x0102)
		int16_t unknow3 = 0x0102;
		int16_to_buf(unknow3, body_msg);
		//pubkey
		int16data_to_buf(ctx->regctx.pubkey, body_msg);

		string trans_msg; {
			//isHas_userStSig
			int8_to_buf(0x00, trans_msg);
			//time_wrapbodyLen
			int16_t fix_timemsg_bodyLen = 0;
			int fix_pos = int16_to_buf(fix_timemsg_bodyLen, trans_msg);

			//appid
			int32_t appid = 0;
			int32_to_buf(appid, trans_msg);

			//appid
			int32_t role = 0x0000005f;
			int32_to_buf(role, trans_msg);

			//st_userStSig
			string userStSig = "";
			int16data_to_buf(userStSig, trans_msg, false);

			//rollback_sig
			string rollback_sig = "";
			int8data_to_buf(rollback_sig, trans_msg, false);

			string timefrontmsg; {

				//时间戳，谨记此字段大小不算在fix_lenOfThis里面,但是算在fix_timemsg_bodyLen里面
				uint32_t timestamp = time(NULL);
				int32_to_buf(timestamp, timefrontmsg);

				//begin sign
				int8_to_buf(0x02, timefrontmsg);

				//lenOfThis
				uint16_t fix_lenOfThis = 0;
				int fix_pos  = int16_to_buf(fix_lenOfThis, timefrontmsg);

				//uint16_t fixed_2byte_3
				uint16_t fixed_2byte_3 = 0x0003;
				int16_to_buf(fixed_2byte_3, timefrontmsg);

				//reg_cmd 00 0A,检测手机 00 05 提交短信验证码, 00 06 提交昵称和密码
				uint16_t reg_cmd = 0x000A;
				int16_to_buf(reg_cmd, timefrontmsg);

				//fixed_1byte_4
				uint8_t fixed_1byte_4 = 0x04;
				int8_to_buf(fixed_1byte_4, timefrontmsg);
				//uint32_t fixed_4byte_0 = buf_to_int32(base + pos); pos += 4;
				int32_t fixed_4byte_0 = 0;
				int32_to_buf(fixed_4byte_0, timefrontmsg);


				//st_phoneNumber
				string area_phone = ctx->regctx.area_code + "-" + ctx->regctx.phoneNumber;
				int8data_to_buf(area_phone, timefrontmsg);
				//fixed_1byte_5
				int8_t fixed_1byte_5 = 0x05;
				int8_to_buf(fixed_1byte_5, timefrontmsg);
				//st_osVersion
				int8data_to_buf(ctx->regctx.osVersion, timefrontmsg);
				//st_apkPackageName
				//string apkPackageName = "com.tencent.mobileqq";
				int8data_to_buf(ctx->regctx.apkPackageName, timefrontmsg);
				//st_apkVersion
				//string apkVersion = "8.3.0";
				int8data_to_buf(ctx->regctx.apkVersion, timefrontmsg);

				//to_register_cr_country
				int8_to_buf(0x00, timefrontmsg);
				//to_register_cr_language
				int8_to_buf(0x02, timefrontmsg);
				//to_register_cr_pigType
				int8_to_buf(0x00, timefrontmsg);

				//fixed_4byte_16
				uint32_t fixed_4byte_16 = 0x00000010;
				int32_to_buf(fixed_4byte_16, timefrontmsg);

				//unknow_4byte
				uint32_t unknow_4byte = 0;
				int32_to_buf(unknow_4byte, timefrontmsg);

				//guid
				int8data_to_buf(ctx->regctx.guid, timefrontmsg);
				//IMSI
				int8data_to_buf(ctx->regctx.imsi, timefrontmsg);

				//tlv data
				uint16_t tlvcnt = 0;
				string tlvdata; {
					string protobuf_secinfo; {
						sec_trans::SecTransInfo secinfo; {
							//secinfo.set_str_phone_brand(std::string("google"));
							//secinfo.set_str_model_type(std::string("Nexus 6P"));
							//secinfo.set_str_wifi_mac(std::string("02:00:00:00:00:00"));
							//secinfo.set_str_bssid(std::string("Lobby 5G"));
							//secinfo.set_str_os_language(std::string("zh"));
							secinfo.set_str_phone_brand(ctx->regctx.phone_brand);
							secinfo.set_str_model_type(ctx->regctx.model_type);
							secinfo.set_str_wifi_mac(ctx->regctx.wifi_mac);
							secinfo.set_str_bssid(ctx->regctx.bssid);
							secinfo.set_str_os_language(ctx->regctx.os_language);
							secinfo.set_uint32_qq_language(2052);
							secinfo.set_str_gps_location(std::string(""));
						}


						secinfo.SerializeToString(&protobuf_secinfo);
					}
					tlv::TlvBox box;
					/*
					00 02 //TagIndex:1,length:8
					00 08
					00 00 00 00 00 00 00 00
					00 04 //TagIndex:2,length:16
					00 10
					0C 93 EF C2 F8 A0 50 08 76 BD 1C C2 82 A3 BE 04
					00 0D //TagIndex:3,length:4
					00 04
					20 02 F0 60
					00 06 //TagIndex:4,length:3
					00 03
					01 00 00
					00 07 //TagIndex:5,length:4
					00 04
					00 00 00 1F
					00 12 //TagIndex:6,length:5
					00 05
					38 2E 33 2E 30
					00 25 //TagIndex:7,length:2
					00 02
					00 00
					00 32 //TagIndex:8,length:46
					00 2E
					0A 06 67 6F 6F 67 6C 65 12 08 4E 65 78 75 73 20
					36 50 1A 11 30 32 3A 30 30 3A 30 30 3A 30 30 3A
					30 30 3A 30 30 2A 02 7A 68 30 84 10 3A 00

					*/

					//ksid
					box.PutBytesValue(htons(0x0001), (unsigned char*)ctx->regctx.ksid.data(), ctx->regctx.ksid.length());

					//这里如果有其他QQ已经登陆过的话，会在这里有,并且会多出一个tlv 3，内容是_sig
					unsigned char _8Zerobytes[8] = { 0 };
					box.PutBytesValue(htons(0x0002), _8Zerobytes, sizeof(_8Zerobytes));
					//UUID
					box.PutBytesValue(htons(0x0004), (unsigned char*)ctx->regctx.guid.data(), ctx->regctx.guid.length());

					uint32_t appid = htonl(0x2002F060);
					box.PutBytesValue(htons(0x000D), (unsigned char*)&appid, sizeof(uint32_t));

					//
					unsigned char _unknow3Bytes[3] = { 0x01, 0x00, 0x00 };
					box.PutBytesValue(htons(0x0006), _unknow3Bytes, sizeof(_unknow3Bytes));

					//RegisterFlg
					uint32_t _tag = htonl(0x0000001F);
					box.PutBytesValue(htons(0x0007), (unsigned char*)&_tag, sizeof(uint32_t));

					//qq版本 8.3.0
					//std::string _qqVersion = "8.3.0";
					box.PutBytesValue(htons(0x0012), (unsigned char*)ctx->regctx.qqVersion.data(), ctx->regctx.qqVersion.length());

					//unknow
					unsigned char _unknow2ZeroBytes[2] = { 0x00, 0x00 };
					box.PutBytesValue(htons(0x0025), _unknow2ZeroBytes, sizeof(_unknow2ZeroBytes));

					//protobuf sec_trans.SecTransInfo
					box.PutBytesValue(htons(0x0032), (unsigned char*)protobuf_secinfo.data(), protobuf_secinfo.length());
					box.Serialize();
					tlvdata = string((const char *)box.GetSerializedBuffer(), box.GetSerializedBytes());
					tlvcnt = box.GetTlvBoxCnt();
				}


				//merge tlvdata
				int16_to_buf(tlvcnt, timefrontmsg);
				string_to_buf(tlvdata, timefrontmsg);

				//end sign
				int8_to_buf(0x03, timefrontmsg);


				//填充大小，减去时间戳所占的大小
				fix_lenOfThis = htons(timefrontmsg.length() - sizeof(timestamp));
				fix_buf_data(fix_pos, (const char*)&fix_lenOfThis, sizeof(fix_lenOfThis), timefrontmsg);
			}

			//merge timefrontmsg
			string_to_buf(timefrontmsg, trans_msg);

			//填充大小
			fix_timemsg_bodyLen = htons(timefrontmsg.length());
			fix_buf_data(fix_pos, (const char*)&fix_timemsg_bodyLen, sizeof(fix_timemsg_bodyLen), trans_msg);
		}

		string encrypt_trans_msg = bufutil::tea_encrypt(trans_msg.data(), trans_msg.length(), ctx->regctx.shared_key.data());





		//merge trans_msg
		string_to_buf(encrypt_trans_msg, body_msg);

		//end sign
		int8_to_buf(0x03, body_msg);


		//填充大小
		fix_body_len = htons(body_msg.length());
		fix_buf_data(fix_pos, (const char*)&fix_body_len, sizeof(fix_body_len), body_msg);
	}


	//merge header
	string total_msg;
	int32data_to_buf(header_msg, total_msg, true);
	//merge body	
	int32data_to_buf(body_msg, total_msg, true);


	//加密

	string encrypt_total = bufutil::tea_encrypt(total_msg.data(), total_msg.length(), ctx->regctx.zero_key.data());


	//meger all
	string_to_buf(encrypt_total, msg);

	//填充大小,带上自身大小
	fix_len = htonl(msg.length());
	fix_buf_data(fix_pos, (const char*)&fix_len, sizeof(fix_len), msg);
	return msg;
}

std::string packer::packer_build_RegSubmitMsgChk(qq_ctx* ctx)
{
	string msg;
	uint32_t fix_len = 0;
	int fix_pos = int32_to_buf(fix_len, msg);

	string header_type = { 0x00, 0x00, 0x00, 0x0A, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x05, 0x30 };

	string_to_buf(header_type, msg);

	string header_msg; {

		//seq
		int32_to_buf(ctx->regctx.seq, header_msg);
		//appid
		int32_t appid1 = 0x2002F060;
		int32_t appid2 = 0x2002F060;
		int32_to_buf(appid1, header_msg);
		int32_to_buf(appid2, header_msg);


		//
		string unknow_12bytes = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };
		string_to_buf(unknow_12bytes, header_msg);


		//
		string unknow_empty = "";
		int32data_to_buf(unknow_empty, header_msg, true);

		//cmd
		string cmd = "wtlogin.trans_emp";
		int32data_to_buf(cmd, header_msg, true);

		//msgcookie
		string msgcookie_str = string((const char*)&ctx->regctx.msgcookie, sizeof(ctx->regctx.msgcookie));
		int32data_to_buf(msgcookie_str, header_msg, true);

		//imei
		int32data_to_buf(ctx->regctx.imei, header_msg, true);
		//ksid
		int32data_to_buf(ctx->regctx.ksid, header_msg, true);
		//imsi
		int16data_to_buf(ctx->regctx.qqimsi, header_msg, true);

		//
		string unknow2_empty = "";
		int32data_to_buf(unknow2_empty, header_msg, true);
	}

	string body_msg; {
		//begin sign
		int8_to_buf(0x02, body_msg);
		//len
		int16_t fix_body_len = 0;
		int fix_pos = int16_to_buf(fix_body_len, body_msg);
		//pcVer: 8001(0x1F41)
		int16_t pcVer = 0x1F41;
		int16_to_buf(pcVer, body_msg);
		//cmd: 2066(0x0812)
		int16_t cmd = 0x0812;
		int16_to_buf(cmd, body_msg);
		//sub_cmd: 1(0x0001)
		int16_t sub_cmd = 0x0001;
		int16_to_buf(sub_cmd, body_msg);

		//qqnum: 0(0x00000000) 注册时为0
		int32_t qqnum = 0;
		int32_to_buf(qqnum, body_msg);
		//qqCryptVersionInfo: 03 07 00 00 00 00 02 00 00 00 00 00 00 00 00
		string qqCryptVersionInfo = { 0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		string_to_buf(qqCryptVersionInfo, body_msg);
		//unknow: 257(0x0101)
		int16_t unknow = 0x0101;
		int16_to_buf(unknow, body_msg);

		//unknow rand md5
		string_to_buf(ctx->regctx.unknow_randmd5, body_msg);

		//unknow3: 258(0x0102)
		int16_t unknow3 = 0x0102;
		int16_to_buf(unknow3, body_msg);
		//pubkey
		int16data_to_buf(ctx->regctx.pubkey, body_msg);

		string trans_msg; {
			//isHas_userStSig
			int8_to_buf(0x00, trans_msg);
			//time_wrapbodyLen
			int16_t fix_timemsg_bodyLen = 0;
			int fix_pos = int16_to_buf(fix_timemsg_bodyLen, trans_msg);

			//appid
			int32_t appid = 0;
			int32_to_buf(appid, trans_msg);

			//appid
			int32_t role = 0x0000005f;
			int32_to_buf(role, trans_msg);

			//st_userStSig
			string userStSig = "";
			int16data_to_buf(userStSig, trans_msg, false);

			//rollback_sig
			string rollback_sig = "";
			int8data_to_buf(rollback_sig, trans_msg, false);

			string timefrontmsg; {

				//时间戳，谨记此字段大小不算在fix_lenOfThis里面,但是算在fix_timemsg_bodyLen里面
				uint32_t timestamp = time(NULL);
				int32_to_buf(timestamp, timefrontmsg);

				//begin sign
				int8_to_buf(0x02, timefrontmsg);

				//lenOfThis
				uint16_t fix_lenOfThis = 0;
				int fix_pos = int16_to_buf(fix_lenOfThis, timefrontmsg);

				//uint16_t fixed_2byte_3
				uint16_t fixed_2byte_3 = 0x0003;
				int16_to_buf(fixed_2byte_3, timefrontmsg);

				//reg_cmd 00 0A,检测手机 00 05 提交短信验证码, 00 06 提交昵称和密码
				uint16_t reg_cmd = 0x0005;
				int16_to_buf(reg_cmd, timefrontmsg);

				//fixed_1byte_4
				uint8_t fixed_1byte_4 = 0x04;
				int8_to_buf(fixed_1byte_4, timefrontmsg);
				//uint32_t fixed_4byte_0 = buf_to_int32(base + pos); pos += 4;
				int32_t fixed_4byte_0 = 0;
				int32_to_buf(fixed_4byte_0, timefrontmsg);


				//st_phoneToken
				int8data_to_buf(ctx->regctx.phoneToken, timefrontmsg);
				//encrypt st_phoneToken
				string st_phoneToken_;
				int8data_to_buf(ctx->regctx.phoneToken, st_phoneToken_);
				string encrypt_phoneToken = bufutil::tea_encrypt(st_phoneToken_.data(), st_phoneToken_.length(), ctx->regctx.sendsms_md5key.data());
				int16data_to_buf(encrypt_phoneToken, timefrontmsg);

				//end sign
				int8_to_buf(0x03, timefrontmsg);


				//填充大小，减去时间戳所占的大小
				fix_lenOfThis = htons(timefrontmsg.length() - sizeof(timestamp));
				fix_buf_data(fix_pos, (const char*)&fix_lenOfThis, sizeof(fix_lenOfThis), timefrontmsg);
			}

			//merge timefrontmsg
			string_to_buf(timefrontmsg, trans_msg);

			//填充大小
			fix_timemsg_bodyLen = htons(timefrontmsg.length());
			fix_buf_data(fix_pos, (const char*)&fix_timemsg_bodyLen, sizeof(fix_timemsg_bodyLen), trans_msg);
		}

		string encrypt_trans_msg = bufutil::tea_encrypt(trans_msg.data(), trans_msg.length(), ctx->regctx.shared_key.data());





		//merge trans_msg
		string_to_buf(encrypt_trans_msg, body_msg);

		//end sign
		int8_to_buf(0x03, body_msg);


		//填充大小
		fix_body_len = htons(body_msg.length());
		fix_buf_data(fix_pos, (const char*)&fix_body_len, sizeof(fix_body_len), body_msg);
	}


	//merge header
	string total_msg;
	int32data_to_buf(header_msg, total_msg, true);
	//merge body	
	int32data_to_buf(body_msg, total_msg, true);


	//加密

	string encrypt_total = bufutil::tea_encrypt(total_msg.data(), total_msg.length(), ctx->regctx.zero_key.data());


	//meger all
	string_to_buf(encrypt_total, msg);

	//填充大小,带上自身大小
	fix_len = htonl(msg.length());
	fix_buf_data(fix_pos, (const char*)&fix_len, sizeof(fix_len), msg);
	return msg;
}

std::string packer::packer_build_RegQueryClientSentMsgStatus(qq_ctx* ctx)
{
	string msg;
	uint32_t fix_len = 0;
	int fix_pos = int32_to_buf(fix_len, msg);

	string header_type = { 0x00, 0x00, 0x00, 0x0A, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x05, 0x30 };

	string_to_buf(header_type, msg);

	string header_msg; {

		//seq
		int32_to_buf(ctx->regctx.seq, header_msg);
		//appid
		int32_t appid1 = 0x2002F060;
		int32_t appid2 = 0x2002F060;
		int32_to_buf(appid1, header_msg);
		int32_to_buf(appid2, header_msg);


		//
		string unknow_12bytes = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };
		string_to_buf(unknow_12bytes, header_msg);


		//
		string unknow_empty = "";
		int32data_to_buf(unknow_empty, header_msg, true);

		//cmd
		string cmd = "wtlogin.trans_emp";
		int32data_to_buf(cmd, header_msg, true);

		//msgcookie
		string msgcookie_str = string((const char*)&ctx->regctx.msgcookie, sizeof(ctx->regctx.msgcookie));
		int32data_to_buf(msgcookie_str, header_msg, true);

		//imei
		int32data_to_buf(ctx->regctx.imei, header_msg, true);
		//ksid
		int32data_to_buf(ctx->regctx.ksid, header_msg, true);
		//imsi
		int16data_to_buf(ctx->regctx.qqimsi, header_msg, true);

		//
		string unknow2_empty = "";
		int32data_to_buf(unknow2_empty, header_msg, true);
	}

	string body_msg; {
		//begin sign
		int8_to_buf(0x02, body_msg);
		//len
		int16_t fix_body_len = 0;
		int fix_pos = int16_to_buf(fix_body_len, body_msg);
		//pcVer: 8001(0x1F41)
		int16_t pcVer = 0x1F41;
		int16_to_buf(pcVer, body_msg);
		//cmd: 2066(0x0812)
		int16_t cmd = 0x0812;
		int16_to_buf(cmd, body_msg);
		//sub_cmd: 1(0x0001)
		int16_t sub_cmd = 0x0001;
		int16_to_buf(sub_cmd, body_msg);

		//qqnum: 0(0x00000000) 注册时为0
		int32_t qqnum = 0;
		int32_to_buf(qqnum, body_msg);
		//qqCryptVersionInfo: 03 07 00 00 00 00 02 00 00 00 00 00 00 00 00
		string qqCryptVersionInfo = { 0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		string_to_buf(qqCryptVersionInfo, body_msg);
		//unknow: 257(0x0101)
		int16_t unknow = 0x0101;
		int16_to_buf(unknow, body_msg);

		//unknow rand md5
		string_to_buf(ctx->regctx.unknow_randmd5, body_msg);

		//unknow3: 258(0x0102)
		int16_t unknow3 = 0x0102;
		int16_to_buf(unknow3, body_msg);
		//pubkey
		int16data_to_buf(ctx->regctx.pubkey, body_msg);

		string trans_msg; {
			//isHas_userStSig
			int8_to_buf(0x00, trans_msg);
			//time_wrapbodyLen
			int16_t fix_timemsg_bodyLen = 0;
			int fix_pos = int16_to_buf(fix_timemsg_bodyLen, trans_msg);

			//appid
			int32_t appid = 0;
			int32_to_buf(appid, trans_msg);

			//appid
			int32_t role = 0x0000005f;
			int32_to_buf(role, trans_msg);

			//st_userStSig
			string userStSig = "";
			int16data_to_buf(userStSig, trans_msg, false);

			//rollback_sig
			string rollback_sig = "";
			int8data_to_buf(rollback_sig, trans_msg, false);

			string timefrontmsg; {

				//时间戳，谨记此字段大小不算在fix_lenOfThis里面,但是算在fix_timemsg_bodyLen里面
				uint32_t timestamp = time(NULL);
				int32_to_buf(timestamp, timefrontmsg);

				//begin sign
				int8_to_buf(0x02, timefrontmsg);

				//lenOfThis
				uint16_t fix_lenOfThis = 0;
				int fix_pos = int16_to_buf(fix_lenOfThis, timefrontmsg);

				//uint16_t fixed_2byte_3
				uint16_t fixed_2byte_3 = 0x0003;
				int16_to_buf(fixed_2byte_3, timefrontmsg);

				//reg_cmd 00 0A,检测手机 00 05 提交短信验证码, 00 06 提交昵称和密码, 00 03 是检测发短信状态
				uint16_t reg_cmd = 0x0003;
				int16_to_buf(reg_cmd, timefrontmsg);

				//fixed_1byte_4
				uint8_t fixed_1byte_4 = 0x04;
				int8_to_buf(fixed_1byte_4, timefrontmsg);
				//uint32_t fixed_4byte_0 = buf_to_int32(base + pos); pos += 4;
				int32_t fixed_4byte_0 = 0;
				int32_to_buf(fixed_4byte_0, timefrontmsg);


				//st_phoneToken
				int8data_to_buf(ctx->regctx.phoneToken, timefrontmsg);
				//encrypt st_phoneToken
				string st_phoneToken_;
				int8data_to_buf(ctx->regctx.phoneToken, st_phoneToken_);
				string encrypt_phoneToken = bufutil::tea_encrypt(st_phoneToken_.data(), st_phoneToken_.length(), ctx->regctx.sendsms_md5key.data());
				int16data_to_buf(encrypt_phoneToken, timefrontmsg);

				//end sign
				int8_to_buf(0x03, timefrontmsg);


				//填充大小，减去时间戳所占的大小
				fix_lenOfThis = htons(timefrontmsg.length() - sizeof(timestamp));
				fix_buf_data(fix_pos, (const char*)&fix_lenOfThis, sizeof(fix_lenOfThis), timefrontmsg);
			}

			//merge timefrontmsg
			string_to_buf(timefrontmsg, trans_msg);

			//填充大小
			fix_timemsg_bodyLen = htons(timefrontmsg.length());
			fix_buf_data(fix_pos, (const char*)&fix_timemsg_bodyLen, sizeof(fix_timemsg_bodyLen), trans_msg);
		}
		const char* tmp = trans_msg.data();

		string encrypt_trans_msg = bufutil::tea_encrypt(trans_msg.data(), trans_msg.length(), ctx->regctx.shared_key.data());





		//merge trans_msg
		string_to_buf(encrypt_trans_msg, body_msg);

		//end sign
		int8_to_buf(0x03, body_msg);


		//填充大小
		fix_body_len = htons(body_msg.length());
		fix_buf_data(fix_pos, (const char*)&fix_body_len, sizeof(fix_body_len), body_msg);
	}


	//merge header
	string total_msg;
	int32data_to_buf(header_msg, total_msg, true);
	//merge body	
	int32data_to_buf(body_msg, total_msg, true);


	//加密

	string encrypt_total = bufutil::tea_encrypt(total_msg.data(), total_msg.length(), ctx->regctx.zero_key.data());


	//meger all
	string_to_buf(encrypt_total, msg);

	//填充大小,带上自身大小
	fix_len = htonl(msg.length());
	fix_buf_data(fix_pos, (const char*)&fix_len, sizeof(fix_len), msg);
	return msg;
}

std::string packer::packer_build_RegGetAccount(qq_ctx* ctx)
{
	string msg;
	uint32_t fix_len = 0;
	int fix_pos = int32_to_buf(fix_len, msg);

	string header_type = { 0x00, 0x00, 0x00, 0x0A, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x05, 0x30 };

	string_to_buf(header_type, msg);

	string header_msg; {

		//seq
		int32_to_buf(ctx->regctx.seq, header_msg);
		//appid
		int32_t appid1 = 0x2002F060;
		int32_t appid2 = 0x2002F060;
		int32_to_buf(appid1, header_msg);
		int32_to_buf(appid2, header_msg);


		//
		string unknow_12bytes = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };
		string_to_buf(unknow_12bytes, header_msg);


		//
		string unknow_empty = "";
		int32data_to_buf(unknow_empty, header_msg, true);

		//cmd
		string cmd = "wtlogin.trans_emp";
		int32data_to_buf(cmd, header_msg, true);

		//msgcookie
		string msgcookie_str = string((const char*)&ctx->regctx.msgcookie, sizeof(ctx->regctx.msgcookie));
		int32data_to_buf(msgcookie_str, header_msg, true);

		//imei
		int32data_to_buf(ctx->regctx.imei, header_msg, true);
		//ksid
		int32data_to_buf(ctx->regctx.ksid, header_msg, true);
		//imsi
		int16data_to_buf(ctx->regctx.qqimsi, header_msg, true);

		//
		string unknow2_empty = "";
		int32data_to_buf(unknow2_empty, header_msg, true);
	}

	string body_msg; {
		//begin sign
		int8_to_buf(0x02, body_msg);
		//len
		int16_t fix_body_len = 0;
		int fix_pos = int16_to_buf(fix_body_len, body_msg);
		//pcVer: 8001(0x1F41)
		int16_t pcVer = 0x1F41;
		int16_to_buf(pcVer, body_msg);
		//cmd: 2066(0x0812)
		int16_t cmd = 0x0812;
		int16_to_buf(cmd, body_msg);
		//sub_cmd: 1(0x0001)
		int16_t sub_cmd = 0x0001;
		int16_to_buf(sub_cmd, body_msg);

		//qqnum: 0(0x00000000) 注册时为0
		int32_t qqnum = 0;
		int32_to_buf(qqnum, body_msg);
		//qqCryptVersionInfo: 03 07 00 00 00 00 02 00 00 00 00 00 00 00 00
		string qqCryptVersionInfo = { 0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		string_to_buf(qqCryptVersionInfo, body_msg);
		//unknow: 257(0x0101)
		int16_t unknow = 0x0101;
		int16_to_buf(unknow, body_msg);

		//unknow rand md5
		string_to_buf(ctx->regctx.unknow_randmd5, body_msg);

		//unknow3: 258(0x0102)
		int16_t unknow3 = 0x0102;
		int16_to_buf(unknow3, body_msg);
		//pubkey
		int16data_to_buf(ctx->regctx.pubkey, body_msg);

		string trans_msg; {
			//isHas_userStSig
			int8_to_buf(0x00, trans_msg);
			//time_wrapbodyLen
			int16_t fix_timemsg_bodyLen = 0;
			int fix_pos = int16_to_buf(fix_timemsg_bodyLen, trans_msg);

			//appid
			int32_t appid = 0;
			int32_to_buf(appid, trans_msg);

			//appid
			int32_t role = 0x0000005f;
			int32_to_buf(role, trans_msg);

			//st_userStSig
			string userStSig = "";
			int16data_to_buf(userStSig, trans_msg, false);

			//rollback_sig
			string rollback_sig = "";
			int8data_to_buf(rollback_sig, trans_msg, false);

			string timefrontmsg; {

				//时间戳，谨记此字段大小不算在fix_lenOfThis里面,但是算在fix_timemsg_bodyLen里面
				uint32_t timestamp = time(NULL);
				int32_to_buf(timestamp, timefrontmsg);

				//begin sign
				int8_to_buf(0x02, timefrontmsg);

				//lenOfThis
				uint16_t fix_lenOfThis = 0;
				int fix_pos = int16_to_buf(fix_lenOfThis, timefrontmsg);

				//uint16_t fixed_2byte_3
				uint16_t fixed_2byte_3 = 0x0003;
				int16_to_buf(fixed_2byte_3, timefrontmsg);

				//reg_cmd 00 0A,检测手机 00 05 提交短信验证码, 00 06 提交昵称和密码
				uint16_t reg_cmd = 0x0006;
				int16_to_buf(reg_cmd, timefrontmsg);

				//fixed_1byte_4
				uint8_t fixed_1byte_4 = 0x04;
				int8_to_buf(fixed_1byte_4, timefrontmsg);
				//uint32_t fixed_4byte_0 = buf_to_int32(base + pos); pos += 4;
				int32_t fixed_4byte_0 = 0;
				int32_to_buf(fixed_4byte_0, timefrontmsg);
				//st_phoneToken
				int8data_to_buf(ctx->regctx.phoneToken, timefrontmsg);

				string embed_body; {

					//st_phoneToken
					int8data_to_buf(ctx->regctx.phoneToken, embed_body);
					//st_qqpassword
					int8data_to_buf(ctx->regctx.password, embed_body);

					//!To_register_type = 0x5 0x0，0x1
					int8_t not_To_register_type = 0x5;
					int8_to_buf(not_To_register_type, embed_body);
					//tlv data
					uint16_t tlvcnt = 0;
					string tlvdata; {
						tlv::TlvBox box;


						//ksid
						box.PutBytesValue(htons(0x0001), (unsigned char*)NULL, 0);

						//qqpassport
						box.PutBytesValue(htons(0x0005), (unsigned char*)"qqpassport", strlen("qqpassport"));
						//UUID
						box.PutBytesValue(htons(0x0006), (unsigned char*)ctx->regctx.nickName.data(), ctx->regctx.nickName.length());


						//fixed_1byte
						uint8_t fixed_1byte = 0x1;
						box.PutBytesValue(htons(0x0008), (unsigned char*)&fixed_1byte, sizeof(fixed_1byte));


						//fixed_4byte
						uint32_t fixed_4byte = htonl(0x00000001);
						box.PutBytesValue(htons(0x000F), (unsigned char*)&fixed_4byte, sizeof(fixed_4byte));

						//unknow
						unsigned char _unknow2ZeroBytes[2] = { 0x00, 0x00 };
						box.PutBytesValue(htons(0x0025), _unknow2ZeroBytes, sizeof(_unknow2ZeroBytes));

						//UUID
						box.PutBytesValue(htons(0x000A), (unsigned char*)ctx->regctx.guid.data(), ctx->regctx.guid.length());


						uint32_t appid = htonl(0x00000000);
						box.PutBytesValue(htons(0x000D), (unsigned char*)&appid, sizeof(uint32_t));


						//apkPackageName
						box.PutBytesValue(htons(0x000E), (unsigned char*)ctx->regctx.apkPackageName.data(), ctx->regctx.apkPackageName.length());


						//qqVersion
						box.PutBytesValue(htons(0x0012), (unsigned char*)ctx->regctx.qqVersion.data(), ctx->regctx.qqVersion.length());

						box.Serialize();
						tlvdata = string((const char*)box.GetSerializedBuffer(), box.GetSerializedBytes());
						tlvcnt = box.GetTlvBoxCnt();
					}


					//merge tlvdata
					int16_to_buf(tlvcnt, embed_body);
					string_to_buf(tlvdata, embed_body);
				}
				string encrypt_embed_body = bufutil::tea_encrypt(embed_body.data(), embed_body.length(), ctx->regctx.sendsms_md5key.data());
				//add encrypt_embed_body
				int16data_to_buf(encrypt_embed_body, timefrontmsg);

				//end sign
				int8_to_buf(0x03, timefrontmsg);


				//填充大小，减去时间戳所占的大小
				fix_lenOfThis = htons(timefrontmsg.length() - sizeof(timestamp));
				fix_buf_data(fix_pos, (const char*)&fix_lenOfThis, sizeof(fix_lenOfThis), timefrontmsg);
			}

			//merge timefrontmsg
			string_to_buf(timefrontmsg, trans_msg);

			//填充大小
			fix_timemsg_bodyLen = htons(timefrontmsg.length());
			fix_buf_data(fix_pos, (const char*)&fix_timemsg_bodyLen, sizeof(fix_timemsg_bodyLen), trans_msg);
		}

		string encrypt_trans_msg = bufutil::tea_encrypt(trans_msg.data(), trans_msg.length(), ctx->regctx.shared_key.data());





		//merge trans_msg
		string_to_buf(encrypt_trans_msg, body_msg);

		//end sign
		int8_to_buf(0x03, body_msg);


		//填充大小
		fix_body_len = htons(body_msg.length());
		fix_buf_data(fix_pos, (const char*)&fix_body_len, sizeof(fix_body_len), body_msg);
	}


	//merge header
	string total_msg;
	int32data_to_buf(header_msg, total_msg, true);
	//merge body	
	int32data_to_buf(body_msg, total_msg, true);


	//加密

	string encrypt_total = bufutil::tea_encrypt(total_msg.data(), total_msg.length(), ctx->regctx.zero_key.data());


	//meger all
	string_to_buf(encrypt_total, msg);

	//填充大小,带上自身大小
	fix_len = htonl(msg.length());
	fix_buf_data(fix_pos, (const char*)&fix_len, sizeof(fix_len), msg);
	return msg;
}


std::string packer::packer_build_wtlogin_login(qq_ctx* ctx)
{
	UNIMPL_FUNCTION
}

//交换安全中心密钥
std::string packer::packer_build_wtlogin_login_exchange_loginauth(qq_ctx* ctx) {
	UNIMPL_FUNCTION
}

std::string packer::packer_build_sec_exchange_A2(qq_ctx* ctx) {
	UNIMPL_FUNCTION
}

std::string packer::packer_build_wtlogin_login_verify_captcha(qq_ctx* ctx) {
	UNIMPL_FUNCTION
}

std::string packer::packer_build_wtlogin_login_verify_captcha_quick(qq_ctx* ctx) {
	UNIMPL_FUNCTION
}

std::string packer::packer_build_ConfigService_ClientReq(qq_ctx* ctx)
{
	UNIMPL_FUNCTION
}