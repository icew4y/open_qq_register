#pragma once
#include "tlv_t.h"

/*
 Tagindex: 1297(0x0511)  -> (需要取的pskey域名)
						Length: 211(0x00D3)
						Value: 00 0E 01 00 0A 74 65 6E 70 61 79 2E 63 6F 6D 01 00 11 6F 70 65 6E 6D 6F 62 69 6C 65 2E 71 71 2E 63 6F 6D 01 00 0B 64 6F 63 73 2E 71 71 2E 63 6F 6D 01 00 0E 63 6F 6E 6E 65 63 74 2E 71 71 2E 63 6F 6D 01 00 0C 71 7A 6F 6E 65 2E 71 71 2E 63 6F 6D 01 00 0A 76 69 70 2E 71 71 2E 63 6F 6D 01 00 11 67 61 6D 65 63 65 6E 74 65 72 2E 71 71 2E 63 6F 6D 01 00 0A 71 75 6E 2E 71 71 2E 63 6F 6D 01 00 0B 67 61 6D 65 2E 71 71 2E 63 6F 6D 01 00 0C 71 71 77 65 62 2E 71 71 2E 63 6F 6D 01 00 09 74 69 2E 71 71 2E 63 6F 6D 01 00 0D 6F 66 66 69 63 65 2E 71 71 2E 63 6F 6D 01 00 0B 6D 61 69 6C 2E 71 71 2E 63 6F 6D 01 00 0A 6D 6D 61 2E 71 71 2E 63 6F 6D

										domain_len: 14(0x000E)
										byteWhat: 1(0x1)
										st_domain(0): tenpay.com
										byteWhat: 1(0x1)
										st_domain(1): openmobile.qq.com
										byteWhat: 1(0x1)
										st_domain(2): docs.qq.com
										byteWhat: 1(0x1)
										st_domain(3): connect.qq.com
										byteWhat: 1(0x1)
										st_domain(4): qzone.qq.com
										byteWhat: 1(0x1)
										st_domain(5): vip.qq.com
										byteWhat: 1(0x1)
										st_domain(6): gamecenter.qq.com
										byteWhat: 1(0x1)
										st_domain(7): qun.qq.com
										byteWhat: 1(0x1)
										st_domain(8): game.qq.com
										byteWhat: 1(0x1)
										st_domain(9): qqweb.qq.com
										byteWhat: 1(0x1)
										st_domain(10): ti.qq.com
										byteWhat: 1(0x1)
										st_domain(11): office.qq.com
										byteWhat: 1(0x1)
										st_domain(12): mail.qq.com
										byteWhat: 1(0x1)
										st_domain(13): mma.qq.com
*/

class tlv_t511 : public tlv_t
{
public:
	tlv_t511() {
		this->_cmd = 0x511;
	}
	string get_tlv_511(vector<string>& domains) {
		string buffer;

		int16_to_buf(domains.size(), buffer);
		for (string domain : domains){
			int8_to_buf(1, buffer);
			int16data_to_buf(domain, buffer);
		}

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};