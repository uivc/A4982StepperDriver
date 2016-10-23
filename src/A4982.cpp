/*
 * A4982 - Stepper Motor Driver Driver
 * Indexer mode only.

 * Copyright (C)2015 Laurentiu Badea
 * Copyright (C)2016 ivc
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include "A4982.h"

/*
 * Microstepping resolution truth table (Page 6 of A4982-Datasheet.pdf)
 * 0bMS2,MS1 for 1,2,4,16 microsteps - A4982 cannot do 8th step
 */
const uint8_t A4982::MS_TABLE[] = {0b00, 0b01, 0b10, 0b11};

/*
 * Basic connection: only DIR, STEP are connected.
 * Microstepping controls should be hardwired.
 */
A4982::A4982(int steps, int dir_pin, int step_pin)
:BasicStepperDriver(steps, dir_pin, step_pin)
{}

A4982::A4982(int steps, int dir_pin, int step_pin, int enable_pin)
:BasicStepperDriver(steps, dir_pin, step_pin, enable_pin)
{}

/*
 * Fully wired.
 * All the necessary control pins for A4982 are connected.
 */
A4982::A4982(int steps, int dir_pin, int step_pin, int ms1_pin, int ms2_pin)
:BasicStepperDriver(steps, dir_pin, step_pin),
    ms1_pin(ms1_pin), ms2_pin(ms2_pin)
{}

A4982::A4982(int steps, int dir_pin, int step_pin, int enable_pin, int ms1_pin, int ms2_pin)
:BasicStepperDriver(steps, dir_pin, step_pin, enable_pin),
ms1_pin(ms1_pin), ms2_pin(ms2_pin)
{}

void A4982::init(void){
    BasicStepperDriver::init();

    if (!IS_CONNECTED(ms1_pin) || !IS_CONNECTED(ms2_pin)){
        return;
    }

    pinMode(ms1_pin, OUTPUT);
    pinMode(ms2_pin, OUTPUT);
}

/*
 * Set microstepping mode (1:divisor)
 * Allowed ranges for A4982 are 1:1 to 1:16 excl. 1:8
 * If the control pins are not connected, we recalculate the timing only
 */
unsigned A4982::setMicrostep(unsigned microsteps){
    BasicStepperDriver::setMicrostep(microsteps);

    if (!IS_CONNECTED(ms1_pin) || !IS_CONNECTED(ms2_pin)){
        return this->microsteps;
    }

    const uint8_t* ms_table = this->getMicrostepTable();
    size_t ms_table_size = this->getMicrostepTableSize();

    int i = 0;
    while (i < ms_table_size){
        if (this->microsteps & (1<<i)){
            uint8_t mask = ms_table[i];
            digitalWrite(ms2_pin, mask & 2);
            digitalWrite(ms1_pin, mask & 1);
            break;
        }
        i++;
    }
    return this->microsteppingteps;
}

const uint8_t* A4982::getMicrostepTable(){
    return A4982::MS_TABLE;
}

size_t A4982::getMicrostepTableSize(){
    return sizeof(A4982::MS_TABLE);
}

unsigned A4982::getMaxMicrostep(){
    return A4982::MAX_MICROSTEP;
}
