#!/bin/bash
cd external/ADS || exit
meson setup build
meson compile -C build
sudo meson install -C build