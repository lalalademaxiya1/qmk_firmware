# Keychron K7 Pro

![Keychron K7 Pro](https://github.com/Keychron/ProductImage/blob/main/K_Pro/k7_pro.jpg?raw=true)

A customizable 68 keys low profile switch keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron K7 Pro
* Hardware Availability: [Keychron K7 Pro QMK/VIA Wireless Mechanical Keyboard](https://www.keychron.com/products/keychron-k7-pro-qmk-via-wireless-custom-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make keychron/k7_pro/ansi/rgb:default
    make keychron/k7_pro/ansi/white:default
    make keychron/k7_pro/iso/rgb:default
    make keychron/k7_pro/iso/white:default

Flashing example for this keyboard:

    make keychron/k7_pro/ansi/rgb:default:flash
    make keychron/k7_pro/ansi/white:default:flash
    make keychron/k7_pro/iso/rgb:default:flash
    make keychron/k7_pro/iso/white:default:flash

## bootloader

Enter the bootloader in two ways:

* **Bootmagic reset**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.
* **Physical reset button**: Briefly press the RESET button under the spacebar.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
