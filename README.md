# Balancer 
Self Balancing Robot, driving on two wheels

## Hardware 
- **Motor:** N20-Dc-Motors 6V 500RPM
- **Motor-Driver:** DRV8833-Driver
- **Microcontroller:** ESP-32 DevKit
- **IMU:** MPU6050

## Software
- **Language:** C++ (PlatformIO)
- **GUI:** Python, PyQt5
- **Filter:** Complementary Filter
- **Controller:** PID

## Problems and Solutions
### Motor does not turn because of deadspot 
**Problem:** The Motors have a deadspot, that changes depending on the weight of the Robot
**Solution:** To solve this Porblem I build an on Tool to change the PWM value via PyQt5 GUI. The tool can also be used in other Projects. 

### Motor react too late to balance the Robot
**Problem:** The Motor racts too slow to balance the Robot 
**Solution:** I had multiple approaches that did not work out. First of all I came to the Solution, that I had the wrong Motors. So I switched to N20 Motors with 500RPM. But the problem was not fixed yet. I tried hightening the center of Gravity, but this also did not work. In the end I found out that the Motors were too small for the weight of my Robot. So I bought a smaller and lighter Motor-Driver and made the construction much smaller

[Motor Calibration Tool](https://github.com/DanielPelzel/motor-calibration-tool)

## Schematic 
![Schematic](docs/Schematic.png)
