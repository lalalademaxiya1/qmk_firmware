# Keychron K17 Pro

![Keychron K17 Pro](https://i.imgur.com/6dAZOkp.jpg)

A wireless custom mechanical 96% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron K17 Pro
* Hardware Availability: [Keychron](https://www.keychron.com)

Make example for this keyboard (after setting up your build environment):

    make keychron/k17_pro/ansi_encoder:default
    make keychron/k17_pro/iso_encoder:default

Flashing example for this keyboard:

    make keychron/k17_pro/ansi_encoder:default:flash
    make keychron/k17_pro/iso_encoder:default:flash

## bootloader

Enter the bootloader in two ways:

* **Bootmagic reset**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.
* **Physical reset button**: Briefly press the RESET button under the spacebar.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
