#pragma once
/*
Tagindex: 322(0x0142)  -> (apk_id)
						Length: 24(0x0018)
						Value: 00 00 00 14 63 6F 6D 2E 74 65 6E 63 65 6E 74 2E 6D 6F 62 69 6C 65 71 71
*/

#include "tlv_t.h"

class tlv_t142 : public tlv_t
{
public:
	tlv_t142() {
		apk_id = "com.tencent.mobileqq";
		this->_cmd = 0x142;
	}
	string get_tlv_t142() {
		string buffer;

		int32data_to_buf(apk_id, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:
	string apk_id;
};