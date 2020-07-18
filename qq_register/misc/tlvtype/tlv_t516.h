#pragma once
#include "tlv_t.h"

/*
Tagindex: 1302(0x0516)  -> (_source_type)
						Length: 4(0x0004)
						Value: 00 00 00 00
*/

class tlv_t516 : public tlv_t
{
public:
	tlv_t516() {
		this->_cmd = 0x516;
		_source_type = 0;
	}
	string get_tlv_516() {
		string buffer;
		int32_to_buf(_source_type, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:
	int _source_type;
};