#include <stdint.h>
#define __IO volatile

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

typedef struct{
	__IO uint32_t ISER[16];
	__IO uint32_t ICER[16];
	__IO uint32_t ISPR[16];
	__IO uint32_t ICPR[16];
	__IO uint32_t IABR[16];
	__IO uint32_t ITNS[16];
	__IO uint32_t reserved[120];
} NVIC_Type;


typedef struct{
	__IO uint32_t ICER[16];
} ICER_Type;

uint32_t wait_microsecond = 10;
uint32_t wait_counter = 0;
uint32_t begin = 0;
uint32_t begin4 = 0;
uint32_t begin5 = 0;
uint32_t begin6 = 0;
uint32_t begin7 = 0;
uint32_t end=0;
uint32_t timer_value=0;
uint32_t time=0;




#define RCC_AHB2ENR *((volatile uint32_t *) (0x40021000 + 0x4C))
#define RCC_CR *((volatile uint32_t *) (0x40021000))
#define RCC_CFGR *((volatile uint32_t *) (0x40021000 + 0x008))
#define RCC_CSR *((volatile uint32_t *) (0x40021000 + 0x094))
#define RCC_APB1ENR1 *((volatile uint32_t *) (0x40021000 + 0x58))


#define NVIC			((NVIC_Type *) 		0xE000E100)
#define CLOSE			((ICER_Type *) 		0xE000E180)
#define GPIOA			((GPIO_TypeDef *)	0x42020000)
#define GPIOB			((GPIO_TypeDef *)	0x42020400)
#define GPIOC			((GPIO_TypeDef *)	0x42020800)
#define GPIOD			((GPIO_TypeDef *)	0x42020C00)
#define GPIOE			((GPIO_TypeDef *)	0x42021000)


#define TIM17           ((TIM_TypeDef *)	0x40014800)
#define TIM16           ((TIM_TypeDef *)	0x40014400)
#define TIM15           ((TIM_TypeDef *)	0x40014000)
#define TIM8            ((TIM_TypeDef *)	0x40013400)
#define TIM7     		((TIM_TypeDef *)    0x40001400)
#define TIM6            ((TIM_TypeDef *)	0x40001000)
#define TIM5            ((TIM_TypeDef *)	0x40000C00)
#define TIM4            ((TIM_TypeDef *)	0x40000800)
#define TIM3            ((TIM_TypeDef *)	0x40000400)
#define TIM2            ((TIM_TypeDef *)	0x40000000)


#define SET1(X,Y) (X|=(0x01<<Y))
#define SET0(X,Y) (X&=(~(0x01<<Y)))

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

void   TIM7_IRQHandler(void){
	//PE11=> RED

	TIM7->SR=0;
	if (begin7==0){
			SET1(GPIOE->ODR,11);
			begin7=1;
	}else if(begin7==1){
		SET0(GPIOE->ODR,11);
		begin7=0;
	}


}



void   TIM6_IRQHandler(void){
	//PE12=> RED

	TIM6->SR=0;
	if (begin6==0){
			SET1(GPIOE->ODR,12);
			begin6=1;
	}else if(begin6==1){
		SET0(GPIOE->ODR,12);
		begin6=0;
	}


}
void   TIM5_IRQHandler(void){
	//PE11=>GREEN
	TIM5->SR=0;
	if (begin5==0){
			SET1(GPIOE->ODR,11);
			begin5=1;
	}else  if(begin5==1){
		SET0(GPIOE->ODR,11);
		begin5=0;
	}


}
void   TIM4_IRQHandler(void){
	//PE_15=>BLUE
	TIM4->SR=0;
	if (begin4==0){
			SET1(GPIOE->ODR,15);
			begin4=1;
	}else if(begin4==1){
		SET0(GPIOE->ODR,15);
		begin4=0;
	}

}
void   TIM3_IRQHandler(void){
	// Color
	TIM3->SR=0;
	if (begin==0){  //None
		begin6=-1;  //12
		begin7=-1;   //11
		begin4=-1; //15
		begin=1;
	}
	else if(begin==1){  //White
		begin6=0;
		begin7=0;
		begin4=0;
		begin=2;
	}
	else if(begin==2){ //Cyan
		begin6=-1;
		SET1(GPIOE->ODR,12);
		begin7=0;
		begin4=0;
		begin=3;

	}
	else if(begin==3){ //Mageta
		begin6=1;
		begin7=-1;
		SET1(GPIOE->ODR,11);
		begin4=1;
		begin=4;

	}
	else if(begin==4){ //Blue
		begin6=-1;
		SET1(GPIOE->ODR,12);
		begin7=-1;
		SET1(GPIOE->ODR,11);
		begin4=1;
		begin=5;
	}
	else if(begin==5){ //Yellow
		begin6=1;
		begin7=1;
		begin4=-1;
		SET1(GPIOE->ODR,15);
		begin=6;

	}
	else if(begin==6){ //Green
		begin6=-1;
		SET1(GPIOE->ODR,12);
		begin7=1;
		begin4=-1;
		SET1(GPIOE->ODR,15);
		begin=7;

	}
	else if(begin==7){ //Green
		begin6=1;
		begin7=-1;
		SET1(GPIOE->ODR,11);
		begin4=-1;
		SET1(GPIOE->ODR,15);
		begin=0;

	}
}



void __enable_irq(void){
	__asm volatile("MOV R0, #0");
	__asm volatile("MSR PRIMASK, R0");
}

void __disable_irq(void){
	__asm volatile("MOV R0, #1");
	__asm volatile("MSR PRIMASK, R0");
}



int main(void) {

	//PE_15=>BLUE   tim4
	//PE11=>GRENN   tim5
	//PE12=> RED   tim6
	SET1(RCC_AHB2ENR,4); //Enable E port

	//PE15 output mode LED -> 01
	SET0(GPIOE->MODER,(15*2+1));
	SET1(GPIOE->MODER,(15*2));

	//PE11 output mode LED -> 01
	SET0(GPIOE->MODER,(11*2+1));
	SET1(GPIOE->MODER,(11*2));

	//PE12 output mode LED -> 01
	SET0(GPIOE->MODER,(12*2+1));
	SET1(GPIOE->MODER,(12*2));

	GPIOE->ODR|=0xffffffff;

	//------------------------------------------------------------------------------------------

	// Timer Enablers:------------------------------------------------------------------


	// 5= TIM7, 4=TIM6, 3=TIM5, 2=TIM4, 1=TIM3, 0=TIM2
	RCC_APB1ENR1 |= 1 << 5;//TIM6x_CLK is enabled, running at 4MHz
	RCC_APB1ENR1 |= 1 << 4;//TIM6x_CLK is enabled, running at 4MHz
	RCC_APB1ENR1 |= 1 << 3;//TIM5x_CLK is enabled, running at 4MHz
	RCC_APB1ENR1 |= 1 << 2;//TIM4x_CLK is enabled, running at 4MHz
	RCC_APB1ENR1 |= 1 << 1;//TIM3x_CLK is enabled, running at 4MHz
	//------------------------------------------------------------------------------------------

	TIM7->DIER|=0x01;
	TIM6->DIER|=0x01; //Enable update interrupt
	TIM5->DIER|=0x01; //Enable update interrupt
	TIM4->DIER|=0x01; //Enable update interrupt
	TIM3->DIER|=0x01; //Enable update interrupt

	TIM7->EGR|=1;
	TIM6->EGR|=1;
	TIM5->EGR|=1;
	TIM4->EGR|=1;
	TIM3->EGR|=1;

	TIM7->CR1 &= ~(1<<1);
	TIM6->CR1 &= ~(1<<1);
	TIM5->CR1 &= ~(1<<1);
	TIM4->CR1 &= ~(1<<1);
	TIM3->CR1 &= ~(1<<1);

	TIM7->CR1 |=1<<2;
	TIM6->CR1 |=1<<2;
	TIM5->CR1 |=1<<2;
	TIM4->CR1 |=1<<2;
	TIM3->CR1 |=1<<2;

	TIM7->PSC = 4000 - 1;//Set Prescaler
	TIM7->CR1 |= (0x01);//TIM6_CNT is enabled (clocked)

	TIM6->PSC = 4000 - 1;//Set Prescaler
	TIM6->CR1 |= (0x01);//TIM6_CNT is enabled (clocked)


	TIM5->PSC = 4000 - 1;//Set Prescaler
	TIM5->CR1 |= (0x01);//TIM5_CNT is enabled (clocked)


	TIM4->PSC = 4000 - 1;//Set Prescaler
	TIM4->CR1 |= (0x01);//TIM4_CNT is enabled (clocked)


	TIM3->PSC = 4000 - 1;//Set Prescaler
	TIM3->CR1 |= (0x01);//TIM3_CNT is enabled (clocked)


	TIM7->SR=0;
	TIM7->ARR=5-1;


	//red
	TIM6->SR=0;
	TIM6->ARR=10-1;

	//green
	TIM5->SR=0;
	TIM5->ARR=5-1;

	//blue
	TIM4->SR=0;
	TIM4->ARR=2-1;


	//color
	TIM3->SR=0;
	TIM3->ARR=1000-1;

	// TIM2 global interrupt : Position 45
	// TIM3 global interrupt : Position 46
	// TIM4 global interrupt : Position 47
	// TIM5 global interrupt : Position 48
	// TIM6 global interrupt : Position 49
	// TIM7 global interrupt : Position 50


	//NVIC regiter set of TIM6
	// NVIC_register=ceil(49/32) = 1
	// bit = 49 mod 32=17

	//TIM7 is 50 so, ISER1 18.bit
	NVIC->ISER[1]|=(1<<18);


	//TIM6 is 49 so, ISER1 17.bit
	NVIC->ISER[1]|=(1<<17);

	//TIM5 is 48 so, ISER1 16.bit
	NVIC->ISER[1]|=(1<<16);


	//TIM4 is 47 so, ISER1 15.bit
	NVIC->ISER[1]|=(1<<15);

	//TIM3 is 46 so, ISER1 14.bit
	NVIC->ISER[1]|=(1<<14);




	__enable_irq();
	TIM7->SR=0;
	TIM6->SR=0;
	TIM5->SR=0;
	TIM4->SR=0;
	TIM3->SR=0;

}

/*
 *
 * #include <stdint.h>
#define PortA 0
#define PortB 1
#define PortC 2
#define PortD 3
#define PortE 4
#define PortF 5
#define PortG 6
#define PortH 7

void Enable_RCC_AHB2ENR(int a){
	SET1(RCC_AHB2ENR,a); //Enable E port
}

#define SET1(X,Y) (X|=(0x01<<Y))
#define SET0(X,Y) (X&=(~(0x01<<Y)))


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

typedef struct{
	__IO uint32_t ISER[16];
	__IO uint32_t ICER[16];
	__IO uint32_t ISPR[16];
	__IO uint32_t ICPR[16];
	__IO uint32_t IABR[16];
	__IO uint32_t ITNS[16];
	__IO uint32_t reserved[120];
} NVIC_Type;


typedef struct{
	__IO uint32_t ICER[16];
} ICER_Type;

#define RCC_AHB2ENR *((volatile uint32_t *) (0x40021000 + 0x4C))
#define RCC_CR *((volatile uint32_t *) (0x40021000))
#define RCC_CFGR *((volatile uint32_t *) (0x40021000 + 0x008))
#define RCC_CSR *((volatile uint32_t *) (0x40021000 + 0x094))
#define RCC_APB1ENR1 *((volatile uint32_t *) (0x40021000 + 0x58))
#define NVIC			((NVIC_Type *) 		0xE000E100)
#define CLOSE			((ICER_Type *) 		0xE000E180)
#define GPIOA			((GPIO_TypeDef *)	0x42020000)
#define GPIOB			((GPIO_TypeDef *)	0x42020400)
#define GPIOC			((GPIO_TypeDef *)	0x42020800)
#define GPIOD			((GPIO_TypeDef *)	0x42020C00)
#define GPIOE			((GPIO_TypeDef *)	0x42021000)
#define TIM17           ((TIM_TypeDef *)	0x40014800)
#define TIM16           ((TIM_TypeDef *)	0x40014400)
#define TIM15           ((TIM_TypeDef *)	0x40014000)
#define TIM8            ((TIM_TypeDef *)	0x40013400)
#define TIM7     		((TIM_TypeDef *)    0x40001400)
#define TIM6            ((TIM_TypeDef *)	0x40001000)
#define TIM5            ((TIM_TypeDef *)	0x40000C00)
#define TIM4            ((TIM_TypeDef *)	0x40000800)
#define TIM3            ((TIM_TypeDef *)	0x40000400)
#define TIM2            ((TIM_TypeDef *)	0x40000000)
uint32_t step = 0;
uint32_t time4_enabler = 0;
uint32_t time5_enabler = 0;
uint32_t time6_enabler = 0;
uint32_t time7_enabler = 0;


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

void TIM7_IRQHandler(void){
	//PE11=> RED
	TIM7->SR=0;
	if (time7_enabler==0){
			SET1(GPIOE->ODR,11);
			time7_enabler=1;
	}else if(time7_enabler==1){
		SET0(GPIOE->ODR,11);
		time7_enabler=0;
	}


}
void TIM6_IRQHandler(void){
	//PE12=> RED

	TIM6->SR=0;
	if (time6_enabler==0){
			SET1(GPIOE->ODR,12);
			time6_enabler=1;
	}else if(time6_enabler==1){
		SET0(GPIOE->ODR,12);
		time6_enabler=0;
	}


}
void TIM5_IRQHandler(void){

}
void TIM4_IRQHandler(void){
	//PE_15=>BLUE
	TIM4->SR=0;
	if (time4_enabler==0){
			SET1(GPIOE->ODR,15);
			time4_enabler=1;
	}else if(time4_enabler==1){
		SET0(GPIOE->ODR,15);
		time4_enabler=0;
	}

}
void TIM3_IRQHandler(void){
	// Color
	TIM3->SR=0;
	if (step==0){  //None
		time6_enabler=-1;  //12
		time7_enabler=-1;   //11
		time4_enabler=-1; //15
		step=1;
	}
	else if(step==1){  //White
		time6_enabler=0;
		time7_enabler=0;
		time4_enabler=0;
		step=2;
	}
	else if(step==2){ //Cyan
		time6_enabler=-1;
		SET1(GPIOE->ODR,12);
		time7_enabler=0;
		time4_enabler=0;
		step=3;

	}
	else if(step==3){ //Mageta
		time6_enabler=1;
		time7_enabler=-1;
		SET1(GPIOE->ODR,11);
		time4_enabler=1;
		step=4;

	}
	else if(step==4){ //Blue
		time6_enabler=-1;
		SET1(GPIOE->ODR,12);
		time7_enabler=-1;
		SET1(GPIOE->ODR,11);
		time4_enabler=1;
		step=5;
	}
	else if(step==5){ //Yellow
		time6_enabler=1;
		time7_enabler=1;
		time4_enabler=-1;
		SET1(GPIOE->ODR,15);
		step=6;

	}
	else if(step==6){ //Green
		time6_enabler=-1;
		SET1(GPIOE->ODR,12);
		time7_enabler=1;
		time4_enabler=-1;
		SET1(GPIOE->ODR,15);
		step=7;

	}
	else if(step==7){ //Green
		time6_enabler=1;
		time7_enabler=-1;
		SET1(GPIOE->ODR,11);
		time4_enabler=-1;
		SET1(GPIOE->ODR,15);
		step=0;

	}
}

void __enable_irq(void){
	__asm volatile("MOV R0, #0");
	__asm volatile("MSR PRIMASK, R0");
	TIM7->SR=0;
	TIM6->SR=0;
	TIM5->SR=0;
	TIM4->SR=0;
	TIM3->SR=0;
}

void __disable_irq(void){
	__asm volatile("MOV R0, #1");
	__asm volatile("MSR PRIMASK, R0");
}



int calculate_distance(){

	SET1(RCC_AHB2ENR,4); //Enable E port
	//Initialize--------------------------------------------------------------
	//PE14 Triggers
	//PE15 Echo
	int trigger_pin=14;
	int echo_pin=15;
	//------------------------------------------------------------------------
	GPIOE->MODER &= (~(0x01 << (trigger_pin*2+1))); //PE14 output mode
	GPIOE->MODER |= (0x01 << (trigger_pin*2));


	GPIOE->MODER &= ~(0x01 << echo_pin*2+1); //PE15 input mode for Echo
	GPIOE->MODER &= ~(0x01 << echo_pin*2);
	//-------------------------------------------------------------------------

	// Timer Enablers:------------------------------------------------------------------
	// 5= TIM7, 4=TIM6, 3=TIM5, 2=TIM4, 1=TIM3, 0=TIM2
	RCC_APB1ENR1 |= 1 << 4;//TIM6x_CLK is enabled, running at 4MHz

	// 18=TIM17, 17=TIM16,16=TIM15, 13=TIM8, 11=TIM1
	//RCC_APB2ENR |= 1 << 17;
	//------------------------------------------------------------------------------------------
	// 1sn=1000ms=1000000us=1000000000ns

	TIM6->PSC = 4 - 1;//Set Prescaler to microseconds
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

int main(void) {


//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------

	//PE15=> BLUE    time4
	//PE11=> GREEN   time5
	//PE12=> RED     time6

	Enable_RCC_AHB2ENR(PortE);


	//PE15 output mode LED -> 01
	SET0(GPIOE->MODER,(15*2+1));
	SET1(GPIOE->MODER,(15*2));

	//PE11 output mode LED -> 01
	SET0(GPIOE->MODER,(11*2+1));
	SET1(GPIOE->MODER,(11*2));

	//PE12 output mode LED -> 01
	SET0(GPIOE->MODER,(12*2+1));
	SET1(GPIOE->MODER,(12*2));


	//PE12 input
	//SET0(GPIOE->MODER,(12*2+1));
	//SET0(GPIOE->MODER,(12*2));


	// To initialize the putputs
	GPIOE->ODR|=0xffffffff;
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	// Timer Enablers:----------------------------------------------------------------------
	// .  5 .    4 .   3     2    1   0
    //  TIM7   TIM6  TIM5 TIM4 TIM3 TIM2
	RCC_APB1ENR1 |= 1 << 5;//TIM7x_CLK is enabled, running at 4MHz
	RCC_APB1ENR1 |= 1 << 4;//TIM6x_CLK is enabled, running at 4MHz
	RCC_APB1ENR1 |= 1 << 3;//TIM5x_CLK is enabled, running at 4MHz
	RCC_APB1ENR1 |= 1 << 2;//TIM4x_CLK is enabled, running at 4MHz
	RCC_APB1ENR1 |= 1 << 1;//TIM3x_CLK is enabled, running at 4MHz
	RCC_APB1ENR1 |= 1 << 0;//TIM2x_CLK is enabled, running at 4MHz
	//----------------------------------------------------------------------------------------
	// DIER ----------------------------------------------------------------------------------
	//15    14    13  12    11    10    9     8   7   6 .   5 .   4 .   3    2    1     0
    //Res. TDE COMDE CC4DE CC3DE CC2DE CC1DE UDE BIE TIE COMIE CC4IE CC3IE CC2IE CC1IE UIE
	//Bit0 UIE : Update interrupt enable
	//        0: Update interrupt disabled
	//        1: Update interrupt enabled
	TIM7->DIER|=0x01; //Enable update interrupt
	TIM6->DIER|=0x01; //Enable update interrupt
	TIM5->DIER|=0x01; //Enable update interrupt
	TIM4->DIER|=0x01; //Enable update interrupt
	TIM3->DIER|=0x01; //Enable update interrupt
	TIM2->DIER|=0x01; //Enable update interrupt
	//----------------------------------------------------------------------------------------
	// EGR -----------------------------------------------------------------------------------
	//                                                       0
	//Res. Res. Res. Res. B2G BG TG COMG CC4G CC3G CC2G CC1G UG
	//Bit0 UG:Updategeneration
    //This bit can be set by software, it is automatically cleared by hardware.
    // .  0: No action
    //    1: Reinitialize the counter and generates an update of the registers. The prescaler internal
    //      counter is also cleared (the prescaler ratio is not affected). The counter is cleared if the
	// .    center-aligned mode is selected or if DIR=0 (upcounting), else it takes the auto-reload value
	// .    (TIMx_ARR) if DIR=1 (downcounting).
	TIM7->EGR|=1;
	TIM6->EGR|=1;
	TIM5->EGR|=1;
	TIM4->EGR|=1;
	TIM3->EGR|=1;
	TIM2->EGR|=1;

	//----------------------------------------------------------------------------------------
	// CR1 -----------------------------------------------------------------------------------
	// 15    14  13    12    11    10     9     8     7      6    5    4    3    2   1    0
	// Res. Res. Res. Res. UIFRE Res      CKD[1:0]   ARPE   CMS[1:0]  DIR  OPM  URS UDIS CEN


	//	Bit1 UDIS:Updatedisable
	//	This bit is set and cleared by software to enable/disable UEV event generation.
	//	0: UEV enabled. The Update (UEV) event is generated by one of the following events:
	//		– Counter overflow/underflow
	//		– Setting the UG bit
	//		– Update generation through the slave mode controller
	//		Buffered registers are then loaded with their preload values.
	//	1: UEV disabled. The Update event is not generated, shadow registers keep their value
	//		(ARR, PSC, CCRx). However the counter and the prescaler are reinitialized if the UG bit
	//	 	is set or if a hardware reset is received from the slave mode controller.

	TIM7->CR1 &= ~(1<<1);
	TIM6->CR1 &= ~(1<<1);
	TIM5->CR1 &= ~(1<<1);
	TIM4->CR1 &= ~(1<<1);
	TIM3->CR1 &= ~(1<<1);

	//	Bit2 URS:Update request source
	//	This bit is set and cleared by software to select the UEV event sources.
	//	0: Any of the following events generate an update interrupt or DMA request if enabled.
	//		hese events can be:
	//		– Counter overflow/underflow
	//		– Setting the UG bit
	//		– Update generation through the slave mode controller
	//	1: Only counter overflow/underflow generates an update interrupt or DMA request if enabled.


	TIM7->CR1 |=1<<2;
	TIM6->CR1 |=1<<2;
	TIM5->CR1 |=1<<2;
	TIM4->CR1 |=1<<2;
	TIM3->CR1 |=1<<2;

	// Bit0 CEN:Counterenable
	//	0: Counter disabled
	//	1: Counter enabled
	//	Note: External clock, gated mode and encoder mode can work only if the CEN bit has been
	//	previously set by software. However trigger mode can set the CEN bit automatically by hardware.


	// Since it is in 4Mhz, the counter will count 4Mhz/4000 = 1000 times per second which is in miliseconds.
	TIM7->PSC = 4000 - 1;//Set Prescaler
	TIM7->CR1 |= (0x01);//TIM6_CNT is enabled (clocked)

	TIM6->PSC = 4000 - 1;//Set Prescaler
	TIM6->CR1 |= (0x01);//TIM6_CNT is enabled (clocked)


	TIM5->PSC = 4000 - 1;//Set Prescaler
	TIM5->CR1 |= (0x01);//TIM5_CNT is enabled (clocked)


	TIM4->PSC = 4000 - 1;//Set Prescaler
	TIM4->CR1 |= (0x01);//TIM4_CNT is enabled (clocked)


	TIM3->PSC = 4000 - 1;//Set Prescaler
	TIM3->CR1 |= (0x01);//TIM3_CNT is enabled (clocked)

	//----------------------------------------------------------------------------------------
	// ARR -----------------------------------------------------------------------------------
	// 1sn=1000ms=1000000us=1000000000ns

	//PE11=> GREEN   time7
	// 1/200hz=5m
	TIM7->ARR=5-1;

	//PE12=> RED     time6
	// 1/100hz=10ms
	TIM6->ARR=10-1;

	//PE15=> BLUE    time4
	// 1/400hz=2.5ms
	TIM4->ARR=2-1;


	//1/1hz=1s which is 1000ms
	TIM3->SR=0;
	TIM3->ARR=1000-1;

	// TIM2 global interrupt : Position 45
	// TIM3 global interrupt : Position 46
	// TIM4 global interrupt : Position 47
	// TIM5 global interrupt : Position 48
	// TIM6 global interrupt : Position 49
	// TIM7 global interrupt : Position 50

	//TIM7 is 50 so, ISER1 18.bit
	NVIC->ISER[1]|=(1<<18);

	//TIM6 is 49 so, ISER1 17.bit
	NVIC->ISER[1]|=(1<<17);

	//TIM5 is 48 so, ISER1 16.bit
	NVIC->ISER[1]|=(1<<16);

	//TIM4 is 47 so, ISER1 15.bit
	NVIC->ISER[1]|=(1<<15);

	//TIM3 is 46 so, ISER1 14.bit
	NVIC->ISER[1]|=(1<<14);

	//TIM2 is 45 so, ISER1 13.bit
	NVIC->ISER[1]|=(1<<13);

	__enable_irq();

}
 */


