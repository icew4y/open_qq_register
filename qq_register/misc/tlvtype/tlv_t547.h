#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t547 : public tlv_t
{
public:
	tlv_t547() {
		this->_cmd = 0x547;
	}
	tlv_t547(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x547;
		verify();
	}
	tlv_t547(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_547(string& syncCalcPow) {
		string buffer;

		//syncCalcPow 00 00 
		string_to_buf(syncCalcPow, buffer);

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