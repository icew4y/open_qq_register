#pragma once
#include "tlv_t.h"

/*
t.aa = (util.isFileExist("/system/bin/su")) || (util.isFileExist("/system/xbin/su")) || (util.isFileExist("/sbin/su")) ? 1 : 0;

v29.get_tlv_153(t.aa)
*/

class tlv_t153 : public tlv_t
{
public:
	tlv_t153() {
		this->_cmd = 0x0153;
	}
	tlv_t153(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x0153;
		verify();
	}
	tlv_t153(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_153(int16_t isRoot) {
		string buffer;

		int16_to_buf(isRoot, buffer);

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