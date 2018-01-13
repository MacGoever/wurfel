#!/bin/bash
rm -f Wurfel.elf
rm -f Wurfel.hex
avr-gcc -mmcu=attiny2313 Wurfel.c -Os -std=c99 -o Wurfel.elf
#avr-gcc -mmcu=atmega32 Wurfel.c -Os -std=c99 -o Wurfel.elf
avr-objcopy -O ihex -R .eeprom Wurfel.elf Wurfel.hex
avrdude -c stk500v2 -p t2313 -P /dev/ttyUSB0 -U flash:w:Wurfel.hex:i -U lfuse:w:0x64:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 
#avrdude -c stk500v2 -p m32 -P /dev/ttyUSB0 -U flash:w:Wurfel.hex:i -U lfuse:w:0xe1:m -U hfuse:w:0x99:m
