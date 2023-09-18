COMMON_DIR = common
SRC += \
	$(COMMON_DIR)/keychron_common.c \
	$(COMMON_DIR)/keychron_ft_common.c

VPATH ?= $(TOP_DIR)/keyboards/keychron/$(COMMON_DIR)
