/*
 * Copyright (c) 2022 by Jeff Reynolds <jeff-xyzzy@live.com>
 *
 * Analog Devices Octal 8-bit DAC (AD8801) library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 3, both as
 * published by the Free Software Foundation.
 */

/*
 * Analog Devices Octal 8-bit DAC
 * Datasheet: https://www.analog.com/media/en/technical-documentation/dzata-sheets/AD8801_8803.pdf
 *
 */

/* Arduino Uno pins used in this sample:
 *  SDI interface:
 *      Digital pin 10 (SS pin)    [AD8801 pin 7    (CS)]
 *      Digital pin 11 (MOSI pin)  [AD8801 pin 10   (SDI)]
 *      Digital pin 12 (MISO pin)  [Not necessary]
 *      Digital pin 13 (SCK pin)   [AD8801 pin 9    (CLK)]
 *
 *  Optional controls:
 *      Digital pin 5              [AD8801 pin 15   (RS)]
 *      Digital pin 6              [AD8801 pin 6    (SHDN)]
 */

#include "AD8801.h"

#define RS 5
#define SHDN 6

AD8801 dac(RS, SHDN);
// If optional controls are unnecessary, use AD8801::AD8801() constructor

void setup()
{
    SPI.begin();
    Serial.begin(115200);
    while (!Serial) {
        // Wait until connection established
    }

    Serial.println("Connection established");
    dac.begin();
}

void loop()
{
    int bytesAvailable = Serial.available();
    if (bytesAvailable > 0)
    {
        String input = Serial.readStringUntil('\n');
        Serial.print("Command: ");
        Serial.println(input);
        if (input == "reset")
        {
            dac.reset();
            Serial.println("AD8801: All outputs reset to mid-point");
        }
        else if (input == "shutdown")
        {
            dac.shutdown();
            Serial.println("AD8801: Power state: Shutdown");
        }
        else if (input == "resume")
        {
            dac.resume();
            Serial.println("AD8801: Power state: Normal");
        }
        else
        {
            int value = input.toInt(); // Note: If toInt() fails it returns 0
            if (value >= 0 and value < 256)
            {
                // Write the value to control AD8801 output 0.
                dac.set(0, value);
                Serial.print("AD8801: Output 0 set to: ");
                Serial.println(value);
            }
        }
    }
}