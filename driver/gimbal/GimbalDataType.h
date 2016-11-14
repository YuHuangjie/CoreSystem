#ifndef GIMBALDATATYPE_H
#define GIMBALDATATYPE_H

#include "Define.h"

BEGIN_NAMESPACE

typedef struct GimbalData
{
	float Roll;
	float Pitch;
	float Yaw;
	float Focus;
	float _n1;
	float _n2;
	float _n3;
	float _n4;
} GimbalData;

END_NAMESPACE

#endif