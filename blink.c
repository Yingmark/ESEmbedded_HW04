#include <stdint.h>
#include "reg.h"

/**
 * 
 * LED init
 * 
 */
void led_init(unsigned int led)
{
	SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTD));

	//MODER led pin = 01 => General purpose output mode
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_MODER_OFFSET, MODERy_1_BIT(led));
	SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_MODER_OFFSET, MODERy_0_BIT(led));

	//OT led pin = 0 => Output push-pull
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OTYPER_OFFSET, OTy_BIT(led));

	//OSPEEDR led pin = 00 => Low speed
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(led));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(led));

	//PUPDR led pin = 00 => No pull-up, pull-down
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(led));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(led));
}

/**
 * 
 * blink LED forever
 * 
 */
void blink(unsigned int led)
{
	led_init(led);

	unsigned int i;
		//set GPIOD led pin
	SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BSy_BIT(led));

	for (i = 0; i < 100000; i++)
		;

		//reset GPIOD led pin
	SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT(led));

	for (i = 0; i < 100000; i++)
		;
}

/**
 * 
 * blink LED x count
 * 
 */
void blink_count(unsigned int led, unsigned int count)
{
	led_init(led);

	unsigned int i;

	while (count--)
	{
		//set GPIOD led pin
		SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BSy_BIT(led));

		for (i = 0; i < 100000; i++)
			;

		//reset GPIOD led pin
		SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT(led));

		for (i = 0; i < 100000; i++)
			;
	}
}

void button_init(unsigned int pin)
{
	SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(pin));

	//MODER led pin = 00 => Input mode
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_MODER_OFFSET, MODERy_1_BIT(pin));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_MODER_OFFSET, MODERy_0_BIT(pin));

	//OT led pin = 0 => Output push-pull
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_OTYPER_OFFSET, OTy_BIT(pin));

	//OSPEEDR led pin = 00 => Low speed
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(pin));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(pin));

	//PUPDR led pin = 00 => No pull-up, pull-down
	SET_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(pin));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(pin));
}

void button_opration(unsigned int button)
{
	button_init(button);
	while(1)
	{
		uint32_t x;
		x = READ_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_IDR_OFFSET, IDRy_BIT(button));
		if (x == 1)
		{
			blink(13);
		}
	}
}
