# DipDucky
ATtiny85 Rubber Ducky with a dip switch to select between 8 different payloads.

![dip_duck](https://user-images.githubusercontent.com/42423946/160273373-ee1496fa-4a7e-4f4f-bdfb-0e9e3ed644ac.jpg)

## Parts

* ATTiny85
* 3-Position Dip Switch

## Tools 

* Soldering equipment
* Something pointy and sharp (I used pointy tweezers)
* Multimeter (recommended)

## Schematic
![dip_duck_schematic](https://user-images.githubusercontent.com/42423946/160273995-f6b0d499-f9a3-4f9e-8ab8-acbf9d599905.png)

Note: The orientation of the dip switch does not matter.

## There are 6 IO-Pins, why not use a 6-position dip switch?
The pins P3 and P4 are connected to the USB data lines which are needed for the "keyboard" communication with the Computer. P5 by default is the reset pin, if you disable that you could use it as additional pin and add another 1-position dip switch there. I just didn't bother.

## P1 is connected to the onboard LED, which needs to be removed

To be able to use P1 as an input pin you need to remove/destroy the onboard LED (marked in the picture below) or somehow else disconnect the circuit it's on. For me it was too small to desolder it so I used pointy tweezers to scratch it off the board and therefore destroying it. Use your multimeter to confirm the circuit is broken.

![digitiny85_led](https://user-images.githubusercontent.com/42423946/160274775-9dd30dbc-3d09-4835-92a6-d8b454c36b39.png)

## Programming

To upload sketches to a Digispark ATtiny85 there are plenty of tutorials online. I've included a sketch with some example payloads in the dip_ducky.ino file.
It includes an (incomplete) mapping between US and German keyboard layouts.

Payload selection via the dip switch is counting in binary. Meaning all dips down is payload 0, first up is payload 1, the second one is 2 and the third one 4. So all up is payload 7.
