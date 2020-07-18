#pragma once
#include "tlv_t.h"

/*
package oicq.wlogin_sdk.tlv_type;

import oicq.wlogin_sdk.tools.util;

public class tlv_t146 extends tlv_t {
	public int _errorinfo_len;
	public int _msg_len;
	public int _title_len;

	public tlv_t146() {
		this._title_len = 0;
		this._msg_len = 0;
		this._errorinfo_len = 0;
		this._cmd = 326;
	}

	public int get_code() {
		return util.buf_to_int16(this._buf, this._head_len + 2);
	}

	public byte[] get_errorinfo() {
		byte[] v0 = new byte[this._errorinfo_len];
		System.arraycopy(this._buf, this._head_len + 12 + this._title_len + this._msg_len, ((Object)v0), 0, this._errorinfo_len);
		return v0;
	}

	public byte[] get_msg() {
		byte[] v0 = new byte[this._msg_len];
		System.arraycopy(this._buf, this._head_len + 8 + this._title_len, ((Object)v0), 0, this._msg_len);
		return v0;
	}

	public byte[] get_title() {
		byte[] v0 = new byte[this._title_len];
		System.arraycopy(this._buf, this._head_len + 6, ((Object)v0), 0, this._title_len);
		return v0;
	}

	public int get_type() {
		return util.buf_to_int16(this._buf, this._head_len + 8 + this._title_len + this._msg_len);
	}

	public int get_ver() {
		return util.buf_to_int16(this._buf, this._head_len);
	}

	@Override  // oicq.wlogin_sdk.tlv_type.tlv_t
	public Boolean verify() {
		if(this._body_len < 12) {
			return Boolean.valueOf(false);
		}

		int v0 = util.buf_to_int16(this._buf, this._head_len + 4);
		if(this._body_len < v0 + 12) {
			return Boolean.valueOf(false);
		}

		this._title_len = v0;
		int v0_1 = util.buf_to_int16(this._buf, this._head_len + 6 + this._title_len);
		if(this._body_len < this._title_len + 12 + v0_1) {
			return Boolean.valueOf(false);
		}

		this._msg_len = v0_1;
		int v0_2 = util.buf_to_int16(this._buf, this._head_len + 10 + this._title_len + this._msg_len);
		if(this._body_len < this._title_len + 12 + this._msg_len + v0_2) {
			return Boolean.valueOf(false);
		}

		this._errorinfo_len = v0_2;
		return Boolean.valueOf(true);
	}
}


*/

class tlv_t146 : public tlv_t
{
public:
	tlv_t146() {
		this->_cmd = 0x146;
	}

	tlv_t146(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x146;
		verify();
	}

	tlv_t146(int16_t cmd, int16_t len, string value):
		tlv_t(cmd, len, value)
	{
		verify();
	}

private:
	void verify() {
		//Ìø¹ýtype ºÍ  len
		this->_pos = 4;
		_get_ver();
		_get_type();
		_get_title();
		_get_msg();
		_get_code();
	}
	void _get_code() {
		_code = buf_to_int32(this->_buf.data() + this->_pos); this->_pos += 4;
	}

	void _get_msg() {
		int16_struct* st_msg = NULL;
		int rc = buf_to_16struct(this->_buf.data() + this->_pos, &st_msg); this->_pos += rc;
		_msg = string(st_msg->data, st_msg->len);
		if (st_msg) delete st_msg;
	}

	void _get_title() {
		int16_struct* st_title = NULL;
		int rc = buf_to_16struct(this->_buf.data() + this->_pos, &st_title); this->_pos += rc;
		_title = string(st_title->data, st_title->len);
		if (st_title) delete st_title;
	}
	void _get_type() {
		_type = buf_to_int16(this->_buf.data() + this->_pos); this->_pos += 2;
	}
	void _get_ver() {
		_ver = buf_to_int16(this->_buf.data() + this->_pos); this->_pos += 2;
	}
public:
	int16_t get_ver() {
		return _ver;
	}
	int16_t get_type() {
		return _type;
	}
	string& get_title() {
		return _title;
	}
	string& get_msg() {
		return _msg;
	}
	int32_t get_code() {
		return _code;
	}
protected:
private:
	int16_t _ver;
	int16_t _type;
	string _title;
	string _msg;
	int32_t _code;
};