# WIP Schnorr Curve25519 on Raspberry Pi Pico

This codebase contains code to run curve25519 on a Raspberry Pi Pico. Both source code and test inspiration are taken from repo's from Adam Langley, who in turn based their code on Dan Bernstein's original implementation of curve25519. 

Source code curve25519: [repo](https://github.com/skeeto/enchive/blob/master/src/curve25519-donna.c)

Test code is based on: [repo](https://github.com/agl/curve25519-donna/blob/master/test-curve25519.c)



## Development Sources

### Curve25519

The curve25519 implementation comes from [curve25519-donna](https://github.com/skeeto/enchive/blob/master/src/curve25519-donna.c) (Adam Langley), who in turn based their code on Dan Bernstein's original implementation of curve25519. 

### Randomness

For testing purposes, randomness is generated. This is not suitable for cryptography purposes and only for testing. This code comes from https://forums.raspberrypi.com//viewtopic.php?f=145&t=302960. 

### SHA256

The SHA256 hashing functionality is extracted from [mbed TLS](https://github.com/wolfeidau/mbedtls/tree/master). 

## Preparation

### Get started with the Raspberry Pi Pico (C)

There are various instructions to be found for this, for example the official documentation [here](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf). 

The following commands follow the steps from [this blogpost](https://www.robertthasjohn.com/post/how-to-set-up-the-raspberry-pi-pico-for-development-on-macos), which is tailored to MacOS. 

Install toolchain:
```
brew install cmake
brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc
```

Install `pico-sdk`:
```
git clone -b master https://github.com/raspberrypi/pico-sdk.git 
cd pico-sdk
git submodule update --init
```
Add the location of this sdk to you (`bash_`)`profile` for `PICO_SDK_PATH`. 

### Get Output from Raspberry Pi Pico in console

To see printed output, `minicom` could be used. 

Using brew, install with

```
brew install minicom
```

This gets started easily by using the command `minicom` in any console. In the settings (which can be changed using `minicom -s`), the correct port for the device can be used. Check what the location of the Raspberry Pi Pico is using:

```
ls -l /dev/tty.*
```

An example of what it could be: `/dev/tty.usbmodem14401`.

Note: this can change after (re)loading code on it, so make sure to double check. 

## Build & Run

In `CMakeLists.txt`, add 
```
set(PICO_SDK_PATH "xxx/pico-sdk")
```
with the correct path to the pico-sdk. 

With the following steps:
```
cd build
cmake ..
make
```

Now, press the BOOTSEL button on the Raspberry Pi Pico and connect to the laptop. Open the folder of the device and drag the `build/schnorr_curve25519.uf2` to it. The code is now loaded onto the device.

It should automatically run the code in `schnorr_curve25519.c`, which has a test in the `main` function. Testvalues are printed to the console - which is visible for example using `minicom` (see steps above).

## Additional info
This info is not needed to run this project, but was used to get it started. 

### Pico-project-generator

This project was created using the `pico-project-generator`:
```
git clone https://github.com/raspberrypi/pico-project-generator.git
```

#### Generate a new project with pico-project-generator

To start a new project, you can use the GUI.
```
cd pico-project-generator
export PICO_SDK_PATH="xxxxx/pico-sdk"
export DISPLAY=127.0.0.1:0
./pico_project.py --gui
```

Here, enter a name and select the correct folder. The additional option selected for this project apart from the default settings is: `Console over USD`. 
