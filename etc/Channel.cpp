#include "Define.h"

BEGIN_NAMESPACE

/*
 * Input PWM channel
 */
int32_t THROTTLE_IN = 0;
int32_t ROLL_IN = 1;
int32_t PITCH_IN = 2;
int32_t YAW_IN = 3;
int32_t VISION_IN = 4;

/*
 * Output PWM channel
 */
int32_t THROTTLE_OUT = 0;
int32_t ROLL_OUT  = 1;
int32_t PITCH_OUT = 2;
int32_t YAW_OUT = 3;
int32_t GIMBAL_ROLL_OUT = 8;
int32_t GIMBAL_PITCH_OUT = 9;
int32_t GIMBAL_YAW_OUT = 10;
int32_t GIMBAL_FOCUS_OUT = 11;

END_NAMESPACE