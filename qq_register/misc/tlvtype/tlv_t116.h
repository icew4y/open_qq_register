#pragma once
#include "tlv_t.h"

/*
 Tagindex: 278(0x0116)  -> ()
						Length: 14(0x000E)
						Value: 00 0A F7 FF 7C 00 01 04 00 01 5F 5E 10 E2

										_ver:0(0x0)
										mMiscBitmap:184024956(0x0AF7FF7C)
										mSubSigMap:66560(0x00010400)
										len:1(0x1)
												value:1600000226(0x5F5E10E2)
*/

class tlv_t116 : public tlv_t
{
public:
	tlv_t116() {
		_cmd = 0x116;
		_ver = 0;
	}
	string get_tlv_t116(int32_t mMiscBitmap, int32_t mSubSigMap, vector<int32_t>& _sub_appid_list) {
		string buffer;

		int8_to_buf(_ver, buffer);
		//mMiscBitmap 0x0AF7FF7C
		int32_to_buf(mMiscBitmap, buffer);
		//mSubSigMap 0x00010400
		int32_to_buf(mSubSigMap, buffer);

		int8_to_buf(_sub_appid_list.size(), buffer);
		for (int Index = 0; Index < _sub_appid_list.size() ; Index++)
		{
			int32_to_buf(_sub_appid_list[Index], buffer);
		}
		

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:
	int _ver;
};