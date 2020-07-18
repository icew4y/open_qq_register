#pragma once
#include "tlv_t.h"

/*
			   Tagindex: 321(0x0141)  -> ()
						Length: 12(0x000C)
						Value: 00 01 00 00 00 02 00 04 77 69 66 69

										_version: 1(0x0001)
										st_sim_operator_name:
										st_network_type: 2(0x0002)
										st_apn_string: wifi
*/

class tlv_t141 : public tlv_t
{
public:
	tlv_t141() {
		this->_cmd = 0x141;
		_version = 1;
	}
	string get_tlv_141(string& sim_operator_name, int16_t network_type, string& apn_string) {
		string buffer;

		int16_to_buf(_version, buffer);
		int16data_to_buf(sim_operator_name, buffer);
		int16_to_buf(network_type, buffer);
		int16data_to_buf(apn_string, buffer);
		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:
	int _version;
};