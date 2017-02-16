#include "DataConverter.h"

BEGIN_NAMESPACE

string Converter::ConvertFloat(const float &value)
{
	union conv
	{
		float f;
		char bytes[4];
	}c;

	c.f = value;

	return string(c.bytes, 4);
}

bool Converter::DecodeFloat(const string &str, float &f)
{
	if (str.size() != 4) {
		return false;
	}

	union conv
	{
		float f;
		char bytes[4];
	}c;

	for (int i = 0; i != 4; ++i)
		c.bytes[i] = str[i];

	f = c.f;

	return true;
}

string Converter::ConvertInt32(const int32_t &value)
{
	union conv
	{
		int32_t d;
		char bytes[4];
	}c;

	c.d = value;

	return string(c.bytes, 4);
}

bool Converter::DecodeInt32(const string &str, int32_t &d)
{
	if (str.size() != 4) {
		return false;
	}

	union conv
	{
		int32_t d;
		char bytes[4];
	}c;

	for (int i = 0; i != 4; ++i)
		c.bytes[i] = str[i];

	d = c.d;

	return true;
}

END_NAMESPACE