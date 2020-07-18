#pragma once
#include "../pch.h"
#include "../net/net.h"
#include "../deps/strutil.h"

namespace sms {

	enum TYPE
	{
		TUDOU = 1,
		ZHIJING,
		LANHU
	};
	class SMSInterface
	{

	public:
		SMSInterface() {}
		SMSInterface(TYPE type,std::string user, std::string pwd, std::string projectId)
			:_type(type), _projectId(projectId), _user(user), _pwd(pwd) {}


		bool login() {
			bool bresult = false;
			switch (_type)
			{
			case TUDOU: {
				_tokenstr = tudou_login_pla(_user, _pwd);
				if (!_tokenstr.empty()) bresult = true;
				break;
			}
			case ZHIJING: {
				_tokenstr = zhijing_login_pla(_user, _pwd);
				if (!_tokenstr.empty()) bresult = true;
				break;
			}
			case LANHU: {
				_tokenstr = lanhu_login_pla(_user, _pwd);
				if (!_tokenstr.empty()) bresult = true;
				break;
			}
			default:
				break;
			}
			return bresult;
		}

		bool getphone(std::string& phone) {
			bool bresult = false;
			switch (_type)
			{
			case TUDOU: {
				vector<string> pid_phone = tudou_get_phone_number(_projectId, _tokenstr);
				if (pid_phone.size() != 2) {
					_phone = pid_phone[0];
					_pid = pid_phone[1];
				}
				phone = _phone;
				if (!_phone.empty()) bresult = true;
				break;
			}
			case ZHIJING: {
				_phone = zhijing_get_phone_number(_projectId, _tokenstr);
				phone = _phone;
				if (!_phone.empty()) bresult = true;
				break;
			}
			case LANHU: {
				_phone = lanhu_get_phone_number(_projectId, _tokenstr);
				if (_phone == "relogin")
					login();
				phone = _phone;
				if (!_phone.empty()) bresult = true;
				break;
			}
			default:
				break;
			}
			return bresult;
		}

		bool getphone_msgcode(std::string& code) {
			bool bresult = false;
			switch (_type)
			{
			case TUDOU: {
				_code = tudou_get_phone_msgcode_repeately(_pid, _tokenstr, 5, 15);
				if (!_code.empty()) bresult = true;
				break;
			}
			case ZHIJING: {
				_code = zhijing_get_phone_msgcode_repeately(_phone, _projectId, _tokenstr, 5, 15);
				if (!_code.empty()) bresult = true;
				break;
			}
			case LANHU: {
				_code = lanhu_get_phone_msgcode_repeately(_phone, _projectId, _tokenstr, 5, 15);
				if (_code == "relogin")
					login();
				if (!_code.empty()) bresult = true;
				break;
			}
			default:
				break;
			}
			code = _code;
			return bresult;
		}

		bool sendmsgcode(std::string recvphone, std::string smscontent) {
			bool bresult = false;
			switch (_type)
			{
			case TUDOU: {
				bresult = tudou_send_phone_msgcode(_tokenstr, _pid, recvphone, smscontent);
				break;
			}
			case ZHIJING: {
				bresult = zhijing_send_phone_msgcode(_projectId, _phone, _tokenstr, recvphone, smscontent);
				break;
			}
			case LANHU: {
				std::string retcode = lanhu_send_phone_msgcode(_projectId, _phone, _tokenstr, recvphone, smscontent);
				if (retcode == "relogin")
					login();
				break;
			}
			default:
				break;
			}
			return bresult;
		}

		bool release_phone() {
			bool bresult = true;
			switch (_type)
			{
			case TUDOU: {
				tudou_release_phone_number(_tokenstr, _pid);
				break;
			}
			case ZHIJING: {
				zhijing_release_phone_number(_projectId, _tokenstr, _phone);
				break;
			}
			case LANHU: {
				std::string retcode = lanhu_release_phone_number(_projectId, _tokenstr, _phone);
				if (retcode == "relogin")
					login();
				break;
			}
			default:
				break;
			}
			return bresult;
		}
	protected:
	private:
		//ÍÁ¶¹
		std::string tudou_login_pla(std::string ApiName, std::string password);
		std::vector<string> tudou_get_phone_number(std::string project_id, std::string tokenstr);
		std::string tudou_get_phone_number_msgcode(std::string tokenstr, std::string pid);
		bool tudou_send_phone_msgcode(std::string tokenstr, std::string pid, string receiver, string smscontent);
		std::string tudou_get_phone_msgcode_repeately(std::string& pid, std::string& token, int r, int w);
		std::string tudou_release_phone_number(std::string tokenstr, std::string pid);

		//ÖÂ¾´
		std::string zhijing_login_pla(std::string user, std::string password);
		std::string zhijing_get_phone_number(std::string project_id, std::string tokenstr);
		std::string zhijing_get_phone_number_msgcode(std::string project_id, std::string tokenstr, std::string phone_number);
		bool zhijing_send_phone_msgcode(std::string project_id, std::string phone_number, std::string tokenstr, string receiver, string smscontent);
		std::string zhijing_get_phone_msgcode_repeately(std::string& phone, std::string& projectId, std::string& token, int r, int w);
		std::string zhijing_release_phone_number(std::string project_id, std::string tokenstr, std::string phone_number);


		//À¶ºü
		std::string lanhu_login_pla(std::string user, std::string password);
		std::string lanhu_get_phone_number(std::string project_id, std::string tokenstr);
		std::string lanhu_get_phone_number_msgcode(std::string project_id, std::string tokenstr, std::string phone_number);
		std::string lanhu_send_phone_msgcode(std::string project_id, std::string phone_number, std::string tokenstr, string receiver, string smscontent);
		bool lanhu_get_send_phone_msgcode_result(std::string project_id, std::string phone_number, std::string tokenstrt);
		std::string lanhu_get_phone_msgcode_repeately(std::string& phone, std::string& projectId, std::string& token, int r, int w);
		std::string lanhu_release_phone_number(std::string project_id, std::string tokenstr, std::string phone_number);
	private:
		TYPE _type;
		std::string _projectId, _user, _pwd;
		std::string _tokenstr;
		std::string _phone;
		std::string _code;
		std::string  _pid;
	};
	
}