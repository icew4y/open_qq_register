#pragma once
#include "tlv_t.h"

class tlv_t18 : public tlv_t
{
public:
	tlv_t18() {
		this->_t18_body_len = 22;
		this->_ping_version = 1;
		this->_sso_version = 0x600;
		this->_cmd = 24;
	}
	string get_tlv18(int64_t qqnum, int32_t dwDstAppid) {
		string buffer;
		int32_t fixed_zero = 0;
		int16_to_buf((int16_t)_ping_version, buffer);
		int32_to_buf((int32_t)_sso_version, buffer);
		int32_to_buf((int32_t)dwDstAppid, buffer);
		int32_to_buf((int32_t)fixed_zero, buffer);
		int32_to_buf((int32_t)qqnum, buffer);
		int16_to_buf((int16_t)0, buffer);
		int16_to_buf((int16_t)0, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:
	int _ping_version;
	int _sso_version;
	int _t18_body_len;
};