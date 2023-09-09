COMMON_DIR = common
SRC += \
	$(COMMON_DIR)/matrix.c \
	$(COMMON_DIR)/keychron_common.c \
	$(COMMON_DIR)/keychron_ft_common.c \
	$(COMMON_DIR)/indicator.c

VPATH += $(TOP_DIR)/keyboards/keychron/$(COMMON_DIR)
