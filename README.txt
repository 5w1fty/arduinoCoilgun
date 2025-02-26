This is my coilgun project. I Will publish all progress and changes that I made and will make on this repository.

coilgun.ino is the C++ file for the arduino nano.
diagram.json contains the setup in the wokwi simulator


This coilgun will have 10 Stages and will probably be powerd by low-voltage but high-current powersources.
Each of the 10 Stages will consist out of a coil (see specs in calculations.txt), an MOSFET to switch the massive curent on and off
which will be also controlled by a phototransistor, which in turn will also send a signal to the arduino for meassuring.

Because of the very low resistances of both the Coil and MOSFET, they enable the usage of very high currents (talking about 400-1000A pulses)
Here is a List of coil specs on different voltages (using 0,07 Ohm as the entire resistance): 
12V: 
    I = 171A
    P = 2052W
    W = 2J/ms

44,4V (prob. what I'll use):
    I = 634A
    P = 28,1kW
    W = 28,1J/ms

So... On 10 Stages we will habe 10x the Power of one Stage. For every ms the projectile is in the barrel it will gain 28J of energy.
-> Make barrel longer, make more stages, make heavier projectiles, get more energy!

On average a coilgun coilpulse is about 1-10ms long, so here are the folloning projectile energy calculations:
10x 1ms = 281J
10x 10ms = 2,8kJ!

The projectile energy will be somewhere between 281-2810J.
(Remember, this is not using capacitors or HV at all, this is fullauto with max. 2,8kJ/projectile.)
(Using capacitors and better MOSFETS or even IGBTs could leed to more than 5kJ projectile Energy, but losing the fullauto function)
