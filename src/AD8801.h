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

#ifndef AD8801_H_

    #define AD8801_H_
    #include <Arduino.h>
    #include <SPI.h>

    class AD8801
    {

    #define AD8801_DAC_COUNT 8

    public:
        enum PowerStates
        {
            Unused = 0,
            Normal = 1,
            Shutdown = 2
        };

        AD8801();
        AD8801(byte resetPin, byte shdnPin);
        void begin(bool initializeAsShutdown = false);
        PowerStates getPowerState();
        void set(byte dacIndex, byte value);
        void reset(byte initialValue = 0x80);
        void shutdown();
        void resume();

    private:
        byte resetPin = 0;
        byte shdnPin = 0;
        bool resetAvailable = false;
        PowerStates powerState = Unused;
    };

#endif