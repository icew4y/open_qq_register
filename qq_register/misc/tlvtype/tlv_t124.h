#pragma once
#include "tlv_t.h"

/*
Tagindex: 292(0x0124)  -> (android network info)
										Length: 26(0x001A)
										Value: 00 07 61 6E 64 72 6F 69 64 00 03 36 2E 30 00 02 00 00 00 00 00 04 77 69 66 69
*/

class tlv_t124 : public tlv_t
{
public:
	tlv_t124() {
		this->_cmd = 0x124;
	}
	string get_tlv_124(string& os_version, int16_t network_type, string& sim_operator_name, string& apn_string) {
		string buffer;

		string android = "android";
		int16data_to_buf(android, buffer);

		int16data_to_buf(os_version, buffer);

		//network_type 0x0002
		int16_to_buf(network_type, buffer);


		//""
		int16data_to_buf(sim_operator_name, buffer);

		string empty_str = "";
		int16data_to_buf(empty_str, buffer);

		//wifi CMCC
		int16data_to_buf(apn_string, buffer);
		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};