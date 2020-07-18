#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t402 : public tlv_t
{
public:
	tlv_t402() {
		this->_cmd = 0x0402;
	}
	tlv_t402(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x0402;
		verify();
	}
	tlv_t402(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_402() {
		string buffer;


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