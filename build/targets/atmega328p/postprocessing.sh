#!/bin/bash
echo "Postprocessing working directory: `pwd`"

avr-objcopy -O ihex -j .text -j .data eos.elf eos.hex                                     #   <- use this to turn into hex file
#avrdude -V -c arduino -p m328p -P /dev/ttyACM1 -e -b 115200 -F -D -U lfuse:w:0x62:m -U hfuse:w:0xD9:m -U efuse:w:0xFF:m -U lock:w:0xFF:m -U flash:w:eos.hex         #     <- use this to upload