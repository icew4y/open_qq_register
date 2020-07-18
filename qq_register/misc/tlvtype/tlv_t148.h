#pragma once
#include "tlv_t.h"

/*
public class tlv_t148 extends tlv_t {
	public tlv_t148() {
		this._cmd = 328;
	}

	public byte[] get_tlv_148(byte[] arg7, long arg8, long arg10, long arg12, byte[] arg14, byte[] arg15) {
		if(arg7 == null) {
			arg7 = new byte[0];
		}

		if(arg14 == null) {
			arg14 = new byte[0];
		}

		if(arg15 == null) {
			arg15 = new byte[0];
		}

		int v0 = this.limit_len(arg7, 0x20);
		int v1 = this.limit_len(arg14, 0x20);
		int v2 = this.limit_len(arg15, 0x20);
		byte[] v3 = new byte[v0 + 16 + v1 + 2 + v2];
		util.int16_to_buf(v3, 0, v0);
		System.arraycopy(((Object)arg7), 0, ((Object)v3), 2, v0);
		int v0_1 = v0 + 2;
		util.int64_to_buf32(v3, v0_1, arg8);
		int v0_2 = v0_1 + 4;
		util.int64_to_buf32(v3, v0_2, arg10);
		int v0_3 = v0_2 + 4;
		util.int64_to_buf32(v3, v0_3, arg12);
		int v0_4 = v0_3 + 4;
		util.int16_to_buf(v3, v0_4, v1);
		int v0_5 = v0_4 + 2;
		System.arraycopy(((Object)arg14), 0, ((Object)v3), v0_5, v1);
		int v0_6 = v0_5 + v1;
		util.int16_to_buf(v3, v0_6, v2);
		System.arraycopy(((Object)arg15), 0, ((Object)v3), v0_6 + 2, v2);
		this.fill_head(this._cmd);
		this.fill_body(v3, v3.length);
		this.set_length();
		return this.get_buf();
	}
}


*/


//此TLV是用来交换登录授权用的
class tlv_t148 : public tlv_t
{
public:
	tlv_t148() {
		this->_cmd = 0x0148;
	}
	tlv_t148(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x0148;
		verify();
	}
	tlv_t148(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_148(string dstAppName, int32_t dwDstSsoVer, int32_t dwDstAppid, int32_t dwSubDstAppid, string dstAppVersion, string dstAppSign) {
		string buffer;


		int16data_to_buf(dstAppName, buffer);
		int32_to_buf(dwDstSsoVer, buffer);
		int32_to_buf(dwDstAppid, buffer);
		int32_to_buf(dwSubDstAppid, buffer);
		int16data_to_buf(dstAppVersion, buffer);
		int16data_to_buf(dstAppSign, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:
	void verify() {
		//跳过type 和  len
		this->_pos = 4;

		const char* base = this->_buf.data();

	}
private:
};