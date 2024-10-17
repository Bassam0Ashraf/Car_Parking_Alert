/******************************************************************************
 *
 * Main Application
 *
 * File Name: Car_Parking_System.c
 *
 * Description: Source file for the Car Parking System Application.
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

/* Include header file "Car_Parking_System.h" that contain all file we need */
#include "Car_Parking_System.h"

/*******************************************************************************
 *                     		  Main Program                                     *
 *******************************************************************************/

int main()
{
	/* Initialize all drivers we need. */
	LCD_init();				/* Initialize LCD driver */
	LCD_clearScreen();		/* Clear any text on LCD */
	Ultrasonic_init();		/* Initialize Ultrasonic Sensor driver */
	Buzzer_init();			/* Initialize buzzer driver */
	LEDS_init();			/* Initialize LEDs driver */

	/* Enable global interrupt by set "1" to register SREG */
	SREG |= (1 << 7);

	/* Define variable to store distance on it */
	uint16 distance;


	/* Display string "Distance =" & "cm" on LCD */
	LCD_displayString("Distance = ");
	LCD_displayStringRowColumn(0, 14, "cm");


	for(;;)
	{
		/* Display distance on LCD */
		LCD_moveCursor(0, 11);
		distance = Ultrasonic_readDistance();
		if (distance < 10)
		{
			/* To clear the second digits after the number */
			LCD_intgerToString(distance);
			LCD_displayString("  ");
		}
		else
		{
			LCD_intgerToString(distance);
		}

		/* LEDs and buzzer control */
		if(distance >= 20)
		{
			LED_off( LED_RED );
			LED_off( LED_GREEN );
			LED_off( LED_BLUE );
			Buzzer_off();
		}
		else if (distance >= 16 && distance <= 20)
		{
			LED_on( LED_RED );
			LED_off( LED_GREEN );
			LED_off( LED_BLUE );
			Buzzer_off();
		}
		else if (distance >= 11 && distance <= 15)
		{
			LED_on( LED_RED );
			LED_on( LED_GREEN );
			LED_off( LED_BLUE );
			Buzzer_off();
		}
		else if (distance >= 6 && distance <= 10)
		{
			LED_on( LED_RED );
			LED_on( LED_GREEN );
			LED_on( LED_BLUE );
			Buzzer_off();
		}
		else
		{
			/* Display waring massage "STOP !" on LCD */
			LCD_displayStringRowColumn(1, 6, "STOP !");

			while( distance <= MINIMUM_SAFTY_DISTANCE_IN_CM )
			{
				/* Flashing all LEDs and buzzer for warning */
				Buzzer_on();
				LED_on( LED_RED );
				LED_on( LED_GREEN );
				LED_on( LED_BLUE );

				_delay_ms(200);

				Buzzer_off();
				LED_off( LED_RED );
				LED_off( LED_GREEN );
				LED_off( LED_BLUE );

				_delay_ms(200);

				/* Continue displaying distance on LCD */
				LCD_moveCursor(0, 11);
				distance = Ultrasonic_readDistance();
				if (distance < 10)
				{
					/* To clear the second digits after the number */
					LCD_intgerToString(distance);
					LCD_displayString("  ");
				}
				else
				{
					LCD_intgerToString(distance);
				}

			}

			/* Turn OFF buzzer and remove "STOP !" from LCD */
			Buzzer_off();
			LCD_displayStringRowColumn(1, 6, "      ");
		}

	}

	return 0;
}
