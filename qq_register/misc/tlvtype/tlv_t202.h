#pragma once
#include "tlv_t.h"

/*
 Tagindex: 514(0x0202)  -> ()
						Length: 28(0x001C)
						Value: 00 10 4B 79 21 E3 CD 33 6A 2A C6 E6 20 EB EC 26 81 90 00 08 22 52 4F 4F 4D 35 47 22

										bssid_addr_md5: 4B 79 21 E3 CD 33 6A 2A C6 E6 20 EB EC 26 81 90
										ssid_addr: "ROOM5G"
*/

class tlv_t202 : public tlv_t
{
public:
	tlv_t202() {
		this->_cmd = 0x202;
	}
	string get_tlv_202(string& bssid_addr_md5, string& ssid) {
		string buffer;

		ssid = "\"" + ssid + "\"";
		int16data_to_buf(bssid_addr_md5, buffer);
		int16data_to_buf(ssid, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};