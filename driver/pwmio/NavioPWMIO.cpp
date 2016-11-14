#include "NavioPWMIO.h"
#include <chrono>
#include <thread>
#include <iostream>

BEGIN_NAMESPACE
	
static PCA9685 *pwm = nullptr;
	
static const uint32_t InputGpio = 4;		// PPM input on Navio's 2.54 header
static const uint32_t SamplingRate = 5;	// microsecond (can be 1,2,4,5,10)
static const uint32_t SyncLength = 4000;	// Length of PPM sync pause
static const uint32_t ChannelsNumber = 8;	// Number of channels packed in PPM (typically 8 channels max)
static const uint32_t ServoFrequency=50;     // Servo control frequency
static const uint8_t outputEnablePin = RPI_GPIO_27;

static uint32_t PreviousTick = 0;
static uint32_t DeltaTime = 0;
static uint32_t CurrentChannel = 0;

static float *Channels = nullptr;	

NavioPWMIO::NavioPWMIO()
{
	Channels = new float[ChannelsNumber];
	// initialize all channels to 0
	for (int i = 0; i != ChannelsNumber; ++i) {
		Channels[i] = 0.0f;
	}	

}

NavioPWMIO::~NavioPWMIO()
{
	if (Channels != nullptr) {
		delete[] Channels;
		Channels = nullptr;
	}
	
	if (pwm != nullptr) {
		delete pwm;
		pwm = nullptr;
	}
	
	Stop();
}

void ppmOnEdge(int gpio, int level, uint32_t tick)
{
	if (level == 0) {
		DeltaTime = tick - PreviousTick;
		PreviousTick = tick;
		
		if (DeltaTime >= SyncLength) {
			// sync
			CurrentChannel = 0;
		}
		else if (CurrentChannel < ChannelsNumber) {
			Channels[CurrentChannel++] = DeltaTime;
		}
	}
}

void NavioPWMIO::Run(void)
{	
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
	Pin pin(outputEnablePin);
	if (pin.init()) {
		pin.setMode(Pin::GpioModeOutput);
		pin.write(0); /* drive Output Enable low */
	}
	else {
		std::cerr << "Output Enable not set. Are you root?" << std::endl;
		exit(-1);
	}
	
	pwm = new PCA9685();
	pwm->initialize();
	pwm->setFrequency(ServoFrequency); 
	
	gpioCfgClock(SamplingRate, PI_DEFAULT_CLK_PERIPHERAL, 0);	
	gpioInitialise();
	PreviousTick = gpioTick();
	gpioSetAlertFunc(InputGpio, ppmOnEdge);
}

void NavioPWMIO::Stop(void)
{
	gpioSetAlertFunc(InputGpio, nullptr);
	gpioTerminate();
}

float NavioPWMIO::GetTick(int32_t channel)
{
	/* 
	 * Navio provides a pwm intensity ranging from 1100 to 1900, roughly.
	 * Do a map to normalize this value to be between -1 and 1.
	 */
	if (channel < 0 && channel >= ChannelsNumber &&
		channel != THROTTLE_IN &&
		channel != ROLL_IN &&
		channel != PITCH_IN &&
		channel != YAW_IN &&
		channel != VISION_IN)
	{
			return 0.0f;
	}
	
	float ret = (Channels[channel] - 1500) / 500;
	
	return ret;
}

void NavioPWMIO::SetTick(int32_t channel, float tick)
{
	if (channel != THROTTLE_OUT &&
		channel != ROLL_OUT     && 
		channel != PITCH_OUT    &&
		channel != YAW_OUT		&&
		channel != GIMBAL_ROLL_OUT &&
		channel != GIMBAL_PITCH_OUT &&
		channel != GIMBAL_YAW_OUT &&
		channel != GIMBAL_FOCUS_OUT)
	{
			return;
	}
	
	if (tick <= -1 || tick >= 1) {
		tick = 0;
	}
	
	// Unnormalize
	tick = (tick * 500) + 1500;
	
	std::lock_guard<std::mutex> lock(pwmMutex);
	pwm->setPWMuS(channel + 3, tick);
	
	
	// debug
	std::cout << channel << " - " << tick << std::endl;
}
	
END_NAMESPACE