# Self Balancing Robot

A two-wheeled, self-balancing robot driven by a PID controller and a complementary filter.

## Demo Video
[![Self Balancing Robot PID](https://img.youtube.com/vi/EBAI_rJyQvA/0.jpg)](https://www.youtube.com/shorts/EBAI_rJyQvA)

## Hardware
* **Motor:** N20 DC Motors 6V 500RPM
* **Motor-Driver:** DRV8833
* **Microcontroller:** ESP32 DevKit
* **IMU:** MPU6050
* **Chassis:** Custom 3D-printed enclosure

## Software
* **Language:** C++ (PlatformIO)
* **GUI:** Python, PyQt5
* **Filter:** Complementary Filter
* **Controller:** PID

## Problems and Solutions

### Motor does not turn because of deadzone
* **Problem:** The motors have a deadzone that changes depending on the weight of the robot.
* **Solution:** I built a custom tool to dynamically change the PWM value via a PyQt5 GUI. This calibration tool can easily be reused in future projects.

### Motors react too late to balance the robot
* **Problem:** The motors reacted too slowly to keep the robot balanced.
* **Solution:** I went through multiple iterations. First, I realized the initial motors were incorrect, so I switched to N20 Motors with 500RPM. When the problem persisted, I tried raising the center of gravity, which also didn't work. Ultimately, I concluded that the motors were too weak for the robot's overall weight. I replaced the motor driver with a smaller, lighter one and redesigned the physical construction to be much more compact. Since the motors also had a deadzone, I used my custom GUI (linked below) to find the exact minimum PWM value needed to spin the motors.
* **Link:** [https://github.com/DanielPelzel/pwm-motor-calibrator]

### Noise in the Angle Graph
* **Problem:** There is too much noise in the angle data, caused by the limitations of the complementary filter and electromagnetic interference (EMI) between the motor driver and the MPU6050.
* **Status:** I decided to conclude this project as a successful proof of concept and move on to new mechatronic challenges. 
* **Possible Solutions:** Upgrading from a complementary filter to a Kalman filter would yield smoother data. Furthermore, physically relocating the motor driver further away from the MPU6050 would mitigate the electromagnetic interference.

### Complicated PID Tuning
* **Problem:** Tuning the PID controller was very tedious because I had to edit and flash the code after every single adjustment.
* **Solution:** I developed a PyQt5 GUI to monitor the PWM output and the robot's angle in real-time, allowing me to tweak the PID values on the fly while the robot is running.

## What I Learned
* Implementing and tuning a PID controller
* Creating electronic schematics
* Adapting mechanical designs to specific hardware constraints (motor specifications)
* Implementing a complementary filter for sensor fusion
* Building PyQt5 tools to calibrate drivers and tune PID controllers
* Identifying and handling electromagnetic interference (EMI) in hardware design

## Schematic
![Schematic](docs/Schematic.png)
