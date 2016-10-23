A4982StepperDriver
=============

A4982 and generic two-pin stepper motor driver library.
Currently supported: 
   - <a href="http://store.ivc.no/product/makerbot-mightystep17">A4982</a> Stepper Motor Driver up to 1:16
   - any 2-pin stepper via DIR and STEP pins.

Motors
======

4-wire bipolar stepper motor or some 6-wire unipolar in 4-wire configuration (leaving centers out).

Connections
===========

Minimal configuration from <a href="https://www.pololu.com/product/2134">Pololu DRV8834 page</a>:

<img src="https://a.pololu-files.com/picture/0J4344.600.png">

Pin-out from <a href="http://store.ivc.no/product/makerbot-mightystep17">MightyStep17 page</a>:

<img src="http://store.ivc.no/images/mightstep_overview_rev1_th.jpg">


Wiring
======

- Arduino to driver board:
    - DIR - D8
    - STEP - D9
    - SLEEP - HIGH (Vdd)
    - RESET - HIGH (Vdd)
    - GND - Arduino GND
    - GND - Motor power GND
    - VMOT - Motor power (check driver-specific voltage range)
    - A4982 microstep control
      - MS1/MODE0 - D10
      - MS2/MODE1 - D11
    - ~ENABLE (optional) recommend D13 to visually check if coils are active

- driver board to motor (this varies from motor to motor, check motor coils schematic).
  I just list the motor wires counter-clockwise
    - A1 - RED
    - A2 - GRN
    - B1 - YEL
    - B2 - BLU 

- 100uF capacitor (can) between GND - VMOT 
- Set the max current on the driver board to the motor limit (see below).
- Have a motor power supply that can deliver that current.

Set Max Current
===============

The max current is set via the Vref pin on board. It can be adjusted digitally
via a digital voltage adjuster or via a potentiometer. The range is 0V to 4.32V for 0 to 2A.
The formula is V = I*8*R where I=max current, R=current sense resistor installed onboard (0.27 Ohm)

- A4982 board, R=0.27 and then V = 2.16 * max current(A). 
  For example, for 1A you will set it to 2.16V.

Code
====

See the BasicStepperDriver example for a generic driver that should work with any board
supporting the DIR/STEP indexing mode.

The Microstepping example works with a A4982 board.

Hardware
========
- Arduino-compatible board
- A <a href="http://store.ivc.no/product/makerbot-mightystep17">A4982 stepper motor driver</a>
- A <a href="http://www.circuitspecialists.com/stepper-motor">Stepper Motor (e.g. NEMA17)</a>
- 1 x 100uF capacitor
