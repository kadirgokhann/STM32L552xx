
#include <stdint.h>


typedef struct {
	volatile uint16_t MODER[2];
	volatile uint16_t OTYPER[2];
	volatile uint16_t OSPEEDR[2];
	volatile uint16_t PUPDR[2];
	volatile uint16_t IDR[2];
	volatile uint16_t ODR[2];
	volatile uint16_t BSRR[2];
	volatile uint16_t LCKR[2];
	volatile uint16_t AFR[4];
	volatile uint16_t BRR[2];
	uint16_t RESERVED[2];
	volatile uint16_t SECCFGR[2];
} GPIO_TypeDef_16bit;




uint32_t wait_milisecond = 1000;
uint32_t wait_counter = 0;

#define RCC_AHB2ENR *((volatile uint32_t *) (0x40021000 + 0x4C))

#define GPIOA	((GPIO_TypeDef_16bit *) 0x42020000)
#define GPIOB	((GPIO_TypeDef_16bit *) 0x42020400)
#define GPIOC	((GPIO_TypeDef_16bit *) 0x42020800)

#define MAKE1(X,Y) (X|=(0x01<<Y))
#define MAKE0(X,Y) (X&= ~(0x01<<Y))


int main(void) {
	MAKE1(RCC_AHB2ENR,0); //Enable A port
	MAKE1(RCC_AHB2ENR,1); //Enable B port
	MAKE1(RCC_AHB2ENR,2); //Enable C port

	// RED  LED PA9
	// BLUE LED PB7
	// GREEN LED PC7

	// PIN PA-0


	// MODER
	// 00 Input Mode
	// 01 Output Mode
	// 10 Alternate Function
	// 11 Analog


	// Output mode for  RED  LED PA9
	MAKE0(GPIOA->MODER[1],3);
	MAKE1(GPIOA->MODER[1],2);

	// Output mode for  Blue  LED PB7
	MAKE0(GPIOB->MODER[0],15);
	MAKE1(GPIOB->MODER[0],14);

	// Output mode for  Green  LED PC7
	MAKE0(GPIOC->MODER[0],15);
	MAKE1(GPIOC->MODER[0],14);


	//------------------------------- PIN
	// Input mode for the PIN PA0
	MAKE0(GPIOA->MODER[0],1);
	MAKE0(GPIOA->MODER[0],0);


	// PUPDR
	// 00: No pull-up, pull-down
	// 01: Pull-up
	// 10: Pull-down
	// 11: Reserved



	// [I     I      I]
	//      input    3.3
	// Bu configurasyon da pull down'a ihtiyacım var neden
	// open drain'de 0 versin. Bosta kalınca sıfır versin diye
	// saga cekince calisiyor, sola cekince 0 geldiginden calismiyor
	//MAKE1(GPIOA->PUPDR[0],1);MAKE0(GPIOA->PUPDR[0],0);


	// [I     I      I]
	//      input    GND
	// Bu configurasyon da pull up'a ihtiyacım var
	// bu sekilde bosta open-drain'de kaldığımda
	// pull-up oldugu icin elektrik versin.
	// saga cekince gnd oldugundna calismiyor
	// sola cekince pull-up'dan dolayı 1 geliyor

	MAKE0(GPIOA->PUPDR[0],1);MAKE1(GPIOA->PUPDR[0],0);
	//--------------------


	while(1) {
		int index;

		if (GPIOA->IDR[0]&0x01){
			MAKE1(GPIOA->ODR[0],9);
			MAKE0(GPIOB->ODR[0],7);
			MAKE0(GPIOC->ODR[0],7);

			for(index=0;index<wait_milisecond*333;index++);

			__asm volatile("LDR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("ADD R12, 1");
			__asm volatile("STR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("LDR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("ADD R12, 1");
			__asm volatile("STR R12, [%0]" : :"r"(&wait_counter));

			MAKE0(GPIOA->ODR[0],9);
			MAKE1(GPIOB->ODR[0],7);
			MAKE0(GPIOC->ODR[0],7);
			if (!(GPIOA->IDR[0]&0x01)){
				MAKE0(GPIOA->ODR[0],9);
				MAKE0(GPIOB->ODR[0],7);
				MAKE0(GPIOC->ODR[0],7);
			}

			for(index=0;index<wait_milisecond*333;index++);
			__asm volatile("LDR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("ADD R12, 1");
			__asm volatile("STR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("STR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("LDR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("ADD R12, 1");
			__asm volatile("STR R12, [%0]" : :"r"(&wait_counter));

			MAKE0(GPIOA->ODR[0],9);
			MAKE0(GPIOB->ODR[0],7);
			MAKE1(GPIOC->ODR[0],7);
			if (!(GPIOA->IDR[0]&0x01)){
				MAKE0(GPIOA->ODR[0],9);
				MAKE0(GPIOB->ODR[0],7);
				MAKE0(GPIOC->ODR[0],7);
			}
			for(index=0;index<wait_milisecond*333;index++);
			__asm volatile("LDR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("ADD R12, 1");
			__asm volatile("STR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("STR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("LDR R12, [%0]" : :"r"(&wait_counter));
			__asm volatile("ADD R12, 1");
			__asm volatile("STR R12, [%0]" : :"r"(&wait_counter));

		}

		MAKE0(GPIOA->ODR[0],9);
		MAKE0(GPIOB->ODR[0],7);
		MAKE0(GPIOC->ODR[0],7);

	}
}
