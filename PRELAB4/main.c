

#define GPIOx_MODER *((volatile uint32_t *) 0x42020000)
#define GPIOx_ODR *((volatile uint32_t *) 0x42020014)




#define RCC_AHB2ENR *((volatile uint32_t *) 0x4002104C)
#define LED1_MODER *((volatile uint32_t *) 0x42020400)
#define LED2_MODER *((volatile uint32_t *) 0x42020800)
#define PUSHBUTTON_MODER *((volatile uint32_t *) 0x42020800)

#define LED1_ODR *((volatile uint32_t *) 0x42020414)
#define LED2_ODR *((volatile uint32_t *) 0x42020814)

#define PUSHBUTTON_IDR *((volatile uint32_t *) 0x42020810)


//LED1_MODER,  PB7         0xFFFF FEBF  15 14
//LED2_MODER,  PC7         0xFFFF FFFF  15 14
//PUSHBUTTON_MODER, PC13   0xFFFF FFFF  27 26


#include <stdint.h>
uint32_t wait_millisecond = 1000;
uint32_t wait_counter = 0;
int main(void)  {
    volatile int index;
    RCC_AHB2ENR |= (1<<1); //Activate B on the bus
    RCC_AHB2ENR |= (1<<2); //Activate C on the bus

    for(index=0;index<wait_millisecond*666;index++);
    wait_counter = wait_counter + 1;

    LED1_MODER &= ~(1 << 15); //output mode  15->0
    LED1_MODER |= (1 << 14); // output mode 14->1

    LED2_MODER &= ~(1 << 15); //output mode  15->0
    LED2_MODER |= (1 << 14);// output mode 14->1

    PUSHBUTTON_MODER&= ~(1 << 27); // input mode 00
    PUSHBUTTON_MODER&= ~(1 << 26);



    while (1){
    	if( (PUSHBUTTON_IDR>>13==1)){
    		//Pressed
    	LED2_ODR |= (1 << 7);
        LED1_ODR &= ~(1 << 7);
    	}else{
    		//Not pressed
    		LED1_ODR |= (1 << 7);
    		LED2_ODR &= ~(1 << 7);
    	}


    }
    return 0;
}
