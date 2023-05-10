# Build Options
#   change yes to no to disable
#

SERIAL_DRIVER = usart

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
