# RGB Lamp

### Schematic on NodeMCU

![nodemcu rgb-lamp fritzing schematic](https://raw.githubusercontent.com/lvidarte/esp8266/master/examples/rgb-lamp/rgb-lamp.png)

### Schematic on ESP12E + CP2102 USB-UART converter

![esp12e rgb-lamp fritzing schematic](https://raw.githubusercontent.com/lvidarte/esp8266/master/examples/rgb-lamp/rgb-lamp-esp12e.png)

![esp12e pinout](https://raw.githubusercontent.com/lvidarte/esp8266/master/examples/rgb-lamp/esp12e-pinout.png)

#### ESP8266 Bootloader Modes

The bootloader can go into a number of modes depending on the state of GPIOs 0, 2 and 15. The two useful modes are the UART download mode (for flashing new firmware) and the flash startup mode (which boots from flash).

 | GPIO 0 | GPIO 2 | GPIO 15
-|--------|--------|--------
UART Download Mode (Programming) | 0 | 1 | 0
Flash Startup (Normal) | 1 | 1 | 0
SD-Card Boot | 0 | 0 | 1
