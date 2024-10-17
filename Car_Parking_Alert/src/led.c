 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.c
 *
 * Description: Source file for the LED driver.
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#include "led.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function initializes all Leds (red, green, blue) pins direction as OUTPUT.
 * Turn off all the Leds.
 */
void LEDS_init(void)
{
	/* Configure LED red as OUTPUT */
	GPIO_setupPinDirection(LED_RED_PORT_ID , LED_RED_PIN_ID , PIN_OUTPUT);

	/* Configure LED green as OUTPUT */
	GPIO_setupPinDirection(LED_GREEN_PORT_ID , LED_GREEN_PIN_ID , PIN_OUTPUT);

	/* Configure LED blue as OUTPUT */
	GPIO_setupPinDirection(LED_BLUE_PORT_ID , LED_BLUE_PIN_ID , PIN_OUTPUT);

#ifdef POSITIVE_LOGIC
	/* Turn OFF all LED */
	GPIO_writePin(LED_RED_PORT_ID , LED_RED_PIN_ID , LOGIC_LOW);
	GPIO_writePin(LED_GREEN_PORT_ID , LED_GREEN_PIN_ID , LOGIC_LOW);
	GPIO_writePin(LED_BLUE_PORT_ID , LED_BLUE_PIN_ID , LOGIC_LOW);
#else
	/* Turn OFF all LED */
	GPIO_writePin(LED_RED_PORT_ID , LED_RED_PIN_ID , LOGIC_HIGH);
	GPIO_writePin(LED_GREEN_PORT_ID , LED_GREEN_PIN_ID , LOGIC_HIGH);
	GPIO_writePin(LED_BLUE_PORT_ID , LED_BLUE_PIN_ID , LOGIC_HIGH);
#endif

}


/*
 * Description :
 * Function Turns ON the specified LED.
 */
void LED_on(LED_ID id)
{

#ifdef POSITIVE_LOGIC
	switch(id)
	{
	case LED_RED:
		/* Turn ON LED Red */
		GPIO_writePin(LED_RED_PORT_ID , LED_RED_PIN_ID , LOGIC_HIGH);
		break;
	case LED_GREEN:
		/* Turn ON LED Green */
		GPIO_writePin(LED_GREEN_PORT_ID , LED_GREEN_PIN_ID , LOGIC_HIGH);
		break;
	case LED_BLUE:
		/* Turn ON LED Blue */
		GPIO_writePin(LED_BLUE_PORT_ID , LED_BLUE_PIN_ID , LOGIC_HIGH);
		break;
	}
#else
	switch(id)
	{
	case LED_RED:
		/* Turn ON LED Red */
		GPIO_writePin(LED_RED_PORT_ID , LED_RED_PIN_ID , LOGIC_LOW);
		break;
	case LED_GREEN:
		/* Turn ON LED Green */
		GPIO_writePin(LED_GREEN_PORT_ID , LED_GREEN_PIN_ID , LOGIC_LOW);
		break;
	case LED_BLUE:
		/* Turn ON LED Blue */
		GPIO_writePin(LED_BLUE_PORT_ID , LED_BLUE_PIN_ID , LOGIC_LOW);
		break;
	}
#endif
}


/*
 * Description :
 * Function Turns OFF the specified LED.
 */
void LED_off(LED_ID id)
{
#ifdef POSITIVE_LOGIC
	switch(id)
	{
	case LED_RED:
		/* Turn OFF LED Red */
		GPIO_writePin(LED_RED_PORT_ID , LED_RED_PIN_ID , LOGIC_LOW);
		break;
	case LED_GREEN:
		/* Turn OFF LED Green */
		GPIO_writePin(LED_GREEN_PORT_ID , LED_GREEN_PIN_ID , LOGIC_LOW);
		break;
	case LED_BLUE:
		/* Turn OFF LED Blue */
		GPIO_writePin(LED_BLUE_PORT_ID , LED_BLUE_PIN_ID , LOGIC_LOW);
		break;
	}
#else
	switch(id)
	{
	case LED_RED:
		/* Turn OFF LED Red */
		GPIO_writePin(LED_RED_PORT_ID , LED_RED_PIN_ID , LOGIC_HIGH);
		break;
	case LED_GREEN:
		/* Turn OFF LED Green */
		GPIO_writePin(LED_GREEN_PORT_ID , LED_GREEN_PIN_ID , LOGIC_HIGH);
		break;
	case LED_BLUE:
		/* Turn OFF LED Blue */
		GPIO_writePin(LED_BLUE_PORT_ID , LED_BLUE_PIN_ID , LOGIC_HIGH);
		break;
	}
#endif
}
