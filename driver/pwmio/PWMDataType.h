#ifndef PWMDATATYPE_H
#define PWMDATATYPE_H

#include "Define.h"

BEGIN_NAMESPACE
	
typedef struct PWMData
{
	float Throttle;
	float Roll;
	float Pitch;
	float Yaw;
	float EnableVision;
	float _n2;
	float _n3;
	float _n4;
} PWMData;
	
END_NAMESPACE

#endif