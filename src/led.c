#include <stdio.h>
#include <stdint.h>
#include "led.h"

uint32_t *gpsel4 = 0xFE200010;
uint32_t *gpset1 = 0xFE200020;
uint32_t *gpclr1 = 0xFE20002C;


void led_init() {
	*gpsel4 = *gpsel4 & 0xFFFFFE3F;
	*gpsel4 = *gpsel4 | (1 << 6);
}

void led_on() {
	*gpset1 = (1 << 10);
}

void led_off() {
	*gpclr1 = (1 << 10);
}

void delay(unsigned int d) {
	unsigned int i, j;
	for (int i = 0; i < 0x7f; i++) {
		for (int j = 0; j < d; j++) {
			asm("nop");
		}
	}
}
