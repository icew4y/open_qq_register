#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t192 : public tlv_t
{
public:
	tlv_t192() {
		this->_cmd = 0x192;
	}
	tlv_t192(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_192() {
		string buffer;


		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}

	string get_url() {
		return _url;
	}
protected:
private:
	void verify() {
		//Ìø¹ýtype ºÍ  len
		this->_pos = 4;
		_url = buf_to_string(this->_buf.data() + this->_pos, this->_buf.length() - 4);
	}
private:
	string _url;
};