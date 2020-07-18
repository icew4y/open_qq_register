#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t194 : public tlv_t
{
public:
	tlv_t194() {
		this->_cmd = 0x194;
	}
	tlv_t194(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x194;
		verify();
	}
	tlv_t194(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_194(string& imsi_md5) {
		string buffer;
		string_to_buf(imsi_md5, buffer);

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