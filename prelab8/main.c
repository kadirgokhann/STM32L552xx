#include <stdint.h>
#define PortA 0
#define PortB 1
#define PortC 2
#define PortD 3
#define PortE 4
#define PortF 5
#define PortG 6
#define PortH 7

#define HI 1
#define LO 0
#define RCC_AHB2ENR     *((volatile uint32_t *) (0x40021000 + 0x4C))
#define RCC_CR          *((volatile uint32_t *) (0x40021000 + 0x00))
#define RCC_CFGR        *((volatile uint32_t *) (0x40021000 + 0x008))
#define RCC_CSR         *((volatile uint32_t *) (0x40021000 + 0x094))
#define RCC_APB1ENR1    *((volatile uint32_t *) (0x40021000 + 0x58))
#define RCC_APB2ENR  	 *((volatile uint32_t *) (0x40021000 + 0x60))

#define NVIC			((NVIC_Type *) 		0xE000E100)

#define GPIOA			((GPIO_TypeDef *)	0x42020000)
#define GPIOB			((GPIO_TypeDef *)	0x42020400)
#define GPIOC			((GPIO_TypeDef *)	0x42020800)
#define GPIOD			((GPIO_TypeDef *)	0x42020C00)
#define GPIOE			((GPIO_TypeDef *)	0x42021000)
#define GPIOF			((GPIO_TypeDef *)	0x42021400)
#define GPIOG			((GPIO_TypeDef *)	0x42021800)
#define GPIOH			((GPIO_TypeDef *)	0x42021C00)

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
#define TIM1            ((TIM_TypeDef *)	0x40012C00)

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
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
} TIM1_TypeDef;
typedef struct{
	volatile uint32_t ISER[16];
	volatile uint32_t ICER[16];
	volatile uint32_t ISPR[16];
	volatile uint32_t ICPR[16];
	volatile uint32_t IABR[16];
	volatile uint32_t ITNS[16];
	volatile uint32_t reserved[120];
} NVIC_Type;


#define SET1(X,Y) (X|=(0x01<<Y))
#define SET0(X,Y) (X&=(~(0x01<<Y)))

#define SET_MODER_INPUT(X,Y) ({\
            SET0(X,((Y)*2+1));\
            SET0(X,((Y)*2));\
           })


#define SET_MODER_OUTPUT(X,Y) ({\
            SET0(X,((Y)*2+1));\
            SET1(X,((Y)*2));\
           })

#define SET_MODER_ALT_FUNC(X,Y) ({\
            SET1(X,((Y)*2+1));\
            SET0(X,((Y)*2));\
           })



void Enable_RCC_AHB2ENR(int a){
	SET1(RCC_AHB2ENR,a); //Enable E port
}
uint32_t wait_counter=0;
uint32_t step = 0;
uint32_t time4_enabler = 0;
uint32_t time5_enabler = 0;
uint32_t time6_enabler = 0;
uint32_t time7_enabler = 0;
uint32_t pulsewidth = 0;
uint32_t edgefirst = 0;

void seven_display_init();
void display(uint32_t value);
void TIM7_IRQHandler(void);
void TIM15_IRQHandler(void){
	static unsigned int ic_pin=0;
	TIM15->SR=0;
	 if(ic_pin==0)//HI has come
	 {
		 ic_pin=1;
		 edgefirst = TIM15->CCR1;
	 }
	 else //LO has come
	 {
		 ic_pin=0;
		 pulsewidth= ((TIM15->CCR1)>>16)-edgefirst;
	 }
}

void TIM4_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM1_IRQHandler(void){
	TIM1->SR=0;
	if (pulsewidth<100 && pulsewidth>0){
		TIM1->CCR1=pulsewidth;
		TIM1->CCR2=pulsewidth; //100
		TIM1->ARR=pulsewidth;
		TIM1->PSC=pulsewidth;}
	else if(pulsewidth>=100 && pulsewidth<300){
		TIM1->CCR1=pulsewidth;
		TIM1->CCR2=pulsewidth; //500
		TIM1->ARR=pulsewidth;
		TIM1->PSC=pulsewidth;}
	else if(pulsewidth>=300 && pulsewidth<600){
		TIM1->CCR1=pulsewidth;
		TIM1->CCR2=pulsewidth; //1000
	TIM1->ARR=pulsewidth;
	TIM1->PSC=pulsewidth;}
	else if(pulsewidth>=600 && pulsewidth<900){
		TIM1->CCR1=pulsewidth;
		TIM1->CCR2=pulsewidth; //1500
		TIM1->PSC=pulsewidth;
	TIM1->ARR=pulsewidth;}
	else if(pulsewidth>=900){
		TIM1->CCR1=pulsewidth;
		TIM1->CCR2=pulsewidth; //2000
	TIM1->ARR=pulsewidth;
	TIM1->PSC=pulsewidth;}

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
int main(void) {




    Enable_RCC_AHB2ENR(PortA); // LED PA9 /
    // Set the mode of the pin to alternate function

    //SET_MODER_OUTPUT(GPIOA->MODER,9); //PA9 for led
    SET_MODER_INPUT(GPIOF->MODER,9); // PF9 for switch



	//INPUT
    // TIM15_CH1  PA2 AF14

    SET_MODER_ALT_FUNC(GPIOA->MODER,2);  // PA2 for TIM15_CH1  AF14
	// 1110 AF14
    SET0(GPIOA->AFRL,((2*4)+0));
    SET1(GPIOA->AFRL,((2*4)+1));
	SET1(GPIOA->AFRL,((2*4)+2));
	SET1(GPIOA->AFRL,((2*4)+3));
	RCC_APB2ENR|=1<<16; //TIM15_CLK is enabled.
	// for 5 ms -> 20000
	TIM15->PSC=8000-1;

	SET1(TIM15->DIER,1);


	SET1(TIM15->CCMR1,0);
	SET0(TIM15->CCMR1,1);

	SET1(TIM15->CCER,0);
	SET1(TIM15->CCER,3);
	SET1(TIM15->CCER,1);


	TIM15->CR1 |= (0x01);//TIM5_CNT is enabled (clocked)sssssss
	//TIM15 is 69 so, ISER2
	NVIC->ISER[2]|=(1<<5);




	//OUTPUT
	//PA9 TIM1_CH2 AF1 and led  AF1=0001
	SET_MODER_ALT_FUNC(GPIOA->MODER,9);

    SET1(GPIOA->AFRH,((9*4-32)+0));
    SET0(GPIOA->AFRH,((9*4-32)+1));
	SET0(GPIOA->AFRH,((9*4-32)+2));
	SET0(GPIOA->AFRH,((9*4-32)+3));
	RCC_APB2ENR|=1<<11;
	TIM1->CCR2=200;
	TIM1->CCR1=200;

	TIM1->CR1 |=1<<2;
	TIM1->CR1 &= ~(1<<1);

	TIM1->EGR|=1;


	SET1(TIM1->DIER,0);
	SET1(TIM1->DIER,1);
	SET1(TIM1->DIER,2);


	SET1(TIM1->BDTR,15);

	SET0(TIM1->CCMR1,9);
	SET0(TIM1->CCMR1,8);
	SET0(TIM1->CCMR1,0);
	SET0(TIM1->CCMR1,1);


	SET0(TIM1->CCMR1,24);
	SET0(TIM1->CCMR1,14);
	SET1(TIM1->CCMR1,13);
	SET1(TIM1->CCMR1,12);

	SET1(TIM1->CCER,4);
	SET1(TIM1->CCER,0);

	TIM1->ARR=200;

	TIM1->PSC=20000-1;

	TIM1->CR1 |= (0x01);//TIM5_CNT is enabled (clocked)sssssss
  //TIM1 44 prior
	NVIC->ISER[1]|=(1<<12);
	NVIC->ISER[1]|=(1<<10);

	__asm volatile("MOV R0, #0");
	__asm volatile("MSR PRIMASK, R0");
	while (1)
	__asm volatile("wfi");
}
