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
#define RCC_APB2ENR  	*((volatile uint32_t *) (0x40021000 + 0x60))
#define RCC_CCIPR1      *((volatile uint32_t *) (0x40021000 + 0x088))


#define ADC_ISR         *((volatile uint32_t *) (0x42028000 + 0x00))
#define ADC_SMPR1       *((volatile uint32_t *) (0x42028000 + 0x14))
#define ADC_IER         *((volatile uint32_t *) (0x42028000 + 0x04))
#define ADC_SMPR2       *((volatile uint32_t *) (0x42028000 + 0x18))
#define ADC_CCR         *((volatile uint32_t *) (0x42028000 + 0x08))
#define ADC_CFGR        *((volatile uint32_t *) (0x42028000 + 0x0C))
#define ADC_SQR1        *((volatile uint32_t *) (0x42028000 + 0x30))
#define ADC_SQR2        *((volatile uint32_t *) (0x42028000 + 0x34))
#define ADC_SQR3        *((volatile uint32_t *) (0x42028000 + 0x38))
#define ADC_SQR4        *((volatile uint32_t *) (0x42028000 + 0x3C))
#define ADC_DR          *((volatile uint32_t *) (0x42028000 + 0x40))
#define ADC_CR          *((volatile uint32_t *) (0x42028000 + 0x08))

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
#define SET_MODER_ANALOG(X,Y) ({\
            SET1(X,((Y)*2+1));\
            SET1(X,((Y)*2));\
           })
void Enable_RCC_AHB2ENR(int a){
	SET1(RCC_AHB2ENR,a);
}

void __enable_irq(void){
	__asm volatile("MOV R0, #0");
	__asm volatile("MSR PRIMASK, R0");
	//TIM7->SR=0;
	//TIM6->SR=0;
	//TIM5->SR=0;
	//TIM4->SR=0;
	//TIM3->SR=0;
}

void __disable_irq(void){
	__asm volatile("MOV R0, #1");
	__asm volatile("MSR PRIMASK, R0");
}

uint32_t wait_millisecond = 1000;
uint32_t wait_counter = 0;

#include <stdint.h>

void ADC1_2_IRQHandler() {

	uint32_t num=ADC_DR;
	if (num>4030*3/4){
	    SET1(GPIOC->ODR,7);//GREEN
	    SET1(GPIOB->ODR,7);//BLUE
	    SET1(GPIOA->ODR,9);//RED
	}else if(num>4030*2/4){
	    SET1(GPIOC->ODR,7);//GREEN
	    SET1(GPIOB->ODR,7);//BLUE
	    SET0(GPIOA->ODR,9);//RED
	}else if(num>4030*1/4){
	    SET0(GPIOC->ODR,7);//GREEN
	    SET1(GPIOB->ODR,7);//BLUE
	    SET0(GPIOA->ODR,9);//RED
	}else{
	    SET0(GPIOC->ODR,7);//GREEN
	    SET0(GPIOB->ODR,7);//BLUE
	    SET0(GPIOA->ODR,9);//RED
	}

	int index;
	for(index=0;index<wait_millisecond*333;index++);
	wait_counter = wait_counter + 1;
	SET1(ADC_CR, 2);
}


int main(void) {
    //GREEN PC7PA5, BLUE PB7, RED PA9
    Enable_RCC_AHB2ENR(PortA);
    Enable_RCC_AHB2ENR(PortB);
    Enable_RCC_AHB2ENR(PortC);
    SET_MODER_OUTPUT(GPIOC->MODER,7);
    SET_MODER_OUTPUT(GPIOA->MODER,9);
    SET_MODER_OUTPUT(GPIOB->MODER,7);
    SET1(GPIOC->ODR,7);//GREEN
    SET1(GPIOB->ODR,7);//BLUE
    SET1(GPIOA->ODR,9);//RED
	//Enable Clock for GPIO ADC12_IN3 = PC2
    SET1(RCC_AHB2ENR, 2);
    //Enable Clock for ADC
    SET1(RCC_AHB2ENR, 13);
	//Select ADC clock as System clock
	SET1(RCC_CCIPR1, 28);
    SET1(RCC_CCIPR1, 29);
	//Change Pin Mode to Analog
    SET_MODER_ANALOG(GPIOC->MODER, 2);
	//Change Pin Pull/Down to no pull-up no pull-down
    SET0(GPIOC->PUPDR, 4);
    SET0(GPIOC->PUPDR, 5);
	//Change Regular channel sequence length to 1 conversion
    SET0(ADC_SQR1, 0);
    SET0(ADC_SQR1, 1);
    SET0(ADC_SQR1, 2);
    SET0(ADC_SQR1, 3);
    SET0(ADC_SQR1, 4);
	//Add to channel to first sequence
    SET1(ADC_SQR1, 6);
    SET1(ADC_SQR1, 7);
    SET0(ADC_SQR1, 8);
    SET0(ADC_SQR1, 9);
    SET0(ADC_SQR1, 10);
    //Disable Deep-power-down for ADC
    SET0(ADC_CR, 29);
	//Enable ADC Voltage regulator
    SET1(ADC_CR, 28);
	//Configure for Single conversion mode
    SET0(ADC_CFGR, 13);
	//Enable ADC
    SET1(ADC_CR, 0);
    //Wait ADC is enabled
    while(ADC_ISR & 0x01 == 0);
	//Enable interrupt for end of regular conversion
	SET1(ADC_IER, 2);//End of regular conversion
    //SET1(ADC_IER, 3);//End of regular sequence of conversions
    //TIM1 37 prior
  	NVIC->ISER[1]|=(1<<5);
  	__asm volatile("MOV R0, #0");
  	__asm volatile("MSR PRIMASK, R0");
	//Start regular conversion of ADC
    SET1(ADC_CR, 2);
	//Write program according to problem description
	while(1){
		__asm ("wfi");
	}
}

