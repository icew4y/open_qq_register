#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t154 : public tlv_t
{
public:
	tlv_t154() {
		this->_cmd = 0x154;
	}
	string get_tlv_154(uint32_t seq) {
		string buffer;

		int32_to_buf(seq, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};