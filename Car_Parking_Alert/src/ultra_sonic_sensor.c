/******************************************************************************
 *
 * Module: Ultra Sonic Sensor (HC-SR04)
 *
 * File Name: ultra_sonic_sensor.c
 *
 * Description: Source file for UltraSonic Sensor (HC-SR04) driver.
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#include "ultra_sonic_sensor.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 g_Flag = 0;			/* This flag is set when the high time is calculated */
uint8 g_EdgeCount = 0;		/* Variable to count the edges */
uint16 g_TimeHigh = 0;		/* This is the time in which the signal travels from HC-SR04 to object and returns to the module HC-SR-04 again */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function Initialize the ICU driver as required.
 * Set up the ICU callback function.
 * Set the direction for the trigger pin as output through the GPIO driver.
 */
void Ultrasonic_init(void)
{
	/* Create configuration structure for ICU driver and wait for the RAISING edge at the beginning */
	ICU_ConfigType ICU_Configurations = { F_CPU_8 , RAISING };

	/* Initialize ICU driver */
	ICU_init(&ICU_Configurations);

	/* Set the Call back function pointer in the ICU driver */
	ICU_setCallBack(Ultrasonic_edgeProcessing);

	/* Configure trigger pin as OUTPUT pin */
	GPIO_setupPinDirection(ULTRASONIC_SENSOR_TRIGGER_PORT_ID , ULTRASONIC_SENSOR_TRIGGER_PIN_ID , PIN_OUTPUT);
	GPIO_writePin(ULTRASONIC_SENSOR_TRIGGER_PORT_ID , ULTRASONIC_SENSOR_TRIGGER_PIN_ID , LOGIC_LOW);
}


/*
 * Description :
 * Function responsible for Sending the trigger pulse to the UltraSonic sensor.
 */
void Ultrasonic_Trigger(void)
{
	/* Send trigger pulse 10 uSec to ultraSoinc */
	GPIO_writePin(ULTRASONIC_SENSOR_TRIGGER_PORT_ID , ULTRASONIC_SENSOR_TRIGGER_PIN_ID , LOGIC_HIGH);

	/* wait 10 uSec as datasheet said that */
	_delay_us(10);

	/* Stop sending pulse */
	GPIO_writePin(ULTRASONIC_SENSOR_TRIGGER_PORT_ID , ULTRASONIC_SENSOR_TRIGGER_PIN_ID , LOGIC_LOW);
}


/*
 * Description :
 * Function Send the trigger pulse by using the Ultrasonic_Trigger function.
 * Start the measurement process via the ICU driver.
 * Return: The measured distance in centimeters.
 */
uint16 Ultrasonic_readDistance(void)
{
	/* Define variable to store distance on it */
	uint16 distance;

	/* Send trigger pulse to Ultrasonic Sensor */
	Ultrasonic_Trigger();

	/* Wait till calculate the high time */
	while(g_Flag != 1);

	/* The distance of Object (in cm) = (340000/2)*Time = 17000*Time
	 *  we have selected an 16MHz oscillator frequency for ATmega32, with
	 *  Prescaler F_CPU/8 for timer frequency,Then time to execute 1 instruction is 0.5 us.
	 * So, the timer gets incremented after 0.5 us time elapse.
	 * The distance of Object (in cm) = 17000*(Timer value)*0.5us
	 * 								  = (Timer value)/117.6  */
	distance = (float32) (g_TimeHigh / 112.1);						/* 112.1 instead of 117.6 (give me best results) in cm */

	return distance;
}


/*
 * Description :
 * Function This is the callback function called by the ICU driver.
 * It calculates the high time (pulse time) generated by the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void)
{
	g_EdgeCount++;
	g_Flag = 0;

	if(g_EdgeCount == 1)
	{
		/* Clear the timer counter register to start measurements from the first detected rising edge */
		ICU_clearTimerValue();

		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_EdgeCount == 2)
	{
		/* Store the High time value */
		g_TimeHigh = ICU_getInputCaptureValue();

		/* Detect rising edge */
		ICU_setEdgeDetectionType(RAISING);
		g_EdgeCount = 0;

		/* Set g_flag to execute the distance measurement in the Ultrasonic_readDistance Function */
		g_Flag = 1;
	}

}
