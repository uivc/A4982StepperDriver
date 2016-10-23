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
const uint8_t A4982::MS_TABLE1[] = {0b00, 0b01, 0b10, 0b11};
const uint8_t A4982::MS_TABLE2[] = {1, 2, 4, 16};

/*
 * Basic connection: only DIR, STEP are connected.
 * Microstepping controls should be hardwired.
 */
A4982::A4982(int steps, int dir_pin, int step_pin)
:BasicStepperDriver(steps, dir_pin, step_pin)
{
    this->init();	
}

A4982::A4982(int steps, int dir_pin, int step_pin, int enable_pin)
:BasicStepperDriver(steps, dir_pin, step_pin, enable_pin)
{
    this->init();	
}

/*
 * Fully wired.
 * All the necessary control pins for A4982 are connected.
 */
A4982::A4982(int steps, int dir_pin, int step_pin, int ms1_pin, int ms2_pin)
:BasicStepperDriver(steps, dir_pin, step_pin),
    ms1_pin(ms1_pin), ms2_pin(ms2_pin)
{
    this->init();	
}

A4982::A4982(int steps, int dir_pin, int step_pin, int enable_pin, int ms1_pin, int ms2_pin)
:BasicStepperDriver(steps, dir_pin, step_pin, enable_pin),
	ms1_pin(ms1_pin), ms2_pin(ms2_pin)
{
    this->init();	
}

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
unsigned A4982::setMicrostep(unsigned _microsteps){

    BasicStepperDriver::setMicrostep(_microsteps);

    if (!IS_CONNECTED(ms1_pin) || !IS_CONNECTED(ms2_pin)){
        return this->microsteps;
    }

    const uint8_t* ms_table1 = this->getMicrostepTable1();
    const uint8_t* ms_table2 = this->getMicrostepTable2();
    size_t ms_table_size = this->getMicrostepTableSize();
    int i = 0;
    while (i < ms_table_size){
		uint8_t ms_set_step = ms_table2[i];
        if (_microsteps == ms_set_step){
            uint8_t mask = ms_table1[i];
            digitalWrite(ms2_pin, mask & 2);
            digitalWrite(ms1_pin, mask & 1);
            break;
        }
        i++;
    }	
    return this->microsteps;
}

const uint8_t* A4982::getMicrostepTable1(){
    return A4982::MS_TABLE1;
}

const uint8_t* A4982::getMicrostepTable2(){
    return A4982::MS_TABLE2;
}

size_t A4982::getMicrostepTableSize(){
    return sizeof(A4982::MS_TABLE1);
}

unsigned A4982::getMaxMicrostep(){
    return A4982::MAX_MICROSTEP;
}
