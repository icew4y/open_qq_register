#pragma once
#include "tlv_t.h"

/*

*/

class tlv_texample : public tlv_t
{
public:
	tlv_texample() {
		this->_cmd = 0x0;
	}
	tlv_texample(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x0;
		verify();
	}
	tlv_texample(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_example() {
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