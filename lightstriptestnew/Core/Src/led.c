/*
 * led.c
 *
 *  Created on: Nov 21, 2024
 *      Author: henryto
 */

#include "led.h"
#include <math.h>

//function to reset all LEDS
void reset_all_leds(led* leds, uint16_t number_leds){
	for(int i = 0; i < number_leds; i++){
		for(int j = 0; j < 8; j++){
			(leds + i) -> r[j] = LED_LOGICAL_ZERO;
			(leds + i) -> g[j] = LED_LOGICAL_ZERO;
			(leds + i) -> b[j] = LED_LOGICAL_ZERO;
		}
	}
}

//function to set white color to all LEDS
void set_all_leds(led* leds, uint16_t number_leds){
	for(int i = 0; i < number_leds; i++){
		for(int j = 0; j < 8; j++){
			(leds + i) -> r[j] = LED_LOGICAL_ONE;
			(leds + i) -> g[j] = LED_LOGICAL_ONE;
			(leds + i) -> b[j] = LED_LOGICAL_ONE;
		}
	}
}

//function to set a specific color to a particular LED & set brightness 0-44
void set_specific_led(led* leds, uint16_t led_position, rgb_color color, int brightness){
	if(brightness > 44){
		brightness = 44;
	}

	float angle = 89-brightness; //degrees
	angle *= M_PI/180; //radians
	color.r /= tan(angle);
	color.g /= tan(angle);
	color.b /= tan(angle);

	for(int j = 0; j < 8; j++){
		if(color.r & 0x1 << j){
			(leds + led_position) ->g[7-j] = LED_LOGICAL_ONE;
		}
		else{
			(leds + led_position) ->g[7-j] = LED_LOGICAL_ZERO;
		}
		if(color.g & 0x1 << j){
			(leds + led_position) ->r[7-j] = LED_LOGICAL_ONE;
		}
		else{
			(leds + led_position) ->r[7-j] = LED_LOGICAL_ZERO;
		}
		if(color.b & 0x1 << j){
			(leds + led_position) ->b[7-j] = LED_LOGICAL_ONE;			}
		else{
			(leds + led_position) ->b[7-j] = LED_LOGICAL_ZERO;
		}
	}
}

void all_specific_led(led* leds, uint16_t number_leds, rgb_color color, int brightness){
	if(brightness > 44){
		brightness = 44;
	}

	float angle = 89-brightness; //degrees
	angle *= M_PI/180; //radians
	color.r /= tan(angle);
	color.g /= tan(angle);
	color.b /= tan(angle);

	for(int i = 0; i < number_leds; i++){ //*****set to how many leds
		for(int j = 0; j < 8; j++){
			if(color.r & 0x1 << j){
				(leds + i) -> g[7-j] = LED_LOGICAL_ONE;
			}
			else{
				(leds + i) -> g[7-j] = LED_LOGICAL_ZERO;
			}
			if(color.g & 0x1 << j){
				(leds + i) -> r[7-j] = LED_LOGICAL_ONE;
			}
			else{
				(leds + i) -> r[7-j] = LED_LOGICAL_ZERO;
			}
			if(color.b & 0x1 << j){
				(leds + i) -> b[7-j] = LED_LOGICAL_ONE;
			}
			else{
				(leds + i) -> b[7-j] = LED_LOGICAL_ZERO;
			}
		}
	}
}

void chase_pattern_LED(led* leds, uint16_t number_leds, rgb_color color, int brightness){
  rgb_color zeroRGB = {0, 0, 0};
  for(int alt = 0; alt < 3; alt++){ //switches odd & even pattern
	  for(int i = 0; i < number_leds; i++){
		  if((i + alt) % 3 == 0){ //even & odd leds are diff color & alternate
			  set_specific_led(leds, i, color, brightness);
		  }
		  else{
			  set_specific_led(leds, i, zeroRGB, brightness);
		  }
	  }
	  HAL_Delay(100);
  }
}

