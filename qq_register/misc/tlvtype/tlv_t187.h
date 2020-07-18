#pragma once
#include "tlv_t.h"

/*
 Tagindex: 391(0x0187)  -> (mac_addr md5)
						Length: 16(0x0010)
						Value: 0F 60 72 64 FC 63 18 A9 2B 9E 13 C6 5D B7 CD 3C

*/

class tlv_t187 : public tlv_t
{
public:
	tlv_t187() {
		this->_cmd = 0x187;
	}
	string get_tlv_187(string& mac_addr_md5) {
		string buffer;

		string_to_buf(mac_addr_md5, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};