# ECU Display running on RPi

LVGL configured to work with /dev/fb0 on Linux.

When cloning this repository, also make sure to download submodules (`git submodule update --init --recursive`) otherwise you will be missing key components.

## Clone the project
```
git clone git@github.com:hptechdesign/rpi_ecu_display.git
cd rpi_ecu_display/
git submodule update --init --recursive
```

## Build the project

```
make
sudo make install
```

## Run the demo application

```
demo
```

Derived from the LVGL Framebuffer Demo project and its related sub modules:
[https://github.com/lvgl/lv_port_linux_frame_buffer.git].
See this blog post for a step by step tutorial for deriving from scratch:
[https://blog.lvgl.io/2018-01-03/linux_fb]
