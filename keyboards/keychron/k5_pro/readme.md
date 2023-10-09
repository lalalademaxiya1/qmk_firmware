# Keychron K5 Pro

![Keychron K5 Pro](https://github.com/Keychron/ProductImage/blob/main/K_Pro/K5_Pro.JPG?raw=true)

A customizable 100% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron K5 Pro
* Hardware Availability: [Keychron K5 Pro QMK/VIA Wireless Custom Mechanical Keyboard](https://www.keychron.com/products/keychron-k5-pro-qmk-via-wireless-custom-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make keychron/k5_pro/ansi/rgb:default
    make keychron/k5_pro/ansi/white:default
    make keychron/k5_pro/iso/rgb:default
    make keychron/k5_pro/iso/white:default
    make keychron/k5_pro/jis/rgb:default
    make keychron/k5_pro/jis/white:default

Flashing example for this keyboard:

    make keychron/k5_pro/ansi/rgb:default:flash
    make keychron/k5_pro/ansi/white:default:flash
    make keychron/k5_pro/iso/rgb:default:flash
    make keychron/k5_pro/iso/white:default:flash
    make keychron/k5_pro/jis/rgb:default:flash
    make keychron/k5_pro/jis/white:default:flash

## bootloader

Enter the bootloader in two ways:

* **Bootmagic reset**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.
* **Physical reset button**: Briefly press the RESET button under the spacebar.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
