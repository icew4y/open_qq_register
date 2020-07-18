#pragma once
#include "../deps/bufutil.h"
#include "../deps/context.h"
#include "../misc/tlvtype/tlv_t18.h"
#include "../misc/tlvtype/tlv_t1.h"
#include "../misc/tlvtype/tlv_t106.h"
#include "../misc/tlvtype/tlv_t116.h"
#include "../misc/tlvtype/tlv_t100.h"
#include "../misc/tlvtype/tlv_t107.h"
#include "../misc/tlvtype/tlv_t108.h"
#include "../misc/tlvtype/tlv_t142.h"
#include "../misc/tlvtype/tlv_t144.h"
#include "../misc/tlvtype/tlv_t145.h"
#include "../misc/tlvtype/tlv_t147.h"
#include "../misc/tlvtype/tlv_t154.h"
#include "../misc/tlvtype/tlv_t141.h"
#include "../misc/tlvtype/tlv_t8.h"
#include "../misc/tlvtype/tlv_t511.h"
#include "../misc/tlvtype/tlv_t187.h"
#include "../misc/tlvtype/tlv_t188.h"
#include "../misc/tlvtype/tlv_t191.h"
#include "../misc/tlvtype/tlv_t202.h"
#include "../misc/tlvtype/tlv_t177.h"
#include "../misc/tlvtype/tlv_t516.h"
#include "../misc/tlvtype/tlv_t521.h"
#include "../misc/tlvtype/tlv_t545.h"

using namespace bufutil;


#define UNIMPL_FUNCTION return NULL;
#define UNIMPL_FUNCTION_EMPTY return;

namespace packer {
	std::string packer_build_RegSubmitMobile(qq_ctx *ctx);
	std::string packer_build_RegSubmitMsgChk(qq_ctx* ctx);
	std::string packer_build_RegQueryClientSentMsgStatus(qq_ctx* ctx);
	std::string packer_build_RegGetAccount(qq_ctx* ctx);
	std::string packer_build_wtlogin_login(qq_ctx* ctx);
	std::string _test_packer_build_wtlogin_login(qq_ctx* ctx);
	std::string packer_build_wtlogin_login_exchange_loginauth(qq_ctx* ctx);
	std::string packer_build_sec_exchange_A2(qq_ctx* ctx);
	std::string packer_build_wtlogin_login_verify_captcha(qq_ctx* ctx);
	std::string packer_build_wtlogin_login_verify_captcha_quick(qq_ctx* ctx);
	std::string packer_build_ConfigService_ClientReq(qq_ctx* ctx);
}