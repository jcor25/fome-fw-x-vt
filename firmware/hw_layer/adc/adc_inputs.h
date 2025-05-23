/**
 * @file	adc_inputs.h
 * @brief	Low level internal ADC code
 *
 * @date Jan 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2020
 */

#pragma once

#include "global.h"
#include "adc_math.h"

float getAnalogInputDividerCoefficient(adc_channel_e);

inline bool isAdcChannelValid(adc_channel_e hwChannel) {
	if (hwChannel <= EFI_ADC_NONE) {
		return false;
	} else if (hwChannel >= EFI_ADC_LAST_CHANNEL) {
		/* this should not happen!
		 * if we have enum out of range somewhere in settings
		 * that means something goes terribly wrong
		 * TODO: should we say something?
		 */
		return false;
	} else {
		return true;
	}
}

#if HAL_USE_ADC

enum class AdcChannelMode : char {
	Off,
	Slow,
	Fast
};

void updateSlowAdc(efitick_t nowNt);

// deprecated - migrate to 'getAdcChannelBrainPin'
int getAdcChannelPin(adc_channel_e hwChannel);

// deprecated - migrate to 'getAdcChannelBrainPin'
ioportid_t getAdcChannelPort(const char *msg, adc_channel_e hwChannel);

adc_channel_e getAdcChannel(brain_pin_e pin);
brain_pin_e getAdcChannelBrainPin(const char *msg, adc_channel_e hwChannel);

// wait until slow ADC readings are valid
void waitForSlowAdc();

int getAdcHardwareIndexByInternalIndex(int index);

int getSlowAdcValue(const char *msg, adc_channel_e index);
float getMCUInternalTemperature(void);

#define adcToVoltsDivided(adc, hwChannel) (adcToVolts(adc) * getAnalogInputDividerCoefficient(hwChannel))

#if !defined(GPT_FREQ_FAST) || !defined(GPT_PERIOD_FAST)
/**
 * 8000 RPM is 133Hz
 * If we want to sample MAP once per 5 degrees we need 133Hz * (360 / 5) = 9576Hz of fast ADC
 */
// todo: migrate to continuous ADC mode? probably not - we cannot afford the callback in
// todo: continuous mode. todo: look into our options
#define GPT_FREQ_FAST 100000   /* PWM clock frequency. I wonder what does this setting mean?  */
#define GPT_PERIOD_FAST 10  /* PWM period (in PWM ticks).    */
#endif /* GPT_FREQ_FAST GPT_PERIOD_FAST */

/* Depth of the conversion buffer, channels are sampled X times each.*/
#ifndef ADC_BUF_DEPTH_FAST
#define ADC_BUF_DEPTH_FAST      4
#endif

// This callback is called by the ADC driver when a new fast ADC sample is ready
void onFastAdcComplete(adcsample_t* samples);


using FastAdcToken = size_t;

FastAdcToken enableFastAdcChannel(const char* msg, adc_channel_e channel);
adcsample_t getFastAdc(FastAdcToken token);
const ADCConversionGroup* getKnockConversionGroup(uint8_t channelIdx);
void onKnockSamplingComplete();
#endif // HAL_USE_ADC
