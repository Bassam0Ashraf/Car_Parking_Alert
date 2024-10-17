# **Project Overview:**
This project uses an ATmega32 microcontroller to process distance data
from an ultrasonic sensor and display the results on an LCD. The system
includes three LEDs (Red, Green, and Blue) and a buzzer for indicating the
proximity of an obstacle. The LEDs light up progressively and the buzzer
activates as the obstacle gets closer, helping drivers park safely.

 # **Features:**
### 1. **Ultrasonic Distance Measurement:**
- The ultrasonic sensor measures the distance between the car and any nearby object.

### 2. **LCD Display:**
- Displays the distance measured by the ultrasonic sensor in centimeters. Also displays "Stop" if the distance is less than 5 cm.
  
### 3.  **LED Indicators:**
- Three LEDs (Red, Green, and Blue) light up according to the proximity of the object.

### 4. **Buzzer Alert:**
- The buzzer sounds when the object is too close (<= 5 cm).

### 5. **Dynamic LED Behavior:**
- LEDs turn ON/OFF based on the following distance ranges.


# **Hardware Components:**
 1. **Microcontroller:** ATmega32.
 2. **Ultrasonic Sensor:** HC-SR04.
 3. **Display:** 16x2 LCD in 4-bit mode.
 4. **LEDs:** Red,Green and Blue.
 5. **Buzzer:** activated when the object is too close.


# **Operation Description:**
- The ultrasonic sensor emits an ultrasonic wave and listens for its reflection from a nearby object.
- The ATmega32 microcontroller calculates the distance by measuring the time taken for the wave to return to the sensor.
- The measured distance is displayed on the LCD in centimeters.
- The system continuously updates and recalculates the distance, providing real-time feedback to the driver.
- Distance to LED and Buzzer Mapping:
    - Distance <= 5 cm: All LEDs are flashing (Red, Green, Blue), Buzzer sounds, LCD shows "Stop."
    - 6 cm <= Distance <= 10 cm: All LEDs ON (Red, Green, Blue), No buzzer.
    - 11 cm <= Distance <= 15 cm: Red and Green LEDs ON, Blue LED OFF.
    - 16 cm <= Distance <= 20 cm: Only Red LED ON, others OFF.
    - Distance > 20 cm: All LEDs OFF, Buzzer OFF.
