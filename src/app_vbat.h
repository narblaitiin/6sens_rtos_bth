/*
 * Copyright (c) 2025
 * Regis Rousseau
 * Univ Lyon, INSA Lyon, Inria, CITI, EA3720
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef APP_VBAT_H
#define APP_VBAT_H

//  ========== includes ====================================================================
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <math.h>

//  ========== defines =====================================================================
// ADC characteristics (nRF52 SAADC)
#define ADC_REF_INTERNAL_MV         600     // 0.6 V internal reference
#define ADC_GAIN                    6       // using ADC_GAIN_1_6 -> 1/6
#define ADC_RESOLUTION              4096    // 12-bit

// effective full-scale voltage in mV
#define ADC_FULL_SCALE_MV   ((ADC_REF_INTERNAL_MV * ADC_GAIN))  // 3600 mV full scale

// voltage divider correction
#define DIVIDER_RATIO_NUM           4600    // (R4 + R5)
#define DIVIDER_RATIO_DEN           3600    // R5

//  ========== prototypes ==================================================================
int8_t app_adc_init();
int16_t app_get_vbat();

#endif /* APP_VBAT_H */