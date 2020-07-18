#pragma once
#include "../deps/pch.h"
#include "../deps/context.h"
#include "../deps/bufutil.h"
#include "../deps/strutil.h"
#include "../misc/web_ecdh.h"

using namespace bufutil;
namespace resolver {
	int resolve_register_body(qq_ctx* ctx, string& body);
	int resolve_0530_body(qq_ctx* ctx, string& body);
	void resolve_tlv119(qq_ctx* ctx, const std::string& data);
	void resolve_token_tlv119(qq_ctx* ctx, const std::string& data);
	void resolve_tlv169(qq_ctx* ctx, const std::string& data);
	void resolve_respone_tlv_data(qq_ctx* ctx, const std::string& data, bool isHaveCMD);
	void resolve_respone_token_tlv_data(qq_ctx* ctx, const std::string& data, bool isHaveCMD);
	int resolve_respone_embedd_body(qq_ctx* ctx, string& body);
	int resolve_respone_embedd_tokenbody(qq_ctx* ctx, string& body);
	int resolve_respone_body(qq_ctx* ctx, string& body);
	int resolve_pack(qq_ctx* ctx, std::string& data);
}
