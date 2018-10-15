Stepper motors are slightly different from servo motors. 
A stepper motor has a limit on speed. As the stepper runs faster the torque falls. A stepper can be used with low ratio gearboxes/belt drives. A servo motor on the other hand has a better torque curve and is able to be run faster. 3000 - 5000 RPM is typical. (Source: https://forum.arduino.cc/index.php?topic=122529.0)

A huge disadvantage with steppers is that they need 5 pins to function. If anyone remembers from our first few classes, each port on the HCDM is connected to one pin of the micro-controller (Teensy 3.2). This puts the stepper at a major disadvantage. 
I would encourage everyone to use servos instead of steppers. However, if you think the steppers are better for your application, feel free to play around with these as well. 

I would recommend reaching out to me if you hope to use the steppers. 