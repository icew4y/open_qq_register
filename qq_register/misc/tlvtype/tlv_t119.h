#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t119 : public tlv_t
{
public:
	tlv_t119() {
		this->_cmd = 0x119;
	}
	tlv_t119(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x119;
		verify();
	}
	tlv_t119(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_119() {
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