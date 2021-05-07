# Latent AI TinyMLPerf Benchmarks v0.7 Closed Division
## System Overview

This document provides a brief overview of our submission for tinyMLPerf benchmarks v0.7. 
Our submission is based on the Latent AI Efficient Inference Platform (LEIP) SDK product that can 
is easy to use for model optimization. LEIP is model and hardware agnostic.

The Latent AI benchmarks were recorded on the Raspberry Pi 4 using a full-UART implementation. The image for the RPi operating system can be found [here](https://drive.google.com/drive/folders/1i7YFF-2HLTE2k1NL3Y1ZF5HF7JTFHwrX?usp=sharing). 

Latent AI Model Binaries are compiled using Latent AI's proprietary SDK. The SDK can be accessed via an evaluation license (free 30-day trial period). 

## Getting Started

### Setting up UART

Install the image onto the SD Card and boot up the RPI. Open terminal and do the following steps:
1. Start raspi-config: `sudo raspi-config`.
2. Select option 3 - Interface Options.
3. Select option P6 - Serial Port.
4. At the prompt Would you like a login shell to be accessible over serial? answer **'No'**
5. At the prompt Would you like the serial port hardware to be enabled? answer **'Yes'**
6. Exit raspi-config and reboot the Pi for changes to take effect.

### Switching to Full UART

The Raspberry Pi 4 has two UART implementations, mini UART and full UART. By default, mini UART is enabled, but it is unstable and subsequently, not recommended. In this section we highlight how to switch from mini-UART to full-UART using the same IO pins. 

By running `ls -l /dev/` you can see that `serial0` is pointing to `ttyS0`, which is the mini-UART implementation.
```
lrwxrwxrwx 1 root root           7 May  6 20:27 serial0 -> ttyS0
lrwxrwxrwx 1 root root           5 May  6 20:27 serial1 -> ttyAMA0
```
Edit /boot/config.txt (`sudo nano boot/config.txt`) to add the following lines:
```
enable_uart=1
dtoverlay=pi3-miniuart-bt
dtoverlay=disable-bt
```

Restart the pi and then run `ls -l /dev/`. You should see the `serial0` now pointing to `/dev/ttyAMA0`, the full UART implementation.
```
lrwxrwxrwx 1 root root           7 May  6 20:27 serial0 -> ttyAMA0
lrwxrwxrwx 1 root root           5 May  6 20:27 serial1 -> ttyS0
```

Run `stty -F /dev/ttyAMA0 115200 -oddp raw` to activate serial comms as expected.

## Running the DUT for a model

Navigate to the model directory that you would like to test and run:
```
make clean all
./bin/main
```

Now use the runner client.
