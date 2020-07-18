#pragma once
#include "tlv_t.h"
#include "../../strutil.h"


/*
 Tagindex: 1(0x0001)  -> (RegTLV(1),ksid)
						Length: 20(0x0014)
						Value: 00 01 79 69 1A 95 CF 16 09 A5 5E A2 69 BC 00 00 00 00 00 00

										_ip_ver:1(0x0001)
										rand_32:2036931221(0x79691A95)
										qqnumber:3474327973(0xCF1609A5)
										server_cur_time:1587702204(0x5EA269BC)
										ipaddr:0(0x00000000)
										ipaddr_length:0(0x0000)
*/
class tlv_t1 : public tlv_t
{
public:


	tlv_t1() {
		this->_cmd = 0x1;
	}
	string get_tlv_t1(uint64_t qqnum, int32_t ipaddr, int32_t timestamp) {
		string buffer;

		int16_to_buf(1, buffer);
		int32_to_buf(getrand_num2(10000000, 88888888), buffer);
		int32_to_buf(qqnum, buffer);
		int32_to_buf(timestamp, buffer);
		int32_to_buf(ipaddr, buffer);
		int16_to_buf(0, buffer);
		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:


};