#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t145 : public tlv_t
{
public:
	tlv_t145() {
		this->_cmd = 0x145;
	}
	string get_tlv_145(string& guid) {
		string buffer;

		string_to_buf(guid, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};