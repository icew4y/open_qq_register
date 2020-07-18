#include "sms_plaform.h"
#include "json/allocator.h"
#include "json/reader.h"

static void split(const string& s, vector<string>& tokens, const string& delimiters = " ")
{
	string::size_type lastPos = s.find_first_not_of(delimiters, 0);
	string::size_type pos = s.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos) {
		tokens.push_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
}

std::string sms::SMSInterface::tudou_login_pla(std::string ApiName, std::string password) {
	std::string tokenstr;
	std::string url;
	url += "http://api.huanyinglu.com:9005/yhapi.ashx?act=login&ApiName=" + ApiName + "&PassWord=" + password;
	std::string result = net::http_get(url, "", NULL, "", false, true, false);
	std::vector<std::string> tokens;
	if (result.find("|") != string::npos) {
		split(result, tokens, std::string("|"));
		if (tokens[0] == "1") {
			tokenstr = tokens[1];
		}
	}


	return tokenstr;
}

std::vector<string> sms::SMSInterface::tudou_get_phone_number(std::string project_id, std::string tokenstr) {
	std::vector<string>  pid_phone;
	std::string url;
	url += "http://api.huanyinglu.com:9005/yhapi.ashx?act=getPhone&token=" + tokenstr + "&iid=" + project_id + "&did=&operator=&provi=&city=&mobile=";
	std::string result = net::http_get(url, "", NULL, "", false, true, false);
	result = UTF8ToGB(result.c_str());

	std::vector<std::string> tokens;
	split(result, tokens, std::string("|"));
	if (tokens[0] == "1") {
		pid_phone.push_back(tokens[1]);
		pid_phone.push_back(tokens[4]);
	}

	return pid_phone;
}


std::string sms::SMSInterface::tudou_get_phone_number_msgcode(std::string tokenstr, std::string pid) {
	std::string msgcode;
	std::string url;
	url += "http://api.huanyinglu.com:9005/yhapi.ashx?act=getPhoneCode&token=" +tokenstr + "&pid=" + pid;
	std::string result = net::http_get(url, "", NULL, "", false, true, false);
	result = UTF8ToGB(result.c_str());
	std::vector<std::string> tokens;
	split(result, tokens, std::string("|"));
	if (tokens[0] == "1") {
		msgcode = tokens[1];
	}

	return msgcode;
}


bool sms::SMSInterface::tudou_send_phone_msgcode(std::string tokenstr, std::string pid, string receiver, string smscontent) {
	string result;
	bool rc = false;
	std::string url;
	url += "http://api.huanyinglu.com:9005/yhapi.ashx?act=sendCode&token=" + tokenstr + "&pid=" + pid + "&receiver=" + receiver + "&smscontent=" + smscontent;
	result = net::http_get(url, "", NULL, "", false, true, false);
	result = UTF8ToGB(result.c_str());
	std::vector<std::string> tokens;
	split(result, tokens, std::string("|"));
	if (tokens[0] == "1") {
		rc = true;
	}
	else {
		printf("发送短信失败:%s", tokens[1].c_str());
	}

	return rc;
}


std::string sms::SMSInterface::tudou_get_phone_msgcode_repeately(std::string& pid, std::string& token, int r, int w)
{


	int repeat = r, waitsec = w;
	std::string code;
	do
	{
		code = tudou_get_phone_number_msgcode(token, pid);
		if (code != "")
			break;

		std::this_thread::sleep_for(std::chrono::seconds(waitsec));
		repeat--;
	} while (repeat > 0);
	return code;
}



std::string sms::SMSInterface::tudou_release_phone_number( std::string tokenstr, std::string pid) {
	std::string rc;
	std::string url;
	url += "http://api.huanyinglu.com:9005/yhapi.ashx?act=setRel&token=" + tokenstr + "&pid=" + pid;
	std::string result = net::http_get(url, "", NULL, "", false, true, false);

	return rc;
}


std::string sms::SMSInterface::zhijing_login_pla(std::string user, std::string password) {
	std::string tokenstr;
	std::string url;
	url += "http://api.zhijing888.com/Login/?username=" + user + "&password=" + password;
	std::string result = net::http_get(url, "", NULL, "", false, true, false);
	std::vector<std::string> tokens;
	split(result, tokens, std::string("|"));
	if (tokens[0] == "1") {
		tokenstr = tokens[1];
	}

	return tokenstr;
}

std::string sms::SMSInterface::zhijing_get_phone_number(std::string project_id, std::string tokenstr) {
	std::string phone;
	std::string url;
	std::string header = "User-Agent:PostmanRuntime/7.24.1\r\nAccept:*/*\r\nAccept-Encoding:gzip, deflate, br";
	url += "http://api.zhijing888.com/GetPhone/?id=" + project_id + "&token=" + tokenstr;
	std::string result = net::http_get(url, header, NULL, "", false, true, false);
	result = UTF8ToGB(result.c_str());

	std::vector<std::string> tokens;
	split(result, tokens, std::string("|"));
	if (tokens[0] == "1") {
		phone = tokens[1];
	}

	return phone;
}


std::string sms::SMSInterface::zhijing_get_phone_number_msgcode(std::string project_id, std::string tokenstr, std::string phone_number) {
	std::string msgcode;
	std::string url;
	url += "http://api.zhijing888.com/GetMsg/?id=" + project_id + "&phone=" + phone_number + "&token=" +tokenstr;
	std::string result = net::http_get(url, "", NULL, "", false, true, false);
	result = UTF8ToGB(result.c_str());
	std::vector<std::string> tokens;
	split(result, tokens, std::string("|"));
	if (tokens[0] == "1") {
		msgcode = tokens[1];
	}

	return msgcode;
}


bool sms::SMSInterface::zhijing_send_phone_msgcode(std::string project_id, std::string phone_number, std::string tokenstr, string receiver, string smscontent) {
	string result;
	bool rc = false;
	std::string url;
	url += "http://api.zhijing888.com/Sendmsg/?id=" + project_id  + "&phone=" + phone_number + "&send=" + receiver + "&content=" + smscontent + "&token=" + tokenstr;
	result = net::http_get(url, "", NULL, "", false, true, false);
	result = UTF8ToGB(result.c_str());
	std::vector<std::string> tokens;
	split(result, tokens, std::string("|"));
	if (tokens[0] == "1") {
		rc = true;
	}
	else {
		printf("发送短信失败:%s", tokens[1].c_str());
	}

	return rc;
}

std::string sms::SMSInterface::zhijing_get_phone_msgcode_repeately(std::string& phone, std::string& projectId, std::string& token, int r, int w)
{


	int repeat = r, waitsec = w;
	std::string code;
	do
	{
		code = zhijing_get_phone_number_msgcode(projectId, token, phone);
		if (code != "")
			break;

		std::this_thread::sleep_for(std::chrono::seconds(waitsec));
		repeat--;
	} while (repeat > 0);
	return code;
}



std::string sms::SMSInterface::zhijing_release_phone_number(std::string project_id, std::string tokenstr, std::string phone_number) {
	std::string rc;
	std::string url;
	url += "http://api.zhijing888.com/Cancel/?id=" + project_id + "&phone=" + phone_number + "&token=" + tokenstr;
	std::string result = net::http_get(url, "", NULL, "", false, true, false);
	std::vector<std::string> tokens;
	split(result, tokens, std::string("|"));
	if (tokens[0] == "1") {
		rc = tokens[1];
	}

	return rc;
}


std::string sms::SMSInterface::lanhu_login_pla(std::string user, std::string password) {
	std::string tokenstr;
	std::string url;
	url += "http://xiangjiuer.cn/sms/api/login?username=" + user + "&password=" + password;
	std::string result = net::http_get(url, "", NULL, "", false, true, false);
	//返回样例：{"msg":"success","code":0,"expire":604800,"token":"xxxxxxxxxxx"}
	
	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	bool ok = reader->parse(result.data(), result.data() + result.length(), &root, &errs);
	if (ok && errs.size() == 0)
	{
		int32_t code = root["code"].asInt();
		if (code == 0) {
			tokenstr = root["token"].asString();
		}
	}

	return tokenstr;
}

std::string sms::SMSInterface::lanhu_get_phone_number(std::string project_id, std::string tokenstr) {
	std::string phone;
	std::string url;
	std::string header = "User-Agent:PostmanRuntime/7.24.1\r\nAccept:*/*\r\nAccept-Encoding:gzip, deflate, br";
	url += "http://xiangjiuer.cn/sms/api/getPhone?token=" + tokenstr + "&sid=" + project_id;
	std::string result = net::http_get(url, header, NULL, "", false, true, false);
	result = UTF8ToGB(result.c_str());

	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	bool ok = reader->parse(result.data(), result.data() + result.length(), &root, &errs);
	if (ok && errs.size() == 0)
	{
		int32_t code = root["code"].asInt();
		if (code == 0) {
			phone = root["phone"].asString();
		}else if (code  == 401)
		{
			return "relogin";
		}
	}

	return phone;
}


std::string sms::SMSInterface::lanhu_get_phone_number_msgcode(std::string project_id, std::string tokenstr, std::string phone_number) {
	std::string msgcode;
	std::string url;
	url += "http://xiangjiuer.cn/sms/api/getMessage?token=" + tokenstr + "&sid=" + project_id + "&phone=" + phone_number;
	std::string result = net::http_get(url, "", NULL, "", false, true, false);
	result = UTF8ToGB(result.c_str());
	
	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	bool ok = reader->parse(result.data(), result.data() + result.length(), &root, &errs);
	if (ok && errs.size() == 0)
	{
		//返回样例：{"msg":"success","code":0,"sms":"您的短信为10083"} 
		int32_t code = root["code"].asInt();
		if (code == 0) {
			msgcode = root["sms"].asString();
		}
		else if (code == 401)
		{
			return "relogin";
		}
	}

	return msgcode;
}


std::string sms::SMSInterface::lanhu_send_phone_msgcode(std::string project_id, std::string phone_number, std::string tokenstr, string receiver, string smscontent) {
	string result;
	bool rc = false;
	std::string url;
	url += "http://xiangjiuer.cn/sms/api/sendMessage?token=" + tokenstr + "&sid=" + project_id + "&phone=" + phone_number + "&content=" + smscontent;
	result = net::http_get(url, "", NULL, "", false, true, false);
	result = UTF8ToGB(result.c_str());

	//返回列子：{"msg":"success","code":0}
	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	bool ok = reader->parse(result.data(), result.data() + result.length(), &root, &errs);
	if (ok && errs.size() == 0)
	{
		int32_t code = root["code"].asInt();
		if (code == 0) {
			result = root["msg"].asString();
			rc = true;
		}
		else if (code == 401)
		{
			return "relogin";
		}
	}

	return "";
}


bool sms::SMSInterface::lanhu_get_send_phone_msgcode_result(std::string project_id, std::string phone_number, std::string tokenstr) {
	string result;
	bool rc = false;
	std::string url;
	url += "http://xiangjiuer.cn/sms/api/getSendMsgStatus?token=" + tokenstr + "&sid=" + project_id  + "&phone=" + phone_number;
	result = net::http_get(url, "", NULL, "", false, true, false);
	result = UTF8ToGB(result.c_str());

	//返回列子：{"msg":"success","code":0}
	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	bool ok = reader->parse(result.data(), result.data() + result.length(), &root, &errs);
	if (ok && errs.size() == 0)
	{
		//返回样例：{"msg":"success","code":0,"sms":"您的短信为10083"} 
		int32_t code = root["code"].asInt();
		if (code == 0) {
			result = root["msg"].asString();
			rc = true;
		}
		else if (code == 401)
		{
			return "relogin";
		}
	}

	return rc;
}

std::string sms::SMSInterface::lanhu_get_phone_msgcode_repeately(std::string& phone, std::string& projectId, std::string& token, int r, int w)
{


	int repeat = r, waitsec = w;
	std::string code;
	do
	{
		code = lanhu_get_phone_number_msgcode(projectId, token, phone);
		if (code != "")
			break;

		std::this_thread::sleep_for(std::chrono::seconds(waitsec));
		repeat--;
	} while (repeat > 0);
	return code;
}





std::string sms::SMSInterface::lanhu_release_phone_number(std::string project_id, std::string tokenstr, std::string phone_number) {
	std::string rc;
	std::string url;
	url += "http://xiangjiuer.cn/sms/api/cancelRecv?token=" + tokenstr + "&sid=" + project_id  + "&phone=" + phone_number;
	std::string result = net::http_get(url, "", NULL, "", false, true, false);
	
	//返回列子：{"msg":"success","code":0}
	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	bool ok = reader->parse(result.data(), result.data() + result.length(), &root, &errs);
	if (ok && errs.size() == 0)
	{
		//返回样例：{"msg":"success","code":0,"sms":"您的短信为10083"} 
		int32_t code = root["code"].asInt();
		if (code == 0) {
			result = root["msg"].asString();
			rc = true;
		}
		else if (code == 401)
		{
			return "relogin";
		}
	}
	return "";
}