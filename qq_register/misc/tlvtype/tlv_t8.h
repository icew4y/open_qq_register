#pragma once
#include "tlv_t.h"

/*

 Tagindex: 8(0x0008)  -> (¹Ì¶¨µÄ)
						Length: 8(0x0008)
						Value: 00 00 00 00 08 04 00 00


byte[] v48 = v20.get_tlv_8(0, t.u, 0);

t.u = 0x804;


*/

class tlv_t8 : public tlv_t
{
public:
	tlv_t8() {
		this->_cmd = 0x8;
		u = 0x804;
	}
	string get_tlv_8() {
		string buffer;

		int16_to_buf(0, buffer);
		int32_to_buf(u, buffer);
		int16_to_buf(0, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:
	int u;
};