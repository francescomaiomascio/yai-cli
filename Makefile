# ==========================================
# YAI CLI Build System (Standalone)
# ==========================================

CC ?= cc

# ---- Local repo layout ----
ROOT_DIR := $(abspath .)

# Compat con orchestrator (se mai lo richiamassi) oppure standalone
OUT_BUILD_DIR ?= $(ROOT_DIR)/build
OUT_BIN_DIR   ?= $(ROOT_DIR)/dist/bin

BUILD_DIR := $(OUT_BUILD_DIR)
BIN_DIR   := $(OUT_BIN_DIR)

TARGET := $(BIN_DIR)/yai-cli

# ---- Specs (submodule) ----
SPECS_DIR := $(ROOT_DIR)/deps/yai-specs

# ---- Flags ----
CFLAGS ?= -Wall -Wextra -O2 -std=c11 -MMD -MP
CFLAGS += -I$(ROOT_DIR)/include

# Specs include roots:
# - $(SPECS_DIR)        => abilita include tipo <protocol/...> o <vault/...>
# - $(SPECS_DIR)/protocol => abilita include “piatti” tipo <yai_protocol_ids.h>, <transport.h>, <roles.h>, <protocol.h>
# - $(SPECS_DIR)/vault    => abilita include tipo <yai_vault_abi.h>
# - runtime headers        => <rpc_runtime.h>
CFLAGS += -I$(SPECS_DIR)
CFLAGS += -I$(SPECS_DIR)/protocol -I$(SPECS_DIR)/vault -I$(SPECS_DIR)/protocol/runtime

LDFLAGS ?=

# ---- Sources ----
SRCS := \
    src/main.c \
    src/cmd_dispatch.c \
    src/cmd_engine.c \
    src/cmd_kernel.c \
    src/cmd_mind.c \
    src/cmd_root.c \
    src/cmd_ws.c \
    src/cmd_law.c \
    src/cmd_test.c \
    src/cmd_up.c \
    src/env.c \
    src/fmt.c \
    src/paths.c \
    src/rpc.c

OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean dirs

all: dirs $(TARGET)
	@echo "--- [YAI-CLI] Build Complete ---"

dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS)
	@echo "[LINK] CLI: $@"
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: src/%.c | dirs
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

-include $(OBJS:.o=.d)
