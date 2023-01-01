/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#define RCC_AHB2ENR *((volatile uint32_t *) 0x4002104C)


#define GPIOA_MODER *((volatile uint32_t *) 0x42020000)


#define GPIOA_ODR *((volatile uint32_t *) 0x42020014)


#include <stdint.h>

uint32_t wait_millisecond = 1000;
uint32_t wait_counter = 0;


int oldmain(){
	*((uint32_t*)(0x40021000 + 0x4C)) |= 0x01 << 1;

	*((uint32_t*)(0x42020400 + 0x08)) &= ~(0x03 << (7 * 2));
	*((uint32_t*)(0x42020400 + 0x08)) |= (0x01 << (7 * 2));

	*((uint32_t*)(0x42020400 + 0x04)) &= ~(0x01 << 7);

	*((uint32_t*)(0x42020400 + 0x0C)) &= ~(0x03 << (7 * 2));

	*((uint32_t*)(0x42020400 + 0x00)) &= ~(0x03 << (7 * 2));
	*((uint32_t*)(0x42020400 + 0x00)) |= (0x01 << (7 * 2));

	*((uint32_t*)(0x42020400 + 0x18)) |= (0x01 << 7);

	while(1) {

		volatile int index;

		*((uint32_t*)(0x42020400 + 0x18)) |= (0x01 << 7);

		for(index=0;index<wait_millisecond*333;index++);
		wait_counter = wait_counter + 1;

		*((uint32_t*)(0x42020400 + 0x18)) |= ((0x01 << 7) << 16);

		for(index=0;index<wait_millisecond*333;index++);
		wait_counter = wait_counter + 1;
	}
}

void init_led(){
	volatile int index;
	RCC_AHB2ENR |= 1;

	// because it takes 2 cycles to enable it.
	for(index=0;index<wait_millisecond*666;index++);
	wait_counter = wait_counter + 1;

    //00 00 00 00 00 00 10 00 00 00 00 00 00 00 00 00 = (1<<19)

	//10 10 10 11 11 11 11 11 11 11 11 11 11 11 11 11 = X
	//11 11 11 11 11 11 01 11 11 11 11 11 11 11 11 11 =~(1<<19) = Y
	//10 10 10 11 11 11 01 11 11 11 11 11 11 11 11 11 = X&Y

	GPIOA_MODER &= ~(1 << 19);
}

int main(void) {
	volatile int index;
	init_led();
	while (1){
		GPIOA_ODR |= (1 << 9);
		for(index=0;index<wait_millisecond*666;index++);
		wait_counter = wait_counter + 1;
		GPIOA_ODR &= ~(1 << 9);
		for(index=0;index<wait_millisecond*666;index++);
		wait_counter = wait_counter + 1;
	}


}
