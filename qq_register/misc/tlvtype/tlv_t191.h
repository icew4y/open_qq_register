#pragma once
#include "tlv_t.h"

/*
 Tagindex: 401(0x0191)  -> (SetCanWebVerify(0x82/0))
						Length: 1(0x0001)
						Value: 82
*/

class tlv_t191 : public tlv_t
{
public:
	tlv_t191() {
		this->_cmd = 0x191;
	}
	string get_tlv_191(int8_t CanWebVerify) {
		string buffer;

		int8_to_buf(CanWebVerify, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};