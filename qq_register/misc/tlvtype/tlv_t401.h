#pragma once
#include "tlv_t.h"

/*


public byte[] c(byte[] arg5, byte[] arg6, byte[] arg7) {
		if(arg5 == null || arg6 == null || arg7 == null) {
			return new byte[16];
		}

		byte[] v0 = new byte[arg5.length + arg6.length + arg7.length];
		System.arraycopy(((Object)arg5), 0, ((Object)v0), 0, arg5.length);
		int v1 = arg5.length;
		System.arraycopy(((Object)arg6), 0, ((Object)v0), v1, arg6.length);
		System.arraycopy(((Object)arg7), 0, ((Object)v0), v1 + arg6.length, arg7.length);
		return MD5.toMD5Byte(v0);
	}



v16._dpwd = "gGkCuUMkRXOewbCT".getBytes();

//这里
v16._G = this.c(t.guid, v16._dpwd, v2.get_data());
*/

class tlv_t401 : public tlv_t
{
public:
	tlv_t401() {
		this->_cmd = 0x0401;
	}
	tlv_t401(string tlvbuf) : tlv_t(tlvbuf) {
		this->_cmd = 0x0401;
		verify();
	}
	tlv_t401(int16_t cmd, int16_t len, string value) :
		tlv_t(cmd, len, value)
	{
		verify();
	}
	string get_tlv_401(std::string guid, std::string dpwd, std::string tlv402) {
		string buffer;

		std::string temp = guid + dpwd + tlv402;
		std::string data = getmd5bytes(temp);
		string_to_buf(data, buffer);

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