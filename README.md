# ECU Display running on RPi

LVGL configured to work with /dev/fb0 on Linux.

When cloning this repository, also make sure to download submodules (`git submodule update --init --recursive`) otherwise you will be missing key components.

## Clone the project
```
git clone git@github.com:hptechdesign/rpi_ecu_display.git
cd rpi_ecu_display/
git submodule update --init --recursive
```

## Recommended build tools and required dependencies: 

  - MSYS2:
    - https://www.msys2.org/wiki/MSYS2-installation/ 
    - Follow the installation instructions, then open the MSYS2 terminal [from start menu, or ```C:\msys64\ucrt64.exe```]
    - Type ```pacman -Syuu``` to update all packages. If the terminal closes, run it again until all updates are complete.
    - Next install the following minimum packages:
  - MINGW64 compiler toolchain:
    - ```pacman -S mingw-w64-ucrt-x86_64-toolchain ```
  - CMAKE
    - ```pacman -S mingw-w64-x86_64-cmake```
  - SDL2 graphics drivers (only required for the windows/SDL build, not RPI):
    - ```pacman -S mingw-w64-x86_64-SDL2```


## RPI cross-compilation toolchain

Download the pre-built windows toolchain for raspberry pi from here (select compatible version, e.g. Bullseye):
https://gnutoolchains.com/raspberry/

Set up environment variable RPIDEV_LOC, and refer to the following document:
https://www.codeproject.com/Articles/1279667/Toolset-to-Cross-Compile-Remote-Debug-Raspberry-fr

Using this information you should be able to modify the rpi_ecu_display project's launch.json and tasks.json to fit your environment. 

## Building

### For Windows:
  - Delete the top-level ```CMakeLists.txt``` file
  - Copy and rename ```CMakeListsSDL.txt``` to ```CMakeLists.txt```
  - Open ```ecu_configs.h```, set ```SDL_ECU_DISPLAY=1``` and ```RPI_ECU_DISPLAY=0```


### For RPI
  - Delete the top-level ```CMakeLists.txt``` file
  - Copy and rename ```CMakeListsRPI.txt``` to ```CMakeLists.txt```
  - Open ```ecu_configs.h```, set ```RPI_ECU_DISPLAY=1``` and ```SDL_ECU_DISPLAY=0```

----

Derived from the LVGL Framebuffer Demo project and its related sub modules:
[https://github.com/lvgl/lv_port_linux_frame_buffer.git].

See this blog post for a step by step tutorial for deriving from scratch:
[https://blog.lvgl.io/2018-01-03/linux_fb]


