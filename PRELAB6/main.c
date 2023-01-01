#include <stdint.h>

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
	volatile uint32_t BRR;
	uint32_t RESERVED;
	volatile uint32_t SECCFGR;
} GPIO_TypeDef;

typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMCR;
  volatile uint32_t DIER;
  volatile uint32_t SR;
  volatile uint32_t EGR;
  volatile uint32_t CCMR1;
  volatile uint32_t CCMR2;
  volatile uint32_t CCER;
  volatile uint32_t CNT;
  volatile uint32_t PSC;
  volatile uint32_t ARR;
  volatile uint32_t RCR;
  volatile uint32_t CCR1;
  volatile uint32_t CCR2;
  volatile uint32_t CCR3;
  volatile uint32_t CCR4;
  volatile uint32_t BDTR;
  volatile uint32_t DCR;
  volatile uint32_t DMAR;
  volatile uint32_t OR1;
  volatile uint32_t CCMR3;
  volatile uint32_t CCR5;
  volatile uint32_t CCR6;
  volatile uint32_t OR2;
  volatile uint32_t OR3;
} TIM_TypeDef;

uint32_t wait_microsecond = 10;
uint32_t wait_counter = 0;
uint32_t begin = 0;
uint32_t end=0;
uint32_t timer_value=0;
uint32_t time=0;




#define RCC_AHB2ENR *((volatile uint32_t *) (0x40021000 + 0x4C))
#define RCC_CR *((volatile uint32_t *) (0x40021000))
#define RCC_CFGR *((volatile uint32_t *) (0x40021000 + 0x008))
#define RCC_CSR *((volatile uint32_t *) (0x40021000 + 0x094))
#define RCC_APB1ENR1 *((volatile uint32_t *) (0x40021000 + 0x58))

#define GPIOA			((GPIO_TypeDef *)	0x42020000)
#define GPIOB			((GPIO_TypeDef *)	0x42020400)
#define GPIOC			((GPIO_TypeDef *)	0x42020800)
#define GPIOD			((GPIO_TypeDef *)	0x42020C00)
#define GPIOE			((GPIO_TypeDef *)	0x42021000)


#define TIM17           ((TIM_TypeDef *)	0x40014800)
#define TIM16           ((TIM_TypeDef *)	0x40014400)
#define TIM15           ((TIM_TypeDef *)	0x40014000)
#define TIM8            ((TIM_TypeDef *)	0x40013400)
#define TIM6            ((TIM_TypeDef *)	0x40001000)
#define TIM5            ((TIM_TypeDef *)	0x40000c00)
#define TIM4            ((TIM_TypeDef *)	0x40000800)
#define TIM3            ((TIM_TypeDef *)	0x40000400)
#define TIM2            ((TIM_TypeDef *)	0x40000000)


#define SET1(X,Y) (X|=(0x01<<Y))
#define SET0(X,Y) (X&=~(0x01<<Y))

void seven_display_init(){

	SET1(RCC_AHB2ENR,3); //Enable D port

	// MODER
	// 00 Input Mode
	// 01 Output Mode
	// 10 Alternate Function
	// 11 Analog

	SET0(GPIOD->MODER,15); //PD7 .
	SET1(GPIOD->MODER,14); //PD7 .

	SET0(GPIOD->MODER,13); //PD6 g
	SET1(GPIOD->MODER,12); //PD6 g

	SET0(GPIOD->MODER,11); //PD5 f
	SET1(GPIOD->MODER,10); //PD5 f

	SET0(GPIOD->MODER,9);  //PD4 e
	SET1(GPIOD->MODER,8);  //PD4 e

	SET0(GPIOD->MODER,7);  //PD3 d
	SET1(GPIOD->MODER,6);  //PD3 d

	SET0(GPIOD->MODER,5);  //PD2 C
	SET1(GPIOD->MODER,4);  //PD2 C

	SET0(GPIOD->MODER,3);  //PD1 b
	SET1(GPIOD->MODER,2);  //PD1 b

	SET0(GPIOD->MODER,1);  //PD0 a
	SET1(GPIOD->MODER,0);  //PD0 a

}
void display(uint32_t value){
	uint32_t arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	volatile int index=0;
	volatile int wait_milisecond=1000;
	//value=(uint32_t)(value/58);
	value=(uint32_t)(value/56);
	if (value>9){
	  GPIOD->ODR=0x80;
	  GPIOA->ODR&=0;
	}else{
	GPIOD->ODR=arr[value];

	GPIOA->ODR|=(1<<9);
	}
	for(index=0;index<wait_milisecond*111;index++);

	__asm volatile("LDR R12, [%0]" : :"r"(&wait_counter));
	__asm volatile("ADD R12, 1");
	__asm volatile("STR R12, [%0]" : :"r"(&wait_counter));
}



int main(void) {

	SET1(RCC_AHB2ENR,0); //Enable A port
	//SET1(RCC_AHB2ENR,1); //Enable B port
	//SET1(RCC_AHB2ENR,2); //Enable C port
	//SET1(RCC_AHB2ENR,3); //Enable D port
	SET1(RCC_AHB2ENR,4); //Enable E port
	//SET1(RCC_AHB2ENR,5); //Enable F port

	seven_display_init();
	//Initialize--------------------------------------------------------------
	//PE14 Triggers
	//PE15 Echo
	int trigger_pin=14;
	int echo_pin=15;
	//------------------------------------------------------------------------



	// MODER------------------------------------------------------------------
	// 00 Input Mode
	// 01 Output Mode
	// 10 Alternate Function
	// 11 Analog

	//PA9 output mode LED -> 01
	SET0(GPIOA->MODER,9*2+1);
	SET1(GPIOA->MODER,9*2);



	GPIOE->MODER &= (~(0x01 << (trigger_pin*2+1))); //PE14 output mode
	GPIOE->MODER |= (0x01 << (trigger_pin*2));


	GPIOE->MODER &= ~(0x01 << echo_pin*2+1); //PE15 input mode for Echo
	GPIOE->MODER &= ~(0x01 << echo_pin*2);
	//------------------------------------------------------------------------------------------





	// Timer Enablers:------------------------------------------------------------------


	// 5= TIM7, 4=TIM6, 3=TIM5, 2=TIM4, 1=TIM3, 0=TIM2
	RCC_APB1ENR1 |= 1 << 4;//TIM6x_CLK is enabled, running at 4MHz

	// 18=TIM17, 17=TIM16,16=TIM15, 13=TIM8, 11=TIM1
	//RCC_APB2ENR |= 1 << 17;
	//------------------------------------------------------------------------------------------


	TIM6->PSC = 4 - 1;//Set Prescaler
	TIM6->CR1 |= (0x01);//TIM6_CNT is enabled (clocked)
	SET0(GPIOE->ODR,14); // To be ensure output is 0

	while(1) {
		timer_value = TIM6->CNT;
		SET1(GPIOE->ODR,14);
		// Here, we sent high to trigger pin.
		while(TIM6->CNT - timer_value < wait_microsecond);
		SET0(GPIOE->ODR,14);

		// then, waiting for it begins to give echo
		while(!((GPIOE->IDR&(1<<15))>>15));

		// after it begins, we save the time it begins
		timer_value = TIM6->CNT;
		while (((GPIOE->IDR&(1<<15))>>15));
		time=TIM6->CNT-timer_value;
		display(time);
		//wait 60ms
		timer_value = TIM6->CNT;
		while(TIM6->CNT - timer_value < 60000);
		continue;
	}

}
