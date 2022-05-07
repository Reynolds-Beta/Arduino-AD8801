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

#include "AD8801.h"

AD8801::AD8801()
{
    this->resetAvailable = false;
    this->powerState = Unused;
}

AD8801::AD8801(byte resetPin, byte shdnPin)
{
    this->resetPin = resetPin;
    this->shdnPin = shdnPin;
    this->resetAvailable = true;
    this->powerState = Normal;
}

void AD8801::begin(bool initializeAsShutdown = false)
{
    if (this->resetAvailable)
    {
        pinMode(resetPin, OUTPUT);
        digitalWrite(this->resetPin, HIGH);
    }

    if (this->powerState != Unused)
    {
        pinMode(shdnPin, OUTPUT);
        this->powerState = Normal;
        if (initializeAsShutdown) 
        {
            this->shutdown();
        }
        else
        {
            this->resume();
        }
    }
}

void AD8801::reset(byte initialValue = 0x80)
{
    if (this->resetAvailable && initialValue == 0x80)
    {
        digitalWrite(this->resetPin, LOW);
        digitalWrite(this->resetPin, HIGH);
    }
    else
    {
        for (int i = 0; i < AD8801_DAC_COUNT; i++)
        {
            this->set(i, initialValue);
        }
    }
}

void AD8801::shutdown()
{
    if (this->powerState != Unused)
    {
        digitalWrite(this->shdnPin, LOW);
        this->powerState = Shutdown;
    }
}

void AD8801::resume()
{
    if (this->powerState != Unused)
    {
        digitalWrite(this->shdnPin, HIGH);
        this->powerState = Normal;
    }
}

AD8801::PowerStates AD8801::getPowerState()
{
    return this->powerState;
}

void AD8801::set(byte dacIndex, byte value)
{
    if (dacIndex < AD8801_DAC_COUNT)
    {
        digitalWrite(SS, LOW);
        SPI.transfer(dacIndex);
        SPI.transfer(value);
        digitalWrite(SS, HIGH);
    }
}

