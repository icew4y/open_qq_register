#pragma once
#include "tlv_t.h"

/*
package oicq.wlogin_sdk.tlv_type;

import oicq.wlogin_sdk.tools.util;

public class tlv_t105 extends tlv_t {
	int _en_pos;
	int _enlen;
	int _pic_pos;
	int _piclen;

	public tlv_t105() {
		this._piclen = 0;
		this._enlen = 0;
		this._pic_pos = 0;
		this._en_pos = 0;
		this._cmd = 0x105;
	}

	public byte[] get_pic() {
		byte[] v0 = new byte[this._piclen];
		if(this._piclen <= 0) {
			return v0;
		}

		System.arraycopy(this._buf, this._pic_pos, ((Object)v0), 0, this._piclen);
		return v0;
	}

	public byte[] get_sign() {
		byte[] v0 = new byte[this._enlen];
		if(this._enlen <= 0) {
			return v0;
		}

		System.arraycopy(this._buf, this._en_pos, ((Object)v0), 0, this._enlen);
		return v0;
	}

	@Override  // oicq.wlogin_sdk.tlv_type.tlv_t
	public Boolean verify() {
		if(this._body_len < 2) {
			return Boolean.valueOf(false);
		}

		this._enlen = util.buf_to_int16(this._buf, this._head_len);
		if(this._body_len < this._enlen + 4) {
			return Boolean.valueOf(false);
		}

		this._piclen = util.buf_to_int16(this._buf, this._head_len + 2 + this._enlen);
		if(this._body_len < this._enlen + 4 + this._piclen) {
			return Boolean.valueOf(false);
		}

		this._en_pos = this._head_len + 2;
		this._pic_pos = this._enlen + 4 + this._head_len;
		return Boolean.valueOf(true);
	}
}


*/

class tlv_t105 : public tlv_t
{
public:
	tlv_t105() {
		this->_cmd = 0x105;
	}
	tlv_t105(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x105;
		verify();
	}
	tlv_t105(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_105() {
		string buffer;


		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}

	string get_sign() {
		return _sign;
	}

	string get_pic_jpg() {
		return _pic_jpg;
	}

protected:
private:
	void verify() {
		//Ìø¹ýtype ºÍ  len
		this->_pos = 4;
		_base = this->_buf.data();
		_get_end_len();
		_get_sign();
		_get_pic_jpg();
	}

	void _get_end_len() {
		_end_len = buf_to_int16(_base + this->_pos); this->_pos += 2;
	}

	void _get_sign() {
		_sign = buf_to_string(_base + this->_pos, _end_len); this->_pos += _end_len;
	}

	void _get_pic_jpg() {
		int16_struct* st_jpg = NULL;
		int rc = buf_to_16struct(_base + this->_pos, &st_jpg); this->_pos += rc;
		_pic_jpg = string(st_jpg->data, st_jpg->len);
		if (st_jpg) delete st_jpg;
	}
private:
	const char* _base;
	int _end_len;
	string _sign;
	string _pic_jpg;
};