#include "Define.h"

BEGIN_NAMESPACE

/*
 * drone PWM channel
 */
const int32_t ROLL_CHN = 0;
const int32_t PITCH_CHN = 1;
const int32_t THROTTLE_CHN = 2;
const int32_t YAW_CHN = 3;
const int32_t MODE_CHN = 6;
const int32_t HOME_CHN = 5;
const int32_t VISION_CHN = 4;

/*
 * gimbal PWM channel
 */
//int32_t THROTTLE_OUT = 0;
//int32_t ROLL_OUT  = 1;
//int32_t PITCH_OUT = 2;
//int32_t YAW_OUT = 3;
const int32_t GIMBAL_ROLL_OUT = 8;
const int32_t GIMBAL_PITCH_OUT = 9;
const int32_t GIMBAL_YAW_OUT = 10;
const int32_t GIMBAL_FOCUS_OUT = 11;

END_NAMESPACE