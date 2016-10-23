/*
 * Microstepping demo
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
#define ENBL 10

// 2-wire basic config, microstepping is hardwired on the driver
// BasicStepperDriver stepper(DIR, STEP);

// microstep control for A4988
#define MS1 11
#define MS2 12
A4982 stepper(MOTOR_STEPS, DIR, STEP, ENBL, MS1, MS2);

void setup() {
    /*
     * Set target motor RPM.
     * These motors can do up to about 200rpm.
     * Too high will result in a high pitched whine and the motor does not move.
     */
    stepper.setRPM(60);
}

void loop() {
    /*
     * Moving motor at full speed is simple:
     */
    stepper.setMicrostep(1); // make sure we are in full speed mode

    // these two are equivalent: 180 degrees is 100 steps in full speed mode
    stepper.move(100);
    stepper.rotate(180);

    // one full reverse rotation
    stepper.move(-100);
    stepper.rotate(-180);

    delay(1000);

    /*
     * Microstepping mode: 1,2,4,16
     * Mode 1 is full speed.
     * Mode 16 is 16 microsteps per step.
     * The motor should rotate just as fast (set RPM),
     * but movement precision is increased.
     */
    stepper.setMicrostep(2);

    // 180 degrees now takes 100 * 8 microsteps
    stepper.move(100*8);
    stepper.rotate(180);

    // as you can see, using degrees is easier
    stepper.move(-100*8);
    stepper.rotate(-180);

    delay(1000);

    /*
     * Microstepping mode 4 microsteps
    */
    stepper.setMicrostep(4);

    // 180 degrees now takes 100 * 8 microsteps
    stepper.move(100*8);
    stepper.rotate(180);

    // as you can see, using degrees is easier
    stepper.move(-100*8);
    stepper.rotate(-180);

    delay(1000);

    /*
     * Microstepping mode 16 microstep
    */
    stepper.setMicrostep(16);

    // 180 degrees now takes 100 * 8 microsteps
    stepper.move(100*8);
    stepper.rotate(180);

    // as you can see, using degrees is easier
    stepper.move(-100*8);
    stepper.rotate(-180);

    delay(2000);
}