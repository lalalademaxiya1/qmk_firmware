# List of all the board related files.
# BOARDSRC = $(CHIBIOS)/os/hal/boards/ST_STM32F401C_DISCOVERY/board.c
BOARDSRC = $(BOARD_PATH)/board/board.c

# Required include directories
# BOARDINC = $(CHIBIOS)/os/hal/boards/ST_STM32F401C_DISCOVERY
BOARDINC = $(BOARD_PATH)/board

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
