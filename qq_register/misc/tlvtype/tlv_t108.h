#pragma once
#include "tlv_t.h"

/*
 Tagindex: 264(0x0108)  -> (ksid)
						Length: 16(0x0010)
						Value: 89 FA 12 0F EE 8A D9 28 6B 9E 50 88 F5 F4 59 80
*/

class tlv_t108 : public tlv_t
{
public:
	tlv_t108() {
		this->_cmd = 0x108;
	}
	string get_tlv_t108(string& ksid) {
		string buffer;

		string_to_buf(ksid, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};