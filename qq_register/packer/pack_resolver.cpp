#include "pack_resolver.h"
#include "../../md5/md5.h"
#include "../../tlv/tlv.h"
#include "../misc/tlvtype/tlv_t146.h"
#include "../misc/tlvtype/tlv_t192.h"
#include "../misc/tlvtype/tlv_t104.h"
#include "../misc/tlvtype/tlv_t105.h"
using namespace tlv;

int resolver::resolve_register_body(qq_ctx* ctx, string& body) {
	const char* base = body.data();
	int pos = 0;
	int rc = 0;
	int result = STATUS_FAILED;

	uint32_t bodylen = buf_to_int32(base + pos); pos += 4;
	int8_t unknow_1byte = buf_to_int8(base + pos); pos += 1;
	int copy_pos = pos;
	int8_t begin_sign = buf_to_int8(base + pos); pos += 1;
	int16_t wrap_by0203_len = buf_to_int16(base + pos); pos += 2;
	int16_t maybe_major_cmd = buf_to_int16(base + pos); pos += 2;
	int16_t subcmd = buf_to_int16(base + pos); pos += 2;

	int8_t unknow_value = buf_to_int8(base + pos);
	pos = copy_pos + unknow_value + 8;
	/*
		int v0 = util.buf_to_int8(arg6, 7);
		return v0 + 8 <= arg6.length ? new int[]{0, v0 + 8} : new int[]{-1009, 8};
		*/
	if (wrap_by0203_len >= unknow_value) {
		switch (subcmd)
		{
		//检测手机号码
		case 0xA: {
			//cmd ? retValue
			if (pos > wrap_by0203_len) return -1;
			int16_t d = buf_to_int16(base + pos); pos += 2;

			if (pos > wrap_by0203_len) return -1;
			int16_t token_pos = buf_to_int16(base + pos); pos += 2;



			if (pos > wrap_by0203_len) return -1;
			std::string _extra_info = buf_to_string(base + pos, token_pos); pos += token_pos;


	
			if (pos > wrap_by0203_len) return -1;
			int8_t token_len = buf_to_int8(base + pos); pos += 1;

			if (pos > wrap_by0203_len) return -1;
			std::string _token = buf_to_string(base + pos, token_len); pos += token_len;

			int16_t msg_len = buf_to_int16(base + pos); pos += 2;
			if (pos > wrap_by0203_len) return -1;
			std::string _msg =  buf_to_string(base + pos, msg_len); pos += msg_len;
			_msg = UTF8ToGB(_msg.c_str());


			switch (d)
			{
				//接受短信
			case 0: {
				result = STATUS_RECV_MSG;
				break;
			}
				  //发短信
			case 2: {
				const char* extra_base = _extra_info.data();
				int extra_pos = 0;
				int extra_rc = 0;
				int8_struct* st_recvphone = NULL;
				int8_struct* st_sendmsg = NULL;
				int16_struct* st_tips = NULL;
				extra_rc = buf_to_8struct(extra_base + extra_pos, &st_recvphone); extra_pos += extra_rc;
				extra_rc = buf_to_8struct(extra_base + extra_pos, &st_sendmsg); extra_pos += extra_rc;
				extra_rc = buf_to_16struct(extra_base + extra_pos, &st_tips); extra_pos += extra_rc;
				ctx->regctx.recv_phoneNumber = string(st_recvphone->data, st_recvphone->len);
				ctx->regctx.sendsms = string(st_sendmsg->data, st_sendmsg->len);
				//计算KEY
				ctx->regctx.sendsms_md5key = getmd5bytes(ctx->regctx.sendsms);

				if (st_tips) delete st_tips;
				if (st_sendmsg) delete st_sendmsg;
				if (st_recvphone) delete st_recvphone;
				result = STATUS_SEND_MSG;

				break;
			}
			case 0x33: {
				_msg.append("(可能是需要好友辅助注册)");
				break;
			}
			}


			printf("msg: %s\n", _msg.c_str());
			if (_msg.find("请输入短信验证码") != std::string::npos ||
				_msg.find("请发送短信") != std::string::npos) {
				ctx->regctx.phoneToken = _token;
			}
			break;
		}
		//提交短信后
		case 0x5: {
			//cmd ? retValue
			if (pos > wrap_by0203_len) return -1;
			int16_t d = buf_to_int16(base + pos); pos += 2;

			if (pos > wrap_by0203_len) return -1;
			int8_t token_len = buf_to_int8(base + pos); pos += 1;

			if (pos > wrap_by0203_len) return -1;
			std::string _token = buf_to_string(base + pos, token_len); pos += token_len;

			int16_t msg_len = buf_to_int16(base + pos); pos += 2;
			if (pos > wrap_by0203_len) return -1;

			std::string _msg = buf_to_string(base + pos, msg_len); pos += msg_len;
			_msg = UTF8ToGB(_msg.c_str());
			
			if (pos + 1 < msg_len) {
				int16_t tlv_cnt = buf_to_int16(base + pos); pos += 2;

				if (tlv_cnt != 0) {
					//pos += 2; tlv.Parse这个函数里面会跳过
					std::string tlvdata = std::string((base + pos), wrap_by0203_len - ((base + pos) - base) - 1);
					tlv::TlvBox tlv;

					tlv.Parse((const unsigned char*)tlvdata.data(), tlvdata.length());
					vector<tlv::Tlv*> qqStr;
					tlv.GetBytesValue(0x0024, qqStr);
					vector<tlv::Tlv*> nickName;
					tlv.GetBytesValue(0x0006, nickName);
				}
			}
			printf("msg: %s\n", _msg.c_str());
			if (_msg.find("请输入短信验证码") != std::string::npos) {
				ctx->regctx.phoneToken = _token;
				result = 0;
			}
			break;
		}
		//提交密码昵称后
		case 0x6: {
			if (pos > wrap_by0203_len) return -1;
			//cmd ? retValue
			int16_t d = buf_to_int16(base + pos); pos += 2;



			if (pos > wrap_by0203_len) return -1;
			int16_t crypted_data_len = buf_to_int16(base + pos); pos += 2;

			if (pos > wrap_by0203_len) return -1;
			std::string crypted_data = buf_to_string(base + pos, crypted_data_len); pos += crypted_data_len;

			if (crypted_data.length() > 0) {
				string decrypted_data;
				if (ctx->regctx.isSendMsg == true) {
					decrypted_data = bufutil::tea_decrypt(crypted_data.data(), crypted_data.length(), ctx->regctx.sendsms_md5key.data());
				}
				else {
					decrypted_data = bufutil::tea_decrypt(crypted_data.data(), crypted_data.length(), ctx->regctx.smscode_md5key.data());
				}
				if (decrypted_data.length() > 0) {
					int _emd_pos = 0;
					int decode_len = decrypted_data.length();
					const char* _emd_base = decrypted_data.data();
					if (_emd_pos > decode_len) return -1;

					int8_t _emd_token_len = *((int8_t*)(_emd_base + _emd_pos));
					_emd_pos = _emd_token_len;

					if (_emd_pos + 8 > decode_len) return -1;

					_emd_pos++;

					//"resp_register_uin"
					uint64_t qqnumber = buf_to_int64(_emd_base + _emd_pos); _emd_pos += 8;
					ctx->regctx.qqid = qqnumber;
				}

			}

			if (pos > wrap_by0203_len) return -1;
			int8_t token_len = buf_to_int8(base + pos); pos += 1;


			if (pos > wrap_by0203_len) return -1;
			std::string _token = buf_to_string(base + pos, token_len); pos += token_len;


			//"resp_register_promptinfo"
			int16_t msg_len = buf_to_int16(base + pos); pos += 2;
			if (pos > wrap_by0203_len) return -1;
			std::string _msg = buf_to_string(base + pos, msg_len); pos += msg_len;
			_msg = UTF8ToGB(_msg.c_str());
			printf("msg: %s\n", _msg.c_str());

			if (_msg.find("请输入短信验证码") != std::string::npos) {
				ctx->regctx.phoneToken = _token;
				result = STATUS_RECV_MSG;
			}
			break;
		}
		//发送短信后返回
		case 0x03: {
			//cmd ? retValue
			if (pos > wrap_by0203_len) return -1;
			int16_t d = buf_to_int16(base + pos); pos += 2;

			if (pos > wrap_by0203_len) return -1;
			int16_t token_pos = buf_to_int16(base + pos); pos += 2;

			if (pos > wrap_by0203_len) return -1;
			std::string _extra_info = buf_to_string(base + pos, token_pos); pos += token_pos;

			if (pos > wrap_by0203_len) return -1;
			int8_t token_len = buf_to_int8(base + pos); pos += 1;

			if (pos > wrap_by0203_len) return -1;
			std::string _token = buf_to_string(base + pos, token_len); pos += token_len;

			int16_t msg_len = buf_to_int16(base + pos); pos += 2;
			if (pos > wrap_by0203_len) return -1;
			std::string _msg = buf_to_string(base + pos, msg_len); pos += msg_len;
			_msg = UTF8ToGB(_msg.c_str());

			printf("msg: %s\n", _msg.c_str());
			if (_msg.find("请输入短信验证码") != std::string::npos ||
				_msg.find("请发送短信") != std::string::npos) {
				ctx->regctx.phoneToken = _token;
				result = STATUS_RECV_MSG;
			}
			switch (d)
			{
			case 0x00: {
				result = STATUS_RECV_MSG;
			}
				break;
			case 0x04: {
				break; 
			}
			}
			break;
		}
		default:
			break;
		}
	}

	return result;
}

int resolver::resolve_0530_body(qq_ctx* ctx, string& body){
	const char* base = body.data();
	int pos = 0;
	int rc = 0;
	int result = STATUS_FAILED;

	//header
	uint32_t headlen = buf_to_int32(base + pos); pos += 4;
	uint32_t seq = buf_to_int32(base + pos); pos += 4;
	uint32_t unknow = buf_to_int32(base + pos); pos += 4;
	uint32_t unknow2 = buf_to_int32(base + pos); pos += 4;

	int32_struct* st_cmd = NULL;
	rc = buf_to_32struct(base + pos, &st_cmd, true); pos += rc;

	string cmdstr = string(st_cmd->data, st_cmd->len);
	if (cmdstr == "ConfigService.ClientReq") {
		int32_struct* st_msgcookie = NULL;
		rc = buf_to_32struct(base + pos, &st_msgcookie, true); pos += rc;
		ctx->msgcookie = buf_to_int32(st_msgcookie->data);
		return 0;
	}

	int32_struct* st_msgcookie = NULL;
	rc = buf_to_32struct(base + pos, &st_msgcookie, true); pos += rc;


	int32_struct* st_unknow = NULL;
	rc = buf_to_32struct(base + pos, &st_unknow, false); pos += rc;

	//body

	uint32_t bodylen = buf_to_int32(base + pos); pos += 4;
	int8_t begin_sign = buf_to_int8(base + pos); pos += 1;
	int16_t fixed_2byte = buf_to_int16(base + pos); pos += 2;
	int16_t pcVer = buf_to_int16(base + pos); pos += 2;
	int16_t cmd = buf_to_int16(base + pos); pos += 2;
	int16_t unknow_2byte = buf_to_int16(base + pos); pos += 2;
	uint32_t may_qqnum = buf_to_int32(base + pos); pos += 4;
	int16_t unknow_2byte_2 = buf_to_int16(base + pos); pos += 2;
	int8_t ret_code = buf_to_int8(base + pos); pos += 1;
	if (ret_code == 0) {
		uint32_t ensign_len = 1;
		int crypted_len = body.length() - pos - ensign_len;
		string crypted_data = string(base + pos, crypted_len);
		string decrypted_data = bufutil::tea_decrypt(crypted_data.data(), crypted_data.length(), ctx->regctx.shared_key.data());
		if (decrypted_data.length() > 0) {
			result = resolve_register_body(ctx, decrypted_data);
		}
	}

	if (st_unknow) delete st_unknow;
	if (st_msgcookie) delete st_msgcookie;
	if (st_cmd) delete st_cmd;
	return result;
}

void resolver::resolve_tlv119(qq_ctx* ctx, const std::string& data) {
	int pos = 0;
	const char* base = data.data();
	int16_t tlv_cnt = buf_to_int16(base + pos); pos += 2;

	int tlv_datalen = data.length() - pos;
	tlv::TlvBox tlvparser;
	tlvparser.Parse((const unsigned char*)(base + pos), tlv_datalen);
	int itemcount = tlvparser.GetTlvBoxCnt();
	vector<pair<short int, Tlv*>> all = tlvparser.GetAll();

	for (int i = 0; i < all.size(); i++) {
		pair<short int, Tlv*> pItem = all[i];
		Tlv* pTlv = pItem.second;
		std::vector<Tlv*> values;
		tlvparser.GetBytesValue(pTlv->GetType(), values);
		std::string value_data = std::string((const char*)values[0]->GetValue(), values[0]->GetLength());

		std::string Tagindex = std::to_string(pTlv->GetType()) + "(0x" + to_hex_stream((int16_t)pTlv->GetType()) + ")";
		std::string Length = std::to_string(pTlv->GetLength()) + "(0x" + to_hex_stream((int16_t)pTlv->GetLength()) + ")";
		std::string Value = value_data.length() > 0 ? spacing_string(string_to_hex(value_data)) : "";

		std::string extra;



		int16_t tlvtype_cmd = pTlv->GetType();
		switch (tlvtype_cmd)
		{
		case 0x169: {
			string tlv169 = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			resolve_tlv169(ctx, tlv169);
			break;
		}
		case 0x16A: {
			ctx->tlv16A = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			break;
		}
		case 0x10C: {
			ctx->tlv10C = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			break;
		}
		case 0x106: {
			ctx->tlv106 = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			break;
		}
		}

	}
}
void resolver::resolve_token_tlv119(qq_ctx* ctx, const std::string& data) {
	int pos = 0;
	const char* base = data.data();
	int16_t tlv_cnt = buf_to_int16(base + pos); pos += 2;

	int tlv_datalen = data.length() - pos;
	tlv::TlvBox tlvparser;
	tlvparser.Parse((const unsigned char*)(base + pos), tlv_datalen);
	int itemcount = tlvparser.GetTlvBoxCnt();
	vector<pair<short int, Tlv*>> all = tlvparser.GetAll();

	for (int i = 0; i < all.size(); i++) {
		pair<short int, Tlv*> pItem = all[i];
		Tlv* pTlv = pItem.second;
		std::vector<Tlv*> values;
		tlvparser.GetBytesValue(pTlv->GetType(), values);

		int16_t tlvtype_cmd = pTlv->GetType();
		switch (tlvtype_cmd)
		{
		case 0x10A: {
			ctx->tokenctx.tlv10A_a2key = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			break;
		}
		}

	}
}


void resolver::resolve_tlv169(qq_ctx* ctx, const std::string& data) {
	int pos = 0;
	const char* base = data.data();
	int16_t tlv_cnt = buf_to_int16(base + pos); pos += 2;

	int tlv_datalen = data.length() - pos;
	tlv::TlvBox tlvparser;
	tlvparser.Parse((const unsigned char*)(base + pos), tlv_datalen);
	int itemcount = tlvparser.GetTlvBoxCnt();
	vector<pair<short int, Tlv*>> all = tlvparser.GetAll();

	for (int i = 0; i < all.size(); i++) {
		pair<short int, Tlv*> pItem = all[i];
		Tlv* pTlv = pItem.second;
		std::vector<Tlv*> values;
		tlvparser.GetBytesValue(pTlv->GetType(), values);
		std::string value_data = std::string((const char*)values[0]->GetValue(), values[0]->GetLength());

		std::string Tagindex = std::to_string(pTlv->GetType()) + "(0x" + to_hex_stream((int16_t)pTlv->GetType()) + ")";
		std::string Length = std::to_string(pTlv->GetLength()) + "(0x" + to_hex_stream((int16_t)pTlv->GetLength()) + ")";
		std::string Value = value_data.length() > 0 ? spacing_string(string_to_hex(value_data)) : "";

		std::string extra;



		int16_t tlvtype_cmd = pTlv->GetType();
		switch (tlvtype_cmd)
		{
		case 0x16A: {
			ctx->tokenctx.tlv16A = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			break;
		}
		case 0x10C: {
			ctx->tokenctx.tlv10C = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			break;
		}
		case 0x106: {
			ctx->tokenctx.tlv106 = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			break;
		}
		}

	}
}


void resolver::resolve_respone_tlv_data(qq_ctx* ctx, const std::string& data, bool isHaveCMD) {
	int pos = 0;
	const char* base = data.data();
	int16_t tlv_cmd = 0;
	if (isHaveCMD) {
		tlv_cmd = buf_to_int16(base + pos); pos += 2;
	}
	int8_t unknow = buf_to_int8(base + pos); pos += 1;
	int16_t unknow_type = buf_to_int16(base + pos); pos += 2;

	int tlv_datalen = data.length() - pos;
	tlv::TlvBox tlvparser;
	tlvparser.Parse((const unsigned char*)(base + pos), tlv_datalen);
	int itemcount = tlvparser.GetTlvBoxCnt();
	vector<pair<short int, Tlv*>> all = tlvparser.GetAll();

	for (int i = 0; i < all.size(); i++) {
		pair<short int, Tlv*> pItem = all[i];
		Tlv* pTlv = pItem.second;
		std::vector<Tlv*> values;
		tlvparser.GetBytesValue(pTlv->GetType(), values);
		std::string value_data = std::string((const char*)values[0]->GetValue(), values[0]->GetLength());

		std::string Tagindex = std::to_string(pTlv->GetType()) + "(0x" + to_hex_stream((int16_t)pTlv->GetType()) + ")";
		std::string Length = std::to_string(pTlv->GetLength()) + "(0x" + to_hex_stream((int16_t)pTlv->GetLength()) + ")";
		std::string Value = value_data.length() > 0 ? spacing_string(string_to_hex(value_data)) : "";

		std::string extra;

		if (pTlv->GetType() == 0x0145) {
			extra = "Guid";
		}

		if (pTlv->GetType() == 0x0154) {
			extra = "Message seq(同消息头)";
		}
		if (pTlv->GetType() == 0x0008) {
			extra = "固定的";
		}
		if (pTlv->GetType() == 0x0511) {
			extra = "需要取的pskey域名";
		}
		if (pTlv->GetType() == 0x0187) {
			extra = "mac_addr md5";
		}
		if (pTlv->GetType() == 0x0188) {
			extra = "android_id_md5";
		}if (pTlv->GetType() == 0x0545) {
			//android_id md5
			extra = "android_id md5";
		}
		if (pTlv->GetType() == 0x0191) {
			extra = "SetCanWebVerify(0x82/0)";
		}if (pTlv->GetType() == 0x0177) {
			extra = "new tlv_t177().get_tlv_177(0x5E53F202L, \"6.0.0.2423\");";
		}if (pTlv->GetType() == 0x0516) {
			extra = "_source_type";
		}if (pTlv->GetType() == 0x0521) {
			extra = "ifQQLoginInQim(yes=13L,no=0),后面两个字节固定0";
		}
		if (pTlv->GetType() == 0x0525) {
			extra = "里面是一个TLV 0536(LoginExtraData)";
		}if (pTlv->GetType() == 0x0536) {
			extra = "LoginExtraData";
		}
		if (pTlv->GetType() == 0x0544) {
			extra = "加密算法在so层，把传入的参数经过一通运算得到这里";
		}if (pTlv->GetType() == 0x0108) {
			extra = "ksid";
		}if (pTlv->GetType() == 0x0142) {
			extra = "apk_id";
		}if (pTlv->GetType() == 0x0146) {
			extra = "errorinfo";
		}
		if (pTlv->GetType() == 0x0001) {
			extra = "RegTLV(1),ksid";
		}
		if (pTlv->GetType() == 0x0002) {
			extra = "RegTLV(2),Long";
		}
		if (pTlv->GetType() == 0x0003) {
			extra = "RegTLV(3),_sig";
		}
		if (pTlv->GetType() == 0x0004) {
			extra = "RegTLV(4),GetGuid/reg_uuid";
		}
		if (pTlv->GetType() == 0x0005) {
			extra = "RegTLV(5),qqpassport";
		}
		if (pTlv->GetType() == 0x0006) {
			extra = "RegTLV(6),To_register_captcha_sig/nickName";
		}
		if (pTlv->GetType() == 0x0007) {
			extra = "RegTLV(7),RegisterFlg";
		}
		if (pTlv->GetType() == 0x000A) {
			extra = "RegTLV(10),reg_uuid";
		}
		if (pTlv->GetType() == 0x000D) {
			extra = "RegTLV(13),appid";
		}
		if (pTlv->GetType() == 0x000E) {
			extra = "RegTLV(14),apkPackageName";
		}
		if (pTlv->GetType() == 0x0012) {
			extra = "RegTLV(18),to_register_cr_appVersion";
		}
		if (pTlv->GetType() == 0x0025) {
			extra = "RegTLV(37),unknow, int616";
		}
		if (pTlv->GetType() == 0x0032) {
			extra = "RegTLV(50),SecTransInfo(protobuf)";
		}if (pTlv->GetType() == 0x0119) {
			extra = "用tgtgt key解密";
		}

		int16_t tlvtype_cmd = pTlv->GetType();
		switch (tlvtype_cmd)
		{
		case 0x146: {
			string tlvbuf = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			tlv_t146 t146(pTlv->GetType(), pTlv->GetLength(), tlvbuf);
			string title = UTF8ToGB(t146.get_title().c_str());
			string msg = UTF8ToGB(t146.get_msg().c_str());
			printf("//title:%s, msg: %s\n", title.c_str(), msg.c_str());
			break;
		}
		case 0x192: {
			string tlvbuf = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			tlv_t192 t192(pTlv->GetType(), pTlv->GetLength(), tlvbuf);
			string url = t192.get_url();
			ctx->cptctx.url = url;
			printf("//url: %s\n", url.c_str());
			break;
		}
		case 0x105: {
			string tlvbuf = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			tlv_t105 t105(pTlv->GetType(), pTlv->GetLength(), tlvbuf);
			string _sign = t105.get_sign();
			string _jpgdata = t105.get_pic_jpg();
			break;
		}
		case 0x104: {
			string tlvbuf = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			tlv_t104 t104(pTlv->GetType(), pTlv->GetLength(), tlvbuf);
			string captcha_sig = t104.get_captcha_sig();
			ctx->cptctx.captcha_sig = captcha_sig;
			printf("//captcha_sig: %s\n", captcha_sig.c_str());
			break;
		}
		case 0x402: {
			string tlvbuf = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			ctx->cptctx.tlv402 = tlvbuf;
			break;
		}
		case 0x403: {
			string tlvbuf = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			ctx->cptctx.tlv403 = tlvbuf;
			break;
		}
		case 0x119: {
			string tlvbuf = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			string _tgtgt_key = tlv_cmd == 0x000D ?  ctx->tokenctx.tgtgt_key : ctx->tgtgt_key;
			string decrypted_tlvdata = bufutil::tea_decrypt(tlvbuf.data(), tlvbuf.length(), _tgtgt_key.data());
			if (decrypted_tlvdata.length() > 0) {
				resolve_tlv119(ctx, decrypted_tlvdata);
			}
			break;
		}
		}
		
	}
}

void resolver::resolve_respone_token_tlv_data(qq_ctx* ctx, const std::string& data, bool isHaveCMD) {
	int pos = 0;
	const char* base = data.data();
	int16_t tlv_cmd = 0;
	if (isHaveCMD) {
		tlv_cmd = buf_to_int16(base + pos); pos += 2;
	}
	int8_t unknow = buf_to_int8(base + pos); pos += 1;
	int16_t unknow_type = buf_to_int16(base + pos); pos += 2;

	int tlv_datalen = data.length() - pos;
	tlv::TlvBox tlvparser;
	tlvparser.Parse((const unsigned char*)(base + pos), tlv_datalen);
	int itemcount = tlvparser.GetTlvBoxCnt();
	vector<pair<short int, Tlv*>> all = tlvparser.GetAll();

	for (int i = 0; i < all.size(); i++) {
		pair<short int, Tlv*> pItem = all[i];
		Tlv* pTlv = pItem.second;
		std::vector<Tlv*> values;
		tlvparser.GetBytesValue(pTlv->GetType(), values);
		
		int16_t tlvtype_cmd = pTlv->GetType();
		switch (tlvtype_cmd)
		{
		case 0x119: {
			string tlvbuf = string((const char*)pTlv->GetValue(), pTlv->GetLength());
			string decrypted_tlvdata = bufutil::tea_decrypt(tlvbuf.data(), tlvbuf.length(), ctx->tokenctx.tlv10C.data());
			if (decrypted_tlvdata.length() > 0) {
				resolve_token_tlv119(ctx, decrypted_tlvdata);
			}
			break;
		}
		}

	}
}


int resolver::resolve_respone_embedd_body(qq_ctx* ctx, string& body) {
	const char* base = body.data();
	int pos = 0;
	int rc = 0;
	int result = STATUS_FAILED;

	int8_t begin_sign = buf_to_int8(base + pos); pos += 1;
	int16_t thisLen = buf_to_int16(base + pos); pos += 2;
	int16_t pcVer = buf_to_int16(base + pos); pos += 2;
	int16_t cmd = buf_to_int16(base + pos); pos += 2;
	int16_t subcmd = buf_to_int16(base + pos); pos += 2;
	uint32_t qqnum = buf_to_int32(base + pos); pos += 4;
	int16_t rsp_flag = buf_to_int16(base + pos); pos += 2;
	int8_t ret_code = buf_to_int8(base + pos); pos += 1;
	ctx->login_retcode = ret_code;

	printf("//rsp_flag:%d\n", rsp_flag);
	printf("//ret_code:%d\n", ret_code);

	uint32_t ensign_len = 1;
	int crypted_len = body.length() - pos - ensign_len;
	string crypted_data = string(base + pos, crypted_len);


	string decrypted_data = bufutil::tea_decrypt(crypted_data.data(), crypted_data.length(), ctx->tokenctx.shared_key.data());
	if (decrypted_data.length() > 0) {
		if (rsp_flag == 4) {
			int16_struct* pubKey = NULL;
			rc = buf_to_16struct(decrypted_data.data(), &pubKey, false);
			crypted_data = string(decrypted_data.data() + rc, decrypted_data.length() - rc);

			//再次解密
			std::string strpubkey = bufutil::string_to_hex(string(pubKey->data, pubKey->len));
			std::string webkey = webecdh::calShareKeyMd5ByPeerPublicKey(strpubkey, string_to_hex(ctx->tokenctx.private_key));
			webkey = hex_to_string(webkey);

			decrypted_data = bufutil::tea_decrypt(crypted_data.data(), crypted_data.length(), webkey.data());
			if (pubKey) delete pubKey;
		}
	}



	switch (ret_code)
	{
	case 0: {
		printf("//登录成功");
		break;
	}
	case 1: {
		//密码错误
		printf("//密码错误");
		break;
	}
	case 2: {
		printf("//需要验证码");
		break;
	}
	case 6: {
		
		break;
	}
	case 9:
	case 160: {
		break;
	}
	case -52: {
		//直接免验证码登录
		break;
	}
	default:
		printf("unknow ret_code: %d", ret_code);
	}

	if (decrypted_data.length() > 0) {
		resolve_respone_tlv_data(ctx, decrypted_data, true);
	}
	return result;
}

int resolver::resolve_respone_embedd_tokenbody(qq_ctx* ctx, string& body) {
	const char* base = body.data();
	int pos = 0;
	int rc = 0;
	int result = STATUS_FAILED;

	int8_t begin_sign = buf_to_int8(base + pos); pos += 1;
	int16_t thisLen = buf_to_int16(base + pos); pos += 2;
	int16_t pcVer = buf_to_int16(base + pos); pos += 2;
	int16_t cmd = buf_to_int16(base + pos); pos += 2;
	int16_t subcmd = buf_to_int16(base + pos); pos += 2;
	uint32_t qqnum = buf_to_int32(base + pos); pos += 4;
	int16_t rsp_flag = buf_to_int16(base + pos); pos += 2;
	int8_t ret_code = buf_to_int8(base + pos); pos += 1;
	ctx->login_retcode = ret_code;

	printf("//rsp_flag:%d\n", rsp_flag);
	printf("//ret_code:%d\n", ret_code);


	uint32_t ensign_len = 1;
	int crypted_len = body.length() - pos - ensign_len;
	string crypted_data = string(base + pos, crypted_len);


	string decrypted_data = bufutil::tea_decrypt(crypted_data.data(), crypted_data.length(), ctx->tokenctx.shared_key.data());
	if (decrypted_data.length() > 0) {
		if (rsp_flag == 4) {
			int16_struct* pubKey = NULL;
			rc = buf_to_16struct(decrypted_data.data(), &pubKey, false);
			crypted_data = string(decrypted_data.data() + rc, decrypted_data.length() - rc);

			//再次解密
			std::string strpubkey = bufutil::string_to_hex(string(pubKey->data, pubKey->len));
			std::string webkey = webecdh::calShareKeyMd5ByPeerPublicKey(strpubkey, string_to_hex(ctx->tokenctx.private_key));
			webkey = hex_to_string(webkey);

			decrypted_data = bufutil::tea_decrypt(crypted_data.data(), crypted_data.length(), webkey.data());
			if (pubKey) delete pubKey;
		}
	}


	switch (ret_code)
	{
	case 0: {
		printf("登录成功");
		break;
	}
	case 1: {
		//密码错误
		printf("密码错误");
		break;
	}
	case 2: {
		break;
	}
	case 6: {

		break;
	}
	case 9:
	case 160: {
		break;
	}
	default:
		printf("unknow ret_code: %d", ret_code);
	}

	if (decrypted_data.length() > 0) {
		resolve_respone_token_tlv_data(ctx, decrypted_data, true);
	}
	return result;
}


int resolver::resolve_respone_body(qq_ctx* ctx, string& body) {
	const char* base = body.data();
	int pos = 0;
	int rc = 0;
	int result = STATUS_FAILED;

	//header
	uint32_t headlen = buf_to_int32(base + pos); pos += 4;
	uint32_t seq = buf_to_int32(base + pos); pos += 4;
	uint32_t unknow = buf_to_int32(base + pos); pos += 4;
	uint32_t unknow2 = buf_to_int32(base + pos); pos += 4;

	int32_struct* st_cmd = NULL;
	rc = buf_to_32struct(base + pos, &st_cmd, true); pos += rc;


	int32_struct* st_msgcookie = NULL;
	rc = buf_to_32struct(base + pos, &st_msgcookie, true); pos += rc;

	int32_struct* st_unknow = NULL;
	rc = buf_to_32struct(base + pos, &st_unknow, false); pos += rc;

	//body

	

	uint32_t bodylen = buf_to_int32(base + pos); pos += 4;

	string embeddbody = string(base + pos, body.length() - pos);
	result = resolve_respone_embedd_body(ctx, embeddbody);

	

	if (st_unknow) delete st_unknow;
	if (st_msgcookie) delete st_msgcookie;
	if (st_cmd) delete st_cmd;
	return result;
}

int resolver::resolve_pack(qq_ctx* ctx, std::string& data)
{
	const char* base = data.data();
	int pos = 0;
	int result = STATUS_FAILED;
	uint32_t plen = buf_to_int32(base + pos); pos += 4;
	if (plen != data.length()) {
		return STATUS_FAILED;
	}
	int8_t unknow_1byte = buf_to_int8(base + pos); pos += 1;
	int type_pos = pos;
	int32_t type = buf_to_int32(base + pos); pos += 4;
	
	if (type == 0x00000A02) {
		int32_t unknow_4bytes = 0;
		unknow_4bytes = buf_to_int32(base + pos); pos += 4;
		

		int16_t fix_what = buf_to_int16(base + pos); pos += 2;
		if (fix_what == 0x0530) {
			int crypted_len = data.length() - pos;
			string crypted_data = string(base + pos, crypted_len);

			string decrypted_data = bufutil::tea_decrypt(crypted_data.data(), crypted_data.length(), ctx->regctx.zero_key.data());
			if (decrypted_data.empty()) {
				decrypted_data = tea_decrypt(crypted_data.data(), crypted_len, ctx->shared_key.data());
			}
			if (decrypted_data.length() > 0) {
				result = resolve_0530_body(ctx, decrypted_data);
			}
		}
		else {
			pos = type_pos;
			type = buf_to_int32(base + pos); pos += 4;
			int8_t unknow_1byte = buf_to_int8(base + pos); pos += 1;
			int qqstr_len = buf_to_int32(base + pos); pos += 4;
			std::string qqstr = buf_to_string(base + pos, qqstr_len - 4); pos += (qqstr_len - 4);


			int crypted_len = data.length() - pos;
			string crypted_data = string(base + pos, crypted_len);
			std::string decrypt_data = tea_decrypt(crypted_data.data(), crypted_len, ctx->zero_key.data());
			if (decrypt_data.empty()) {
				decrypt_data = tea_decrypt(crypted_data.data(), crypted_len, ctx->shared_key.data());
			}
			if (decrypt_data.length() > 0) {
				result = resolve_respone_body(ctx, decrypt_data);
			}
		}
	}
	return result;
}
