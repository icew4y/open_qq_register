#include "tlv_t.h"

void tlv_t::fill_head()
{
	int16_to_buf(this->_cmd, this->_buf);
}

void tlv_t::fill_body(string& body)
{
	this->_body_len = body.length();
	fill_body_len(this->_body_len);
	string_to_buf(body, this->_buf);
}

string tlv_t::get_buf()
{
	return _buf;
}

void tlv_t::fill_body_len(int16_t len)
{
	int16_to_buf(this->_body_len, this->_buf);
}
