#pragma once
#include "tlv_t.h"

/*
 Tagindex: 375(0x0177)  -> (new tlv_t177().get_tlv_177(0x5E53F202L, "6.0.0.2423");)
						Length: 17(0x0011)
						Value: 01 5E 53 F2 02 00 0A 36 2E 30 2E 30 2E 32 34 32 33
*/

class tlv_t177 : public tlv_t
{
public:
	tlv_t177() {
		this->_cmd = 0x177;
	}
	string get_tlv_177(int32_t fixed_5E53F202, string ver_string) {
		string buffer;
		
		int8_to_buf(1, buffer);
		int32_to_buf(fixed_5E53F202, buffer);

		string d = ver_string;
		int16data_to_buf(d, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};