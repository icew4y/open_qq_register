#pragma once
#include "tlv_t.h"

/*

*/

class tlv_t544 : public tlv_t
{
public:
	tlv_t544() {
		this->_cmd = 0x544;
	}
	string get_tlv_544() {
		string buffer;

		buffer = hex_to_string("000007D90000000000220020FD265B200CD2D338975B59CE20A093994E7F0F03478D253F1253C9A9C88121CE01000000000001000000010000000171AA6D09DD474536634369456369620014636F6D2E74656E63656E742E6D6F62696C657171413642373435424632344132433237373532373731364636463336454236384404FA96BE00000000");
		//buffer = hex_to_string("00");

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};