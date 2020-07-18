#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t536 : public tlv_t
{
public:
	tlv_t536() {
		this->_cmd = 0x536;
	}	
	string get_tlv_536() {
		string buffer;

		//buffer = hex_to_string("0103000000006DA11BD504B7141D315EA15B8E2002F060000000006DA11BD504B7141D315EA19A342002F060000000006DA11BD504B7141D315EA213C02002F060");
		buffer = hex_to_string("0100");

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};