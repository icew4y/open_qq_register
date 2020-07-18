#pragma once
#include "tlv_t.h"

/*
 Tagindex: 1349(0x0545)  -> (android_id md5)
						Length: 16(0x0010)
						Value: 41 26 29 7B 1C 1A 99 D9 F3 44 A6 56 68 43 65 60
*/

class tlv_t545 : public tlv_t
{
public:
	tlv_t545() {
		this->_cmd = 0x545;
	}
	string get_tlv_545(string& android_id_md5) {
		string buffer;
		string_to_buf(android_id_md5, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};