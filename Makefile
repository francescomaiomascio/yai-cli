# ==========================================
# YAI CLI Build System (Standalone)
# ==========================================

CC ?= cc

# ---- Local repo layout ----
ROOT_DIR := $(abspath .)

OUT_BUILD_DIR ?= $(ROOT_DIR)/build
OUT_BIN_DIR   ?= $(ROOT_DIR)/dist/bin

BUILD_DIR := $(OUT_BUILD_DIR)
BIN_DIR   := $(OUT_BIN_DIR)

TARGET := $(BIN_DIR)/yai
LEGACY_TARGET := $(BIN_DIR)/yai-cli

# ---- Specs (submodule) ----
LAW_DIR := 20 20 101 12 61 79 80 81 98 702 701 33 100 204 250 395 398 399 400ROOT_DIR)/deps/yai-law
LAW_INC_PROTOCOL := 20 20 101 12 61 79 80 81 98 702 701 33 100 204 250 395 398 399 400LAW_DIR)/law/surfaces/protocol/include
LAW_INC_VAULT := 20 20 101 12 61 79 80 81 98 702 701 33 100 204 250 395 398 399 400LAW_DIR)/law/surfaces/vault/include
LAW_INC_RUNTIME := 20 20 101 12 61 79 80 81 98 702 701 33 100 204 250 395 398 399 400LAW_DIR)/law/surfaces/protocol/runtime/include

# ---- Flags ----
CFLAGS ?= -Wall -Wextra -O2 -std=c11 -MMD -MP
CFLAGS += -I$(ROOT_DIR)/include
CFLAGS += -I$((LAW_DIR))
CFLAGS += -I$(LAW_INC_PROTOCOL) -I$(LAW_INC_VAULT) -I$(LAW_INC_RUNTIME)

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
    src/commands/status.c \
    src/platform/env.c \
    src/platform/paths.c \
    src/support/fmt.c \
    src/runtime/rpc_client.c

OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

TEST_BIN_DIR := $(BUILD_DIR)/tests
UNIT_TEST_BIN := $(TEST_BIN_DIR)/unit_parse_test
VECTORS_TEST_BIN := $(TEST_BIN_DIR)/vectors_rpc_test

.PHONY: all clean dirs docs docs-clean test

all: dirs docs $(TARGET)
	@echo "--- [YAI-CLI] Build Complete ---"

dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS)
	@echo "[LINK] CLI: $@"
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@ln -sf yai $(LEGACY_TARGET)

$(BUILD_DIR)/%.o: src/%.c | dirs
	@mkdir -p $(dir $@)
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

# -----------------------------------------
# Tests
# -----------------------------------------
test: $(UNIT_TEST_BIN) $(VECTORS_TEST_BIN)
	@echo "[TEST] $(UNIT_TEST_BIN)"
	@$(UNIT_TEST_BIN)
	@echo "[TEST] $(VECTORS_TEST_BIN)"
	@$(VECTORS_TEST_BIN)
	@echo "--- [YAI-CLI] Tests Complete ---"

$(UNIT_TEST_BIN): tests/unit/parse_test.c | dirs
	@mkdir -p $(TEST_BIN_DIR)
	@$(CC) $(CFLAGS) $< -o $@

$(VECTORS_TEST_BIN): tests/vectors/rpc_vectors_test.c | dirs
	@mkdir -p $(TEST_BIN_DIR)
	@$(CC) $(CFLAGS) $< -o $@

-include $(OBJS:.o=.d)
