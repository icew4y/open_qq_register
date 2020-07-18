#pragma once
#include "tlv_t.h"

/*
Tagindex: 366(0x016E)  -> (Build.MODEL)
										Length: 8(0x0008)
										Value: 4E 65 78 75 73 20 36 50
*/

class tlv_t16e : public tlv_t
{
public:
	tlv_t16e() {
		this->_cmd = 0x16e;
	}
	string get_tlv_16e(string& build_model) {
		string buffer;

		string_to_buf(build_model, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};