#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t16A : public tlv_t
{
public:
	tlv_t16A() {
		this->_cmd = 0x016A;
	}
	tlv_t16A(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x016A;
		verify();
	}
	tlv_t16A(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_16A(string& data) {
		string buffer;

		string_to_buf(data, buffer);

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