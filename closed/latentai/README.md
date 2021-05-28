# Latent AI TinyMLPerf Benchmarks v0.7 Closed Division
## System Overview

This document provides a brief overview of our submission for tinyMLPerf benchmarks v0.7. 
Our submission is based on the Latent AI Efficient Inference Platform (LEIP) SDK product that can 
is easy to use for model optimization. LEIP is model and hardware agnostic.

The Latent AI benchmarks were recorded on the Raspberry Pi 4 using a full-UART implementation.

# Getting Started
Latent AI Model Binaries are compiled using Latent AI's proprietary SDK. The SDK can be accessed via an evaluation license (free 30-day trial period).

The image for the RPi operating system can be found [here](https://drive.google.com/file/d/1zH-Ae6N-UgwEz3gi2X9rxEXq4yhlH2OS/view?usp=sharing). The username for the Pi is `pi`, and the password for this image is `raspberry`

**Note: You must always type `stty -F /dev/ttyAMA0 115200 -oddp raw` in the terminal after each restart of the device. However, it is possible to create a script to launch this command each time during boot up.**

## Quick Start
1. Download the image provided in `Getting Started`.
2. Flash the image on a microSD card (i.e balenaEtcher).
3. Once booted into the OS, open a terminal and type: `stty -F /dev/ttyAMA0 115200 -oddp raw`. This can be achieved in 2 ways.
    - SSH: Connect the Pi via ethernet, and attempt to ping the hostname `latentai-closed-raspberrypi4`.
    - Locally: Plug a monitor, mouse, and keyboard to the Pi. Open up terminal via the desktop GUI.
4. Refer to `Running the DUT for a model`.

## Complete Setup (skip if using Quick Start)
1. [Download the 64-bit Raspberry Pi OS](https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2020-08-24/2020-08-20-raspios-buster-arm64.zip). Unzip the download and flash the image to a microSD card (i.e balenaEtcher).
2. Boot into the OS via either SSH or locally (mouse, keyboard, monitor) and refer to `Setting Up UART` in the `Appendix`. Restart the device (`sudo reboot now`).
3. Once booted into the OS, open a terminal and type: `stty -F /dev/ttyAMA0 115200 -oddp raw`.
    - Note: since the stock image of the Raspberry Pi OS is used, the default hostname should be `raspberry`. The hostname can be changed via `sudo raspi-config` for convenience. The user and password is `pi` and `raspberrypi` respectively.
4. Refer to `Running the DUT for a model`.

## Running the DUT for a model
**Note: As mentioned in `Getting Started`, if you wish to generate the binaries of a given model, please reach out to Latent AI for a free 30-day evaluation license to compile the models in this repository. Then, simply place the binary in the root of the respective benchmark (i.e `closed/latentai/code/ic/ic_int8/ic_int8.so`)**

1. Navigate to the model directory (i.e `closed/latentai/code/ic/ic_int8/ic_int8.so`) that you would like to test and run:
    ```
    make clean all
    ./bin/main
    ```
2. Now use the EEMBC runner client after following the instructions in the runner's readme to obtain the datasets.

# Appendix
## Setting Up UART

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