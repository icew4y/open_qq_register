#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "../../deps/bufutil.h"
using namespace std;
using namespace bufutil;

class tlv_t
{
public:
	tlv_t() : _body_len(0),
			  _buf(""),
			  _cmd(0),
			  _pos(0){
		
	};

	tlv_t(string& data) {
		const char* base = data.data();
		int pos = 0;
		this->_cmd = buf_to_int16(base + pos); pos += 2;
		this->_body_len = buf_to_int16(base + pos); pos += 2;

		this->fill_head();
		string body = buf_to_string(base + pos, _body_len);
		this->fill_body(body);
		this->_pos = 0;
	}

	tlv_t(int16_t cmd, int16_t len, string value) {
		this->_cmd = cmd;
		this->fill_head();
		this->_body_len = len;
		this->fill_body(value);
		this->_pos = 0;
	}

	tlv_t(int16_t cmd) {
		this->_cmd = cmd;
	}
	~tlv_t() {};

	string get_buf();
protected:

	void fill_head();
	void fill_body(string& body);
	
private:
	void fill_body_len(int16_t len);

public:
	int _body_len;
	string _buf;
	int16_t _cmd;
	int _pos;
};
