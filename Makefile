CC       := gcc
STD      := -std=c99

INCLUDE  := -Iinclude -Isrc

WARNINGS := \
	-Werror \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wshadow \
	-Wconversion \
	-Wsign-conversion \
	-Wcast-qual \
	-Wwrite-strings \
	-Wformat=2 \
	-Wundef \
	-Wstrict-prototypes \
	-Wold-style-definition \
	-Wimplicit-fallthrough \
	-Wlogical-op \
	-Wcast-align \
	-Wvla \
	-Wnull-dereference \
	-Wdouble-promotion \
	-Wformat-overflow=2 \
	-Wformat-truncation=2 \
	-Walloc-zero \
	-Warray-bounds=2 \
	-Wstringop-overflow=4 \
	-Wstrict-overflow=5 \
	-Wswitch-enum \
	-Wpointer-arith \
	-Winit-self

CPPFLAGS := -D_POSIX_C_SOURCE=200809L $(INCLUDE)

CFLAGS  := $(STD) $(WARNINGS) -MMD -MP

LDFLAGS :=

AR      := ar
ARFLAGS := rcs

SRC_DIR   := src
BUILD_DIR := build
LIB_DIR   := lib

TARGET    := $(LIB_DIR)/liblcwf.a

SRCS      := $(shell find $(SRC_DIR) -name '*.c')
OBJS      := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS      := $(OBJS:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) | $(LIB_DIR)
	@$(AR) $(ARFLAGS) $@ $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

clean:
	@rm -rf $(BUILD_DIR) $(LIB_DIR)

-include $(DEPS)
