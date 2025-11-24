# Code for 6Sens Project : testing the conversion and storage applications of MDBT50Q SoC ADC (AIN1 - P0.03) and SHT31 sensor (I2C)

## Overview
This first code allows us to convert a voltage and digital values and adds processing to it:

 - take sample of battery level (Analog-to-Digital), temperature and humidity levels (serial data)
 - store the different values in an area of partitioned internel flash memory (16kbytes at the end of flash memory)

Storing values ​​in internal memory is, in this example, the way to test the reading, writing and erasing of the 16 kB partition of the internal flash memory of the mcu, intended for data storage.

This is also an opportunity to test interrupt management in the Zephyr environment.

This allows us to test SHT31 environmental sensor and the internal ADC of the MDBT50Q. The final goal will be to send the samples to a lorawan server every 15 minutes

The version of Zephyr RTOS used is the version v4.0.0.

## Board used
Original MDBT50Q board, powered by battery/solar panel. (see 6sens_project repository/hardware part, for more information.)

## Building and Running
The following commands clean build folder, build and flash the sample:

**Command to use**
````
west build -t pristine

west build -p always -b mdbt50q_lora_dev applications/6sens_rtos_bth

west flash --runner jlink