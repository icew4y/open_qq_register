#pragma once
#include "tlv_t.h"


/*

Tagindex: 256(0x0100)  -> ()
						Length: 22(0x0016)
						Value: 00 01 00 00 00 07 00 00 00 10 20 02 F0 60 00 00 00 00 02 14 10 E0

										_db_buf_ver:1(0x0001)
										_sso_ver:7(0x00000007)
										_appid:16(0x00000010)
										appid2:537063520(0x2002F060)
										unknowBit:34869472(0x021410E0)
*/
class tlv_t100 : public tlv_t
{
public:
	tlv_t100() {
		_db_buf_ver = 1;
		_cmd = 0x100;
	}
	string get_tlv_t100(int32_t _sso_ver, int32_t dwDstAppid, int32_t dwSubDstAppid, int32_t AppClientVersion, int32_t main_sigmap) {
		string buffer;

		int16_to_buf(_db_buf_ver, buffer);
		int32_to_buf(_sso_ver, buffer);
		//apid
		int32_to_buf(dwDstAppid, buffer);
		int32_to_buf(dwSubDstAppid, buffer);

		//zero
		int32_to_buf(AppClientVersion, buffer);
		//int main_sigmap = arg35 & 0xFDFFFFFF;
		int32_to_buf(main_sigmap, buffer);
		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:
	int _db_buf_ver;
};