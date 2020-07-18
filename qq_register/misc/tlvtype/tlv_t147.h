#pragma once
#include "tlv_t.h"

/*

int v0_5 = l.e.GetStWithPasswd(arg14.getUin(), 16L, 0x2141060, v5, v7, true, v9, v10, v11);

Tagindex: 327(0x0147)  -> ()
						Length: 29(0x001D)
						Value: 00 00 00 10 00 05 38 2E 33 2E 30 00 10 A6 B7 45 BF 24 A2 C2 77 52 77 16 F6 F3 6E B6 8D



	PkgSigFromApkName ->

	public static byte[] getPkgSigFromApkName(Context arg4, String arg5) {
		try {
			PackageInfo v0_1 = arg4.getPackageManager().getPackageInfo(arg5, 0x40);
			return v0_1.signatures != null && v0_1.signatures.length > 0 && v0_1.signatures[0] != null ? MD5.toMD5Byte(v0_1.signatures[0].toByteArray()) : new byte[0];
		}
		catch(Throwable v0) {
			return new byte[0];
		}
	}
*/

class tlv_t147 : public tlv_t
{
public:
	tlv_t147() {
		this->_cmd = 0x147;
	}

	//PkgSigFromApkName -> A6 B7 45 BF 24 A2 C2 77 52 77 16 F6 F3 6E B6 8D
	//sappid/* 登录为16*/ //从QQ客户端交换安全中心A2为16//从安全客户端为0x1F2C6DEB
	string get_tlv_147(int32_t src_appid/* 登录为16*/, string& apk_version_str, string& PkgSigFromApkName) {
		string buffer;

		//
		int32_to_buf(src_appid, buffer);

		int16data_to_buf(apk_version_str, buffer);
		int16data_to_buf(PkgSigFromApkName, buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};