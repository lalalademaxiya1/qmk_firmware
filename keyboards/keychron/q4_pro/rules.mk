# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable boot magic
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover
DIP_SWITCH_ENABLE = yes
BLUETOOTH_ENABLE = no
BLUETOOTH_DRIVER = custom
RAW_ENABLE = yes

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
OPT_DEFS += -DNO_USB_STARTUP_CHECK -DENABLE_FACTORY_TEST
OPT_DEFS += -DKC_BLUETOOTH_ENABLE

CUSTOM_MATRIX = lite

VPATH += keyboards/keychron/common
SRC += matrix.c

include keyboards/keychron/bluetooth/bluetooth.mk
