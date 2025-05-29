# Car Parking Sensor System  

## 📖 Project Overview  
Develop a car parking alert system using ATmega32 microcontroller and ultrasonic sensor to measure obstacle distance and provide visual and audio warnings to assist drivers.

## 🎯 Objectives  
- Measure distance to obstacles using ultrasonic sensor and display on LCD.  
- Provide LED and buzzer alerts based on proximity thresholds.  
- Ensure safe parking with dynamic, real-time feedback.

## 💡 Features  
- **Ultrasonic Distance Measurement:** Calculates distance and updates in real-time.  
- **LCD Display:** Shows distance in centimeters, displays "Stop" if object is ≤5 cm.  
- **LED Indicators:** Red, Green, and Blue LEDs light up based on proximity.  
- **Buzzer Alert:** Activates when distance ≤5 cm.  
- **Dynamic Feedback:** LED and buzzer behavior based on distance ranges.

## 📚 Hardware Components  
- **Microcontroller:** ATmega32  
- **Ultrasonic Sensor:** HC-SR04  
- **Display:** 16x2 LCD (4-bit mode)  
- **LEDs:** Red, Green, Blue  
- **Buzzer:** Audible alert for close obstacles  

![Car Parking Sensor](https://github.com/user-attachments/assets/4e8ff323-0c4a-4098-8eb4-e5b5094a2c42)  

## 🚀 Operation Highlights  
- **Ultrasonic Measurement:** Sends and receives waves to detect distance.  
- **Distance Calculation:** ATmega32 calculates and updates LCD with real-time distance.  
- **Alert Levels:**
  - ≤5 cm: All LEDs flash, buzzer sounds, LCD shows "Stop".  
  - 6–10 cm: All LEDs ON, no buzzer.  
  - 11–15 cm: Red & Green ON, Blue OFF.  
  - 16–20 cm: Red ON, others OFF.  
  - >20 cm: All LEDs OFF, buzzer OFF.  
- **Continuous Updates:** System provides real-time feedback for safe parking.

---  
