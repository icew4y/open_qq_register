#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t104 : public tlv_t
{
public:
	tlv_t104() {
		this->_cmd = 0x104;
	}
	tlv_t104(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x104;
		verify();
	}
	tlv_t104(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_104(string& captcha_sig) {
		string buffer;
		
		string_to_buf(captcha_sig, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}

	string get_captcha_sig() {
		return _captcha_sig;
	}
protected:
private:
	void verify() {
		//Ìø¹ýtype ºÍ  len
		this->_pos = 4;

		_get_captcha_sig();
	}

	void _get_captcha_sig() {
		const char* base = this->_buf.data();
		_captcha_sig = buf_to_string(base + this->_pos, this->_buf.length() - this->_pos);
	}
private:
	string _captcha_sig;
};