#pragma once
#include "tlv_t.h"
#include "tlv_t536.h"
/*

*/

class tlv_t525 : public tlv_t
{
public:
	tlv_t525() {
		this->_cmd = 0x525;
	}
	string get_tlv_525() {
		string buffer;

		int16_t tlvcnt = 1;
		int16_to_buf(tlvcnt, buffer);

		//tlv

		tlv_t536 t536;
		string t536_buf = t536.get_tlv_536();
		string_to_buf(t536_buf, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};