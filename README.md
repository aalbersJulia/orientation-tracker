# Orientation-Tracker
Application to display information from a microcontroller using serial communication!

#### Study on microcontrollers, working with serial communication.

This project contains an implementation of oriention tracking with the ATmega328P and the ADXL345 3-axis Accelerometer. The sensor uses the I2C protocol and communicates with the ATmega328P. The data will be processed after which the Roll and Pitch values around the X and Y axes are calculated to determine the orientation of the sensor. This data is serially written by the microcontroller to the PC to create a 3D visualization of the accelerometer. 

The application is created using WPF a UI framework part of .NET


![Alt Image 1](https://user-images.githubusercontent.com/30042039/234247969-e0735f84-2fd0-4278-8a1e-b6bcfa398d12.png)


