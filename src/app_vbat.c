/*
 * Copyright (c) 2025
 * Regis Rousseau
 * Univ Lyon, INSA Lyon, Inria, CITI, EA3720
 * SPDX-License-Identifier: Apache-2.0
 */


//  ========== includes ====================================================================
#include "app_vbat.h"

//  ========== globals =====================================================================
// ADC buffer to store raw ADC readings
int32_t buf;

// ADC channel configuration obtained from the device tree
static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

// ADC sequence configuration to specify the ADC operation
static struct adc_sequence sequence = {
    .channels = 1,
	.buffer = &buf,
	.buffer_size = sizeof(buf),
};

//  ========== app_nrf52_vbat_init =========================================================
int8_t app_nrf52_vbat_init()
{
    int8_t ret;

    // verify if the ADC is ready for operation
    if (!adc_is_ready_dt(&adc_channel)) {
		printk("ADC is not ready. error: %d\n", ret);
		return 0;
	}

    // configure the ADC channel settings
    ret = adc_channel_setup_dt(&adc_channel);
	if (ret < 0) {
		printk("failed to set up ADC channel. error: %d\n", ret);
		return 0;
	}

    // initialize the ADC sequence for continuous or single readings
    ret = adc_sequence_init_dt(&adc_channel, &sequence);
	if (ret < 0) {
		printk("failed to initialize ADC sequence. error: %d\n", ret);
		return 0;
	}
    return 1;
}

//  ======== app_nrf52_get_vbat ============================================================
int16_t app_nrf52_get_vbat()
{
    int16_t percent = 0;

    // read sample from the ADC
    int8_t ret = adc_read(adc_channel.dev, &sequence);
    if (ret < 0 ) {        
	    printk("raw adc value is not up to date. error: %d\n", ret);
	    return 0;
    }
    printk("raw adc value: %d\n", buf);

    // convert raw ADC reading to voltage
    int32_t v_adc = (buf * ADC_FULL_SCALE_MV) / ADC_RESOLUTION;
    printk("convert voltage AIN1: %d mV\n", v_adc);

    // scale back to actual battery voltage using voltage divider
    int32_t v_bat = (v_adc * DIVIDER_RATIO_NUM) / DIVIDER_RATIO_DEN;
    printk("convert voltage BATT: %d mv\n", v_bat);

    // simple linear mapping
    float percent_f = 100.0f * (v_bat - BATTERY_MIN_VOLTAGE) / (BATTERY_MAX_VOLTAGE - BATTERY_MIN_VOLTAGE);
    if (percent_f < 0.0f) percent_f = 0.0f;
    if (percent_f > 100.0f) percent_f = 100.0f;

    percent = (int16_t)percent_f;
    return percent;
}
