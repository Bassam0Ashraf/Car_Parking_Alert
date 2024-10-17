 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.h
 *
 * Description: header file for LED driver.
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/
#ifndef SRC_LED_H_
#define SRC_LED_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LED HW Ports and Pins Ids */
#define LED_RED_ID						1
#define LED_RED_PORT_ID                 PORTC_ID
#define LED_RED_PIN_ID                  PIN0_ID

#define LED_GREEN_ID					2
#define LED_GREEN_PORT_ID               PORTC_ID
#define LED_GREEN_PIN_ID                PIN1_ID

#define LED_BLUE_ID						3
#define LED_BLUE_PORT_ID                PORTC_ID
#define LED_BLUE_PIN_ID                 PIN2_ID

/* If LED connected by positive logic we keep this #define and if not we can deleted */
#define POSITIVE_LOGIC

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	LED_RED,LED_GREEN,LED_BLUE
}LED_ID;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function initializes all Leds (red, green, blue) pins direction as OUTPUT.
 * Turn off all the Leds.
 */
void LEDS_init(void);

/*
 * Description :
 * Function Turns ON the specified LED.
 */
void LED_on(LED_ID id);

/*
 * Description :
 * Function Turns OFF the specified LED.
 */
void LED_off(LED_ID id);


#endif /* SRC_LED_H_ */
