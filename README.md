# Arduino-AD8801
Arduino library to control Analog Device's 8801 Octal 8-bit DAC via 3-wire SPI/serial communication.

## Datasheet
https://www.analog.com/media/en/technical-documentation/data-sheets/AD8801_8803.pdf

## Example breadboard wiring for example
Below is the writing diagram used to test /examples/SampleAD8801.ino.</br></br>
* vRef and Vdd (pins 1 and 16, respectively on the AD8801) are tied to the Ardiono Uno's regulated 5v output.
* The sample code only references the first output (pin 2 on the AD8801), which is probed with a DC multimieter to watch the changes
* Output should be between 0 - 5v depending on the DAC value
</br></br>
![This is an image](/Sample%20AD8801.jpg)
