#pragma once
#include "tlv_t.h"
#include "../../strutil.h"
#include "../../md5/md5.h"

/*
Tagindex: 262(0x0106)  -> ()
						Length: 120(0x0078)
						Value: 36 25 B7 41 59 CA 99 81 57 45 E5 48 08 5C 93 53 9A E0 60 72 BE 27 B6 B9 A9 68 AE AA 05 EB 5E 90 BF 7A D6 F6 CD DA A0 7E 67 0F 7B 3E 36 0C 10 71 87 B6 F2 2E F6 4A 5B DD 6B AE C0 5C 7C 2E B0 DF 8D 5A 91 BE 2F C4 45 69 CF 6F A9 1F 27 61 98 7A 03 29 08 B8 34 90 1C 40 C4 E7 C9 F7 4E BE 0E 8F FA 2C 08 A4 94 B5 3F A7 C2 F4 1B 50 02 94 2E A6 30 DD 8C E3 16 19 35 7A

								decrypted tlv_106:
										_TGTGTVer: 4(0x0004)
										rand_32: 943203293(0x383823DD)
										_SSoVer: 7(0x00000007)
										_unknow1: 16(0x00000010)
										_unknow2: 0(0x00000000)
										qqnum: 3474327973(0x00000000CF1609A5)
										timestamp: 1587702204(0x5EA269BC)
										ipaddr: 0(0x00000000)
										fixed_1byte: 1(0x1)
										qqpsw_md5_key: 8A 6F 28 05 B4 51 5A C1 20 58 E7 9E 66 53 9B E9
										tgtgt_key: 40 2D D3 54 D0 DD 3C 68 A3 9D 16 E7 AE EA C9 81
										fixed_4byte: 0(0x00000000)
										isHaveGuid: 1(0x1)
										appid: 537063520(0x2002F060)
										_isSmslogin: 1(0x00000001)
										qq_string: 3474327973
*/
class tlv_t106 : public tlv_t
{
public:
	tlv_t106(){
		_TGTGTVer = 4;
		_SSoVer = 7;
		_cmd = 0x106;
	}
	string get_tlv106(int64_t qqnum, int64_t timestamp,string& qqpwd, string& pwd_md5key, string& tgtgt_key, string& guid) {
		string buffer;

		int16_to_buf(_TGTGTVer, buffer);
		int32_to_buf(getrand_num2(10000000, 88888888), buffer);
		int32_to_buf(_SSoVer, buffer);
		int32_to_buf(16, buffer);
		int32_to_buf(0, buffer);
		int64_to_buf(qqnum, buffer);
		int32_to_buf(time(NULL), buffer);
		//ipaddr
		int32_to_buf(0, buffer);
		int8_to_buf(1, buffer);

		//qqpwd md5
		string pwdmd5 = getmd5bytes(qqpwd);
		string_to_buf(pwdmd5, buffer);
		//tgtgt_key
		string_to_buf(tgtgt_key, buffer);
		//
		int32_to_buf(0, buffer);
		//isHaveGuid
		int8_to_buf(1, buffer);
		//guid
		string_to_buf(guid, buffer);
		//appid
		int32_to_buf(0x2002F060, buffer);
		//_isSmslogin
		//3 ÊÇ¶ÌÐÅµÇÂ¼
		//1 ·ñ
		int32_to_buf(1, buffer);
		//
		string qqstr = std::to_string(qqnum);
		int16data_to_buf(qqstr, buffer);

		//_unknow2Zerobytes
		int16_to_buf(0, buffer);

		string encrypted_data = bufutil::tea_encrypt(buffer.data(), buffer.length(), pwd_md5key.data());


		this->fill_head();
		this->fill_body(encrypted_data);
		return this->get_buf();
	}
protected:
private:
	int _SSoVer;
	int _TGTGTVer;
	int _t106_body_len;	
};