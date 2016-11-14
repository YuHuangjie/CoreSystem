#ifndef DEFINE_H
#define DEFINE_H

#include <cstdint>
#include <string>

#define BEGIN_NAMESPACE namespace Au {
#define END_NAMESPACE }

BEGIN_NAMESPACE

const std::string CORE_ADDRESS = "192.168.0.230";	// server Listen all interfaces
const std::string VISION_ADDRESS = "192.168.0.236";	// client connect on LAN
const uint16_t CORE_PORT = 10000;

const std::string TEST_CORE_ADDRESS = "192.168.1.108";
const std::string TEST_VISION_ADDRESS = "192.168.1.104";

/*
 * global Input PWM channel
 */
extern int32_t THROTTLE_IN;
extern int32_t ROLL_IN;
extern int32_t PITCH_IN;
extern int32_t YAW_IN;
extern int32_t VISION_IN;

/*
 * global Output PWM channel
 */
extern int32_t THROTTLE_OUT;
extern int32_t ROLL_OUT;
extern int32_t PITCH_OUT;
extern int32_t YAW_OUT;
extern int32_t GIMBAL_ROLL_OUT;
extern int32_t GIMBAL_PITCH_OUT;
extern int32_t GIMBAL_YAW_OUT;
extern int32_t GIMBAL_FOCUS_OUT;

END_NAMESPACE

#endif
