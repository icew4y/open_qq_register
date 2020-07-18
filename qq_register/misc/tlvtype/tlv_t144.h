#pragma once
#include "tlv_t.h"
#include "tlv_t109.h"
#include "tlv_t52d.h"
#include "tlv_t124.h"
#include "tlv_t128.h"
#include "tlv_t16e.h"
#include "tlv_t148.h"
#include "tlv_t148.h"
#include "tlv_t153.h"

/*

Tagindex: 324(0x0144)  -> ()
						Length: 488(0x01E8)
						Value: 7D DD 5B 67 52 CB ED 46 99 49 98 58 61 02 A2 F1 DA 6E CB 43 84 B8 0E 09 19 DE 59 4D 7D 8C 03 AD 62 37 1E A3 C0 FC 4D C9 78 A9 38 95 AC D2 C3 93 2C 92 31 DE 34 72 15 01 94 34 35 0E 93 A1 78 EC E6 45 38 3B B8 37 A7 08 7F 93 BB CE 43 83 56 41 5C E9 2D E4 C6 B8 BC 74 AC E5 03 C7 88 CD AD 6C 00 79 AA DC 17 58 75 A1 C7 6F 66 2C FA BC E1 D5 75 E8 74 2E EA 8A 21 ED 2D 6E 90 BF 85 1F A1 10 60 DA C4 FD B1 A3 09 9D 74 93 DB 76 49 2A 57 9F E2 54 AC E7 7B DD E4 20 4A D4 A9 F2 17 BB 53 E4 B7 A1 78 7A EF 98 A6 30 26 CF FC FE 78 67 B6 A4 76 77 07 2B 9F A6 AC F0 7A 3E 01 3A 55 D4 D9 EE 7D 59 D4 C8 3E 9A 47 F9 45 EC E9 63 7E 4D F8 89 22 CC 3A 7D 26 F3 3E 2F AE 7C 57 F1 6A C8 E2 2B 07 14 E4 F2 4E 83 7E DF F7 12 DE F4 E0 44 10 56 C8 13 60 8B 21 5B 64 DA C9 35 3D E3 41 E8 20 2A 76 0C B7 96 B4 FA 68 39 2D 70 8F 0B 2B 29 F1 B8 8A A2 99 8A 0C ED A0 46 99 FB 1D C7 2A 14 54 5B 5E EF D5 04 FB B8 61 E7 43 5D 81 F0 40 61 E7 AA F5 A5 05 A3 F5 A2 32 17 52 AF 4D BC 63 07 E3 30 65 86 5F F3 71 97 3A 92 64 DE 25 52 38 31 DB AE ED 98 09 D6 61 8B 90 57 B1 87 AA E7 23 82 F6 18 5B 56 1E 74 13 6E 4A A0 32 1E 64 08 07 54 B6 08 56 B9 13 01 71 DE 96 B7 AA 02 98 CE F4 64 83 7B FB 83 68 93 7F 33 C2 52 F8 2E 59 F3 90 A6 0F D9 30 63 1E 5F 9D B7 43 4E 43 9D A8 62 80 37 98 00 DA 99 1C 7C 57 A2 FA CB 0A 19 68 3F 86 67 1E 70 3D 43 75 09 1A F3 7C 24 5C FF B3 3F B1 E6 17 1C DA F5 16 09 9B 8E F5 E3 3D DE 4B E7 DE 6C 57 B6 60 4E C9 70 C0 1C EA BA 0B 4B 0D 70 72 80 46 9D 57 C8 DE 49 B6 0F A8 3F

								decrypted tlv_144:
										tlv_cnt: 5(0x0005)
										Tagindex: 265(0x0109)  -> (android_id md5)
										Length: 16(0x0010)
										Value: 41 26 29 7B 1C 1A 99 D9 F3 44 A6 56 68 43 65 60


										Tagindex: 1325(0x052D)  -> (android_dev_info(protobuf))
										Length: 361(0x0169)
										Value: 0A 0C 61 6E 67 6C 65 72 2D 30 31 2E 33 31 12 AC 01 4C 69 6E 75 78 20 76 65 72 73 69 6F 6E 20 33 2E 31 30 2E 37 33 2D 67 39 62 36 35 39 36 64 20 28 61 6E 64 72 6F 69 64 2D 62 75 69 6C 64 40 76 70 61 6B 34 2E 6D 74 76 2E 63 6F 72 70 2E 67 6F 6F 67 6C 65 2E 63 6F 6D 29 20 28 67 63 63 20 76 65 72 73 69 6F 6E 20 34 2E 39 2E 78 2D 67 6F 6F 67 6C 65 20 32 30 31 34 30 38 32 37 20 28 70 72 65 72 65 6C 65 61 73 65 29 20 28 47 43 43 29 20 29 20 23 31 20 53 4D 50 20 50 52 45 45 4D 50 54 20 53 61 74 20 53 65 70 20 32 36 20 31 38 3A 31 37 3A 35 39 20 55 54 43 20 32 30 31 35 1A 03 52 45 4C 22 07 32 32 39 34 38 31 39 2A 39 67 6F 6F 67 6C 65 2F 61 6E 67 6C 65 72 2F 61 6E 67 6C 65 72 3A 36 2E 30 2F 4D 44 41 38 39 44 2F 32 32 39 34 38 31 39 3A 75 73 65 72 2F 72 65 6C 65 61 73 65 2D 6B 65 79 73 32 24 35 64 37 37 30 63 34 31 2D 34 66 39 64 2D 34 65 33 30 2D 62 34 36 30 2D 30 63 34 37 62 63 30 32 38 37 30 34 3A 10 34 32 36 38 65 66 61 30 33 61 34 66 64 30 35 61 42 20 2E 32 2E 36 2E 31 2E 63 34 2D 30 30 30 30 34 2D 4D 38 39 39 34 46 41 41 41 41 4E 41 5A 4D 2D 31 4A 07 32 32 39 34 38 31 39


										Tagindex: 292(0x0124)  -> (android network info)
										Length: 26(0x001A)
										Value: 00 07 61 6E 64 72 6F 69 64 00 03 36 2E 30 00 02 00 00 00 00 00 04 77 69 66 69


										Tagindex: 296(0x0128)  -> (ÓÐguid)
										Length: 45(0x002D)
										Value: 00 00 00 01 00 01 00 00 00 00 08 4E 65 78 75 73 20 36 50 00 10 0C 93 EF C2 F8 A0 50 08 76 BD 1C C2 82 A3 BE 04 00 06 67 6F 6F 67 6C 65


										Tagindex: 366(0x016E)  -> (Build.MODEL)
										Length: 8(0x0008)
										Value: 4E 65 78 75 73 20 36 50
*/

class tlv_t144 : public tlv_t
{
public:
	tlv_t144() {
		this->_cmd = 0x144;
	}
	string get_tlv_t144(bool isExchangeA2, string& tgtgt_key,string& android_id, string& androidid_md5,
		string& osVersion, int16_t network_type, string& sim_operator_name,
		string& apn_string, string& model_type, string& guid, string& phone_brand, int32_t guidsrcSigmap) {
		string buffer;

		tlv_t109 t109;
		tlv_t52d t52d;
		tlv_t124 t124;
		tlv_t128 t128;
		tlv_t16e t16e;
		

		string t109_buf = t109.get_tlv_109(androidid_md5);
		string t52d_buf = t52d.get_tlv_t52d(android_id);
		string t124_buf = t124.get_tlv_124(osVersion, network_type, sim_operator_name, apn_string);
		string t128_buf = t128.get_tlv_128(guidsrcSigmap, model_type, guid, phone_brand);
		
		string t148_buf;
		string t153_buf;
		if (isExchangeA2) {
			tlv_t148 t148;
			string tencent_token_apksig = hex_to_string("CB746CE354D17D9BCD03F7F8C232F4C1");
			t148_buf = t148.get_tlv_148("com.tencent.token", 0x1F2C6DEB, 0x1F2C6DEB, 0x00000001, "6.9.15", tencent_token_apksig);

			tlv_t153 t153;
			t153_buf = t153.get_tlv_153(0x0000);
		}
		string t16e_buf = t16e.get_tlv_16e(model_type);

		int16_t tlvcnt = 0;
		int fix_pos = 0;
		
		int16_to_buf(tlvcnt, buffer);
		
		string_to_buf(t109_buf, buffer); tlvcnt++;
		string_to_buf(t52d_buf, buffer); tlvcnt++;
		string_to_buf(t124_buf, buffer); tlvcnt++;
		string_to_buf(t128_buf, buffer); tlvcnt++;
		if (isExchangeA2) {
			string_to_buf(t148_buf, buffer); tlvcnt++;
			string_to_buf(t153_buf, buffer); tlvcnt++;
		}
		string_to_buf(t16e_buf, buffer); tlvcnt++;

		//ÐÞ¸´´óÐ¡
		int16_t fix_data = htons(tlvcnt);
		fix_buf_data(fix_pos, (const char*)&fix_data, sizeof(fix_data), buffer);

		string encrypted_data = bufutil::tea_encrypt(buffer.data(), buffer.length(), tgtgt_key.data());
		this->fill_head();
		this->fill_body(encrypted_data);
		return this->get_buf();
	}
protected:
private:

};