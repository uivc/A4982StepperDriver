/*
 * Clock Microstepping demo
 *
 * Moves the stepper motor like the seconds hand of a watch.
 *
 * Copyright (C)2015 Laurentiu Badea
 * Copyright (C)2016 ivc
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "A4982.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR 8
#define STEP 9

// 2-wire basic config, microstepping is hardwired on the driver
// BasicStepperDriver stepper(DIR, STEP);

// microstep control for A4982
#define MS1 10
#define MS2 11
A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2);

void setup() {
    /*
     * Set target motor RPM.
     */
    stepper.setRPM(1);
    stepper.setMicrostep(1); // make sure we are in full speed mode
}

void loop() {
    /*
     * The easy way is just tell the motor to rotate 360 degrees at 1rpm
     */
    stepper.rotate(360);
}
