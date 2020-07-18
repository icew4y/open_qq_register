#pragma once
#include "tlv_t.h"
/*

 Tagindex: 296(0x0128)  -> (ÓÐguid)
										Length: 45(0x002D)
										Value: 00 00 
										00 
										01 
										00 
										
										01 00 00 00 
										00 08 
										4E 65 78 75 73 20 36 50 00 10 0C 93 EF C2 F8 A0 50 08 76 BD 1C C2 82 A3 BE 04 00 06 67 6F 6F 67 6C 65


byte[] v8_2 = new tlv_t128().get_tlv_128(t.U, t.V, t.W, t.Z, t.model_type, t.guid, t.P);

 t.U = 0;
		t.V = 0;
		t.W = 0;
		t.X = 0;
		t.Y = 0;
		t.Z = 0;


 public byte[] get_tlv_128(int arg7, int arg8, int arg9, int arg10, byte[] arg11, byte[] arg12, byte[] arg13) {
		if(arg11 == null) {
			arg11 = new byte[0];
		}

		if(arg12 == null) {
			arg12 = new byte[0];
		}

		if(arg13 == null) {
			arg13 = new byte[0];
		}

		int v0 = this.limit_len(arg11, 0x20);
		int v1 = this.limit_len(arg12, 16);
		int v2 = this.limit_len(arg13, 16);
		this._t128_body_len = v0 + 13 + v1 + 2 + v2;
		byte[] v3 = new byte[this._t128_body_len];
		util.int16_to_buf(v3, 0, 0);
		util.int8_to_buf(v3, 2, arg7);
		util.int8_to_buf(v3, 3, arg8);
		util.int8_to_buf(v3, 4, arg9);
		util.int32_to_buf(v3, 5, arg10);
		util.int16_to_buf(v3, 9, v0);
		System.arraycopy(((Object)arg11), 0, ((Object)v3), 11, v0);
		int v0_1 = v0 + 11;
		util.int16_to_buf(v3, v0_1, v1);
		int v0_2 = v0_1 + 2;
		System.arraycopy(((Object)arg12), 0, ((Object)v3), v0_2, v1);
		int v0_3 = v0_2 + v1;
		util.int16_to_buf(v3, v0_3, v2);
		System.arraycopy(((Object)arg13), 0, ((Object)v3), v0_3 + 2, v2);
		this.fill_head(this._cmd);
		this.fill_body(v3, this._t128_body_len);
		this.set_length();
		return this.get_buf();
	}
*/
class tlv_t128 : public tlv_t
{
public:
	tlv_t128() {
		this->_cmd = 0x128;
	}
	string get_tlv_128(int32_t guidsrcSigmap, string& model_type, string& guid, string& phone_brand) {
		string buffer;

		int16_to_buf(0, buffer);
		int8_to_buf(0, buffer);
		int8_to_buf(1, buffer);
		int8_to_buf(0, buffer);

		/*
		 t.Z |= t.X << 24 & 0xFF000000;
		t.Z |= t.Y << 8 & 0xFF00;
		t.guid = (byte[])v1_1.clone();
		t.B = (byte[])v1_1.clone();
		util.LOGI("guid src " + t.X, "");
		*/
		//guid src sigmap
		int32_to_buf(guidsrcSigmap/*t.Z*/, buffer);

		//model_type -> Nexus 6P
		int16data_to_buf(model_type, buffer);

		int16data_to_buf(guid, buffer);
		//phone_brand -> google
		int16data_to_buf(phone_brand, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};