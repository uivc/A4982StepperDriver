/*
 * A4982 - Stepper Motor Driver Driver
 * Indexer mode only.
 *
 * Copyright (C)2015 Laurentiu Badea
 * Copyright (C)2016 ivc
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#ifndef A4982_H
#define A4982_H
#include <Arduino.h>
#include "BasicStepperDriver.h"

class A4982 : public BasicStepperDriver {
protected:
    static const uint8_t MS_TABLE[];
    int ms1_pin = PIN_UNCONNECTED;
    int ms2_pin = PIN_UNCONNECTED;
    void init(void);
    // tA STEP minimum, HIGH pulse width (1us)
    static const int step_high_min = 1;
    // tB STEP minimum, LOW pulse width (1us)
    static const int step_low_min = 1;
    // wakeup time, nSLEEP inactive to STEP (1000us)
    static const int wakeup_time = 1000;
    // also 200ns between ENBL/DIR/MSx changes and STEP HIGH

    // Get the microstep table
    virtual const uint8_t* getMicrostepTable();
    virtual size_t getMicrostepTableSize();

    // Get max microsteps supported by the device
    unsigned getMaxMicrostep() override;

private:
    // microstep range (1, 16, 32 etc.) - 16 for A4982/A4988
    static const unsigned MAX_MICROSTEP = 16;

public:
    /*
     * Basic connection: only DIR, STEP are connected.
     * Microstepping controls should be hardwired.
     */
    A4982(int steps, int dir_pin, int step_pin);
    A4982(int steps, int dir_pin, int step_pin, int enable_pin);
    
    /*
     * Fully wired. All the necessary control pins for A4982 are connected.
     */
    A4982(int steps, int dir_pin, int step_pin, int ms1_pin, int ms2_pin);
    A4982(int steps, int dir_pin, int step_pin, int enable_pin, int ms1_pin, int ms2_pin);
    unsigned setMicrostep(unsigned microsteps);
};
#endif // A4982_H
