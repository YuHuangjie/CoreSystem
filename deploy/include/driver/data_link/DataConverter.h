#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include "Define.h"
#include <string>

using namespace std;

BEGIN_NAMESPACE

class Converter
{
public:
	// encode
	static string ConvertFloat(const float &);
	static string ConvertDouble(const double &);
	static string ConvertUint8(const uint8_t &);
	static string ConvertInt8(const int8_t &);
	static string ConvertUint16(const uint16_t &);
	static string ConvertInt16(const int16_t &);
	static string ConvertUint32(const uint32_t &);
	static string ConvertInt32(const int32_t &);

	// decode
	static bool DecodeFloat(const string &, float &);
	static bool DecodeDouble(const string &, double &);
	static bool DecodeUint8(const string &, uint8_t &);
	static bool DecodeInt8(const string &, int8_t &);
	static bool DecodeUint16(const string &, uint16_t &);
	static bool DecodeInt16(const string &, int16_t &);
	static bool DecodeUint32(const string &, uint32_t &);
	static bool DecodeInt32(const string &, int32_t &);
};

END_NAMESPACE

#endif