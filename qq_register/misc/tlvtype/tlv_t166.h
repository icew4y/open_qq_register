#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t166 : public tlv_t
{
public:
	tlv_t166() {
		this->_cmd = 0x166;
	}
	tlv_t166(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x166;
		verify();
	}
	tlv_t166(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_166(int8_t ImgType) {
		string buffer;

		int8_to_buf(ImgType, buffer);

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