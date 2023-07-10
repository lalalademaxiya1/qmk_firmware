OPT_DEFS += -DNO_USB_STARTUP_CHECK -DENABLE_FACTORY_TEST

SRC += matrix.c

include keyboards/keychron/bluetooth/bluetooth.mk
