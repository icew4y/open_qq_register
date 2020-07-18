#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t193 : public tlv_t
{
public:
	tlv_t193() {
		this->_cmd = 0x193;
	}
	tlv_t193(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x193;
		verify();
	}
	tlv_t193(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_193(string& slide_captcha_ticket) {
		string buffer;

		string_to_buf(slide_captcha_ticket, buffer);
		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:
	void verify() {
		//Ìø¹ýtype ºÍ  len
		this->_pos = 4;

		const char* base = this->_buf.data();

	}
private:
};