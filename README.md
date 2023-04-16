# Dynamite
> A customizable LV2 distortion plugin.

| ![Screenshot of the Clipping panel](https://user-images.githubusercontent.com/24496030/232308846-63d8c4e6-d3b0-4382-b521-5cac8483c6cf.png) | ![Screenshot of the ](https://user-images.githubusercontent.com/24496030/232308851-35e12391-1e0a-4de1-9d3a-1b2e64d6a1cd.png) |
|-----|------|

Dynamite has two modes: *Clipping* and *Distortion*.
*Clipping* works by amplifying the audio signal (the "Drive" setting), cutting it off at a certain frequency (the "Threshold" setting), and then applying makeup gain (the "Gain" setting).
*Transmogrifier* works by rounding the wave to a square wave, cutting out amplitudes below the "noise threshold", and applying makeup gain (generally negative, to prevent hearing loss).

The UI is GTK2-based (since I use Ardour), so it may not work with all DAWs.

## Installation
Dependencies:
- Meson
- gtkmm-2.4
- lv2
- lv2-c++-tools
- libm

```
meson setup builddir --prefix /usr
ninja -C builddir
sudo ninja -C builddir install
```
