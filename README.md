# Embedded Energy-Efficient House

An Arduino-based house demonstrator integrating temperature measurement, thermal actuation and motorized mechanisms. The project connects embedded control software with an energy-efficiency study and a physical model.

## Embedded architecture

The firmware reads a **TCN75A temperature sensor over I²C** and presents information on a **20 × 4 I²C LCD**. Buttons select operating modes. GPIO and PWM outputs drive heating, a Peltier element, ventilation and a simulated sun source; a stepper motor and servo control the mechanical demonstration.

| Interface | Implementation |
| --- | --- |
| Temperature acquisition | TCN75A at address `0x48`, local C++ driver |
| Display | LCD at address `0x27` |
| User input | Buttons with internal pull-ups |
| Actuation | Heater, Peltier, fan, light, stepper and servo |
| Diagnostics | Serial output at 9600 baud |

## Repository guide

- [arduino](arduino/): application sketch, sensor driver and shutter support.
- [cad](cad/): mechanical design files.
- [documentation](documentation/): report and poster.
- [assets](assets/): prototype photographs.
- [tests](tests/): host-side checks and Arduino stubs.

## Getting started

Open the sketch in Arduino IDE and install its LCD, stepper and servo dependencies. Confirm the pin assignments in the sketch against the wiring before uploading.

The supplied software includes demonstration modes and component-level tests. Full thermal regulation and assembled-system behaviour require validation on the physical prototype.
