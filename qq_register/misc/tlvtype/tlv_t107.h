#pragma once
/*
Tagindex: 263(0x0107)  -> ()
						Length: 6(0x0006)
						Value: 00 00 00 00 00 01


						public byte[] get_tlv_107(int arg3, int arg4, int arg5, int arg6) {
		byte[] v1 = new byte[this._t107_body_len];
		util.int16_to_buf(v1, 0, arg3);
		util.int8_to_buf(v1, 2, arg4);
		util.int16_to_buf(v1, 3, arg5);
		util.int8_to_buf(v1, 5, arg6);
		this.fill_head(this._cmd);
		this.fill_body(v1, this._t107_body_len);
		this.set_length();
		return this.get_buf();
	}
*/

#include "tlv_t.h"

class tlv_t107 : public tlv_t
{
public:
	tlv_t107() {
		this->_cmd = 0x107;
	}
	string get_tlv_t107() {
		string buffer;

		int16_to_buf(0, buffer);
		int8_to_buf(0, buffer);
		int16_to_buf(0, buffer);
		int8_to_buf(1, buffer);
		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};