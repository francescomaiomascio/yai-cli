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
SPECS_INC_PROTOCOL := $(SPECS_DIR)/specs/protocol/include
SPECS_INC_VAULT := $(SPECS_DIR)/specs/vault/include
SPECS_INC_RUNTIME := $(SPECS_DIR)/specs/protocol/runtime/include

# ---- Flags ----
CFLAGS ?= -Wall -Wextra -O2 -std=c11 -MMD -MP
CFLAGS += -I$(ROOT_DIR)/include

CFLAGS += -I$(SPECS_DIR)
CFLAGS += -I$(SPECS_INC_PROTOCOL) -I$(SPECS_INC_VAULT) -I$(SPECS_INC_RUNTIME)

LDFLAGS ?=

# ---- Sources ----
SRCS := \
    src/main.c \
    src/cli/dispatch.c \
    src/commands/engine.c \
    src/commands/kernel.c \
    src/commands/mind.c \
    src/commands/root.c \
    src/commands/workspace.c \
    src/commands/law.c \
    src/commands/selftest.c \
    src/commands/up.c \
    src/platform/env.c \
    src/platform/paths.c \
    src/support/fmt.c \
    src/runtime/rpc_client.c

OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean dirs docs docs-clean

all: dirs docs $(TARGET)
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

# -----------------------------------------
# Docs (Doxygen)
# -----------------------------------------
DOXYFILE ?= Doxyfile
DOXYGEN ?= doxygen
DOXY_OUT ?= dist/docs

docs:
	@mkdir -p $(DOXY_OUT)
	@$(DOXYGEN) $(DOXYFILE)
	@echo "[yai-cli] docs: $(DOXY_OUT)/doxygen/html/index.html"

docs-clean:
	@rm -rf $(DOXY_OUT)

-include $(OBJS:.o=.d)
