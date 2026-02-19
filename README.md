# S2000-CR-Shift-Light

2008+ clusters already have the space where the LED would be if it was soldered onto the PCB. I added a green LED Diode and removed the paint that blocks this hole on the lens with some alcohol. Eventually I would like to replace the LED with an RGB one and update the code to maybe light up solid red when the RPMs approach 7800-8000.

Currently it is programmed as:

6000 RPM, start flashing at a 500ms rate
Ramp up at a linear rate to 100ms once RPMs approach 7800
Stay lit at >= 7800 RPM
Wiring was very simple:

12V to VIN
Chassis to GND
LED to D13
Tachometer pulse signal to D2 (with a voltage divider in between)
Voltage divider was very simple to make with two resistors:

12V Pulsing Signal ---- R1 (4.7kΩ) ---- Arduino Pin (e.g., D2) | R2 (2.2kΩ) | GND

In this repository you will find;

The .ino file that you can upload directly to your Arduino


