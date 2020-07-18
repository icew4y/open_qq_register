#pragma once
#include "tlv_t.h"

/*
	   Tagindex: 1313(0x0521)  -> (ifQQLoginInQim(yes=13L,no=0),后面两个字节固定0)
						Length: 6(0x0006)
						Value: 00 00 00 00 00 00
*/

class tlv_t521 : public tlv_t
{
public:
	tlv_t521() {
		this->_cmd = 0x521;
	}
	string get_tlv_521() {
		string buffer;

		int32_to_buf(0, buffer);
		int16_to_buf(0, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};