# Car Parking Sensor System

**ATmega32-Based Proximity Detection System with Real-Time Distance Measurement**

## Table of Contents
- [Project Overview](#project-overview)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
- [System Features](#system-features)
- [Alert System](#alert-system)
- [Pin Configuration](#pin-configuration)
- [Driver Implementation](#driver-implementation)
- [Distance Measurement](#distance-measurement)
- [Development Environment](#development-environment)
- [Operation Procedure](#operation-procedure)
- [Project Structure](#project-structure)
- [License](#license)

## Project Overview

This project implements an intelligent car parking assistance system using the ATmega32 microcontroller and HC-SR04 ultrasonic sensor. The system provides real-time distance measurement with progressive visual and auditory alerts to help drivers park safely and avoid collisions.

The implementation demonstrates advanced embedded systems concepts including ultrasonic distance measurement, ICU-based signal processing, LCD interfacing, layered driver architecture, and real-time feedback systems.

### System Demonstration
![Car Parking Sensor](https://github.com/user-attachments/assets/4e8ff323-0c4a-4098-8eb4-e5b5094a2c42)

## System Architecture

### Layered Architecture Design
```
┌─────────────────────────────────────────┐
│         Application Layer               │
│         └── Car Parking System         │
├─────────────────────────────────────────┤
│         HAL (Hardware Abstraction)      │
│         ├── Ultrasonic Sensor Driver   │
│         ├── LCD Driver (4-bit mode)     │
│         ├── LED Driver                  │
│         └── Buzzer Driver               │
├─────────────────────────────────────────┤
│         MCAL (Microcontroller)          │
│         ├── GPIO Driver                 │
│         └── ICU Driver (Timer1)         │
├─────────────────────────────────────────┤
│         Hardware (ATmega32)             │
└─────────────────────────────────────────┘
```

## Hardware Components

### Core Processing Unit
- **Microcontroller**: ATmega32 @ 16MHz
- **Architecture**: 8-bit AVR RISC processor
- **Memory**: 32KB Flash, 2KB SRAM, 1KB EEPROM

### Sensor and Display System
- **Distance Sensor**: HC-SR04 Ultrasonic Sensor
  - Range: 2cm to 400cm
  - Accuracy: ±3mm
  - Operating Frequency: 40KHz
- **Display**: 16x2 LCD (4-bit mode)
- **Visual Indicators**: RGB LEDs (Red, Green, Blue)
- **Audio Alert**: Active buzzer for proximity warnings

### Interface Components
- **Ultrasonic Sensor Pins**:
  - Trigger: PD7 (Output)
  - Echo: PD6 (Input/ICU)
- **LCD Interface**: 4-bit mode
  - RS: PA1, E: PA2
  - Data: PA3-PA6 (D4-D7)
- **LED Indicators**: PC0 (Red), PC1 (Green), PC2 (Blue)
- **Buzzer**: PC5 (Output)

## System Features

### Distance Measurement
- **Ultrasonic Ranging**: Uses time-of-flight measurement
- **ICU Integration**: Timer1 Input Capture for precise timing
- **Real-time Updates**: Continuous distance monitoring
- **Range**: 2-400cm with centimeter precision

### Display System
- **Distance Display**: Shows current distance in centimeters
- **Warning Messages**: Displays "STOP!" when distance ≤ 5cm
- **Real-time Updates**: Continuous refresh for live feedback
- **Format**: "Distance = XXX cm"

### Progressive Alert System
- **Multi-level Warnings**: Five distinct alert levels
- **Visual Feedback**: Progressive LED activation
- **Audio Alerts**: Buzzer activation for critical proximity
- **Dynamic Behavior**: LEDs flash during emergency situations

## Alert System

### Distance-Based Alert Levels

| Distance Range | Red LED | Green LED | Blue LED | Buzzer | LCD Display |
|---------------|---------|-----------|----------|---------|-------------|
| > 20 cm       | OFF     | OFF       | OFF      | OFF     | Distance only |
| 16-20 cm      | ON      | OFF       | OFF      | OFF     | Distance only |
| 11-15 cm      | ON      | ON        | OFF      | OFF     | Distance only |
| 6-10 cm       | ON      | ON        | ON       | OFF     | Distance only |
| ≤ 5 cm        | FLASH   | FLASH     | FLASH    | ON      | "STOP!" + Distance |

### Alert Logic Implementation
```c
// Progressive LED control based on distance
if(distance >= 20) {
    // All indicators OFF - Safe distance
    LED_off(LED_RED); LED_off(LED_GREEN); LED_off(LED_BLUE);
    Buzzer_off();
}
else if (distance >= 16 && distance <= 20) {
    // Red LED only - Caution zone
    LED_on(LED_RED); LED_off(LED_GREEN); LED_off(LED_BLUE);
}
else if (distance >= 11 && distance <= 15) {
    // Red + Green LEDs - Warning zone
    LED_on(LED_RED); LED_on(LED_GREEN); LED_off(LED_BLUE);
}
else if (distance >= 6 && distance <= 10) {
    // All LEDs ON - Critical zone
    LED_on(LED_RED); LED_on(LED_GREEN); LED_on(LED_BLUE);
}
else {
    // Emergency: Flashing LEDs + Buzzer
    // Implementation includes flashing behavior and "STOP!" message
}
```

## Pin Configuration

### ATmega32 Pin Assignments
```c
// LCD Interface (4-bit mode)
#define LCD_RS_PORT_ID      PORTA_ID
#define LCD_RS_PIN_ID       PIN1_ID
#define LCD_E_PORT_ID       PORTA_ID  
#define LCD_E_PIN_ID        PIN2_ID
#define LCD_DATA_PORT_ID    PORTA_ID
// Data pins PA3-PA6 for D4-D7

// LED Indicators
#define LED_RED_PORT_ID     PORTC_ID
#define LED_RED_PIN_ID      PIN0_ID
#define LED_GREEN_PORT_ID   PORTC_ID
#define LED_GREEN_PIN_ID    PIN1_ID
#define LED_BLUE_PORT_ID    PORTC_ID
#define LED_BLUE_PIN_ID     PIN2_ID

// Buzzer
#define BUZZER_PORT_ID      PORTC_ID
#define BUZZER_PIN_ID       PIN5_ID

// Ultrasonic Sensor
#define ULTRASONIC_TRIGGER_PORT_ID  PORTD_ID
#define ULTRASONIC_TRIGGER_PIN_ID   PIN7_ID
#define ULTRASONIC_ECHO_PORT_ID     PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID      PIN6_ID
```

## Driver Implementation

### Ultrasonic Sensor Driver
```c
// Core ultrasonic driver functions
void Ultrasonic_init(void);              // Initialize ICU and GPIO
void Ultrasonic_Trigger(void);           // Send 10μs trigger pulse
uint16 Ultrasonic_readDistance(void);    // Measure and return distance
void Ultrasonic_edgeProcessing(void);    // ICU callback for timing
```

### Distance Calculation Algorithm
- **Trigger Pulse**: 10μs HIGH pulse on trigger pin
- **Echo Measurement**: ICU captures echo pulse duration
- **Distance Formula**: Distance = (Echo_Time × 17000 × 0.5μs) / 112.1
- **Calibration**: Optimized divisor (112.1) for accurate measurements

### LCD Driver Features
- **4-bit Mode**: Efficient pin usage with PA3-PA6
- **Dynamic Display**: Real-time distance updates
- **Warning Messages**: Context-sensitive text display
- **Cursor Control**: Precise positioning for clean updates

### LED Driver Implementation
- **Individual Control**: Separate functions for each LED
- **Positive Logic**: High = ON, Low = OFF
- **Configurable Pins**: Easy hardware modification
- **State Management**: Synchronized with distance readings

### Buzzer Driver
- **Simple Interface**: On/Off control functions
- **GPIO-based**: Direct microcontroller pin control
- **Emergency Alert**: Activates during critical proximity

## Distance Measurement

### Ultrasonic Ranging Principle
1. **Trigger Phase**: 10μs pulse sent to HC-SR04
2. **Echo Phase**: Sensor returns HIGH pulse proportional to distance
3. **Timing Capture**: ICU measures echo pulse width
4. **Distance Calculation**: Convert time to distance using sound speed

### ICU Configuration
```c
ICU_ConfigType ICU_Config = {
    .clock = F_CPU_8,        // 16MHz/8 = 2MHz timer frequency
    .edge = RAISING          // Detect rising edge first
};
```

### Timing Specifications
- **Timer Frequency**: 2MHz (F_CPU/8)
- **Resolution**: 0.5μs per timer tick
- **Update Rate**: Continuous measurement
- **Accuracy**: ±1cm typical accuracy

## Development Environment

**IDE**: Eclipse IDE for C/C++ Developers  
**Simulation**: Proteus Design Suite 8.0+  
**Compiler**: AVR-GCC with optimization  
**Debugger**: AVR Dragon or USBasp  
**Target**: ATmega32 @ 16MHz  

### Simulation Features
- **Complete System**: All components modeled in Proteus
- **Real-time Behavior**: Accurate sensor and display simulation
- **Interactive Testing**: Virtual distance adjustment
- **Hardware Verification**: Pin-level signal analysis

## Operation Procedure

### System Initialization
1. **Power On**: System initializes all drivers
2. **Display Setup**: LCD shows "Distance = " template
3. **Sensor Ready**: Ultrasonic sensor begins measurements
4. **LED Test**: Brief LED sequence confirms functionality

### Normal Operation
1. **Distance Measurement**: Continuous ultrasonic ranging
2. **Display Update**: Real-time distance on LCD
3. **Alert Processing**: LED and buzzer control based on proximity
4. **Safety Monitoring**: Emergency alerts for critical distances

### Emergency Mode (≤5cm)
1. **Immediate Alert**: All LEDs flash, buzzer sounds
2. **Display Warning**: "STOP!" message on LCD
3. **Continuous Monitoring**: System remains in alert until distance increases
4. **Recovery**: Normal operation resumes when distance > 5cm

## Project Structure

```
Car_Parking_Sensor/
├── Application/
│   ├── Car_Parking_System.c           # Main application logic
│   └── Car_Parking_System.h           # Application header
├── HAL/
│   ├── LCD/
│   │   ├── lcd.c                       # LCD driver implementation
│   │   └── lcd.h                       # LCD driver header
│   ├── LED/
│   │   ├── led.c                       # LED driver implementation
│   │   └── led.h                       # LED driver header
│   ├── Buzzer/
│   │   ├── buzzer.c                    # Buzzer driver implementation
│   │   └── buzzer.h                    # Buzzer driver header
│   └── UltraSonic/
│       ├── ultra_sonic_sensor.c        # Ultrasonic driver implementation
│       └── ultra_sonic_sensor.h        # Ultrasonic driver header
├── MCAL/
│   ├── GPIO/
│   │   ├── gpio.c                      # GPIO driver implementation
│   │   └── gpio.h                      # GPIO driver header
│   └── ICU/
│       ├── icu.c                       # ICU driver implementation
│       └── icu.h                       # ICU driver header
├── Common/
│   ├── std_types.h                     # Standard type definitions
│   └── common_macros.h                 # Common utility macros
├── Documentation/
│   ├── Mini_Project4.pdf               # Project specifications
│   └── README.md                       # This file
├── Simulation/
│   └── Proteus_Project.pdsprj          # Complete Proteus simulation
└── Images/
    └── car_parking_sensor.png          # System demonstration image
```

## System Specifications

### Performance Characteristics
- **Response Time**: < 50ms for distance updates
- **Measurement Range**: 2-400cm
- **Accuracy**: ±1cm for distances < 100cm
- **Update Frequency**: ~20Hz continuous measurement
- **Power Consumption**: < 100mA @ 5V typical

### Safety Features
- **Multi-level Alerts**: Progressive warning system
- **Emergency Stop**: Immediate alerts for critical proximity
- **Fail-safe Design**: Default to warning state on sensor failure
- **Visual Confirmation**: LED status indicates system operation

## License

This project is developed as part of the Standard Embedded Systems Diploma program for educational purposes.

---

**Developed by**: Bassam Ashraf  
**Course**: Standard Embedded Systems Diploma  
**Program**: EDGES Training Program  
**Development Environment**: Eclipse IDE, Proteus Design Suite  
**Language**: C          
**Target Hardware**: ATmega32 Microcontroller  

---

*This car parking sensor system demonstrates professional embedded systems development with emphasis on safety-critical applications, real-time processing, and modular driver architecture. The project showcases integration of multiple hardware components with sophisticated software control for practical automotive assistance applications.*
