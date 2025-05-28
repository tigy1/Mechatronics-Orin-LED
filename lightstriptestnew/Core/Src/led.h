/*
 * led.c
 *
 *  Created on: Nov 21, 2024
 *      Author: henryto
 */

#ifndef INC_LIGHT_STRIP
#define INC_LIGHT_STRIP
#include <stdio.h>
#include <stdint.h>


typedef struct rgb_struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgb_color;

typedef struct led_struct{
	uint16_t r[8];
	uint16_t g[8];
	uint16_t b[8];
} led;

#define LED_LOGICAL_ONE 57 //high
#define LED_LOGICAL_ZERO 28 //low

void reset_all_leds(led* leds, uint16_t number_leds);
void set_all_leds(led* leds, uint16_t number_leds);
void set_specific_led(led* leds, uint16_t led_position, rgb_color color, int brightness);
void all_specific_led(led* leds, uint16_t number_leds, rgb_color color, int brightness);

#endif
