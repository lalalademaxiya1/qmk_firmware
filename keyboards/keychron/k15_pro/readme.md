# Keychron K15 Pro

![Keychron K15 Pro]

A customizable 75% ergonomic keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron K15 Pro
* Hardware Availability:

Make example for this keyboard (after setting up your build environment):

    make keychron/k5_pro/ansi_encoder/rgb:default
    make keychron/k5_pro/ansi_encoder/white:default
    make keychron/k5_pro/jis_encoder/rgb:default
    make keychron/k5_pro/jis_encoder/white:default

Flashing example for this keyboard:

    make keychron/k15_pro/ansi_enoder/rgb:default:flash
    make keychron/k15_pro/ansi_enoder/white:default:flash
    make keychron/k15_pro/jis_enoder/rgb:default:flash
    make keychron/k15_pro/jis_enoder/white:default:flash

## bootloader

Enter the bootloader in two ways:

* **Bootmagic reset**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.
* **Physical reset button**: Briefly press the RESET button under the spacebar.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
