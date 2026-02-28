# ==========================================
# YAI CLI Build System (SDK-backed)
# ==========================================

CC ?= cc
ROOT_DIR := $(abspath .)

OUT_BUILD_DIR ?= $(ROOT_DIR)/build
OUT_BIN_DIR   ?= $(ROOT_DIR)/dist/bin

BUILD_DIR := $(OUT_BUILD_DIR)
BIN_DIR   := $(OUT_BIN_DIR)

TARGET := $(BIN_DIR)/yai
LEGACY_TARGET := $(BIN_DIR)/yai-cli

# ---- SDK (submodule) ----
SDK_DIR := $(ROOT_DIR)/deps/yai-sdk
SDK_INC := $(SDK_DIR)/include
SDK_LIB := $(SDK_DIR)/dist/lib/libyai_sdk.a

# ---- Law headers (protocol contracts) ----
# NOTE: source of truth is deps/yai-sdk/deps/yai-law (not deps/yai-law in this repo)
LAW_DIR := $(SDK_DIR)/deps/yai-law
LAW_INC_PROTOCOL := $(LAW_DIR)/contracts/protocol/include
LAW_INC_VAULT    := $(LAW_DIR)/contracts/vault/include
LAW_INC_RUNTIME  := $(LAW_DIR)/contracts/protocol/runtime/include

# ---- Flags ----
CFLAGS ?= -Wall -Wextra -O2 -std=c11 -MMD -MP
CFLAGS += -I$(ROOT_DIR)/include
CFLAGS += -I$(SDK_INC)
CFLAGS += -I$(LAW_INC_PROTOCOL) -I$(LAW_INC_VAULT) -I$(LAW_INC_RUNTIME)

LDFLAGS ?=
LDLIBS  ?= $(SDK_LIB)

# ---- Sources (CLI only) ----
SRCS := \
  src/cli/main.c \
  src/cli/porcelain/porcelain.c \
  src/cli/porcelain/porcelain_errors.c \
  src/cli/porcelain/porcelain_help.c \
  src/cli/porcelain/porcelain_output.c \
  src/cli/porcelain/porcelain_parse.c \
  src/support/fmt.c

OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

TEST_BIN_DIR := $(BUILD_DIR)/tests
UNIT_TEST_BIN := $(TEST_BIN_DIR)/unit_parse_test
VECTORS_TEST_BIN := $(TEST_BIN_DIR)/vectors_rpc_test

.PHONY: all clean dirs docs docs-clean test sdk sdk-clean

all: dirs docs sdk $(TARGET)
	@echo "--- [YAI-CLI] Build Complete ---"

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Build SDK as a static library (submodule)
sdk:
	@echo "[SDK] build: $(SDK_DIR)"
	@$(MAKE) -C $(SDK_DIR)

sdk-clean:
	@echo "[SDK] clean: $(SDK_DIR)"
	@$(MAKE) -C $(SDK_DIR) clean

$(TARGET): $(OBJS) sdk
	@echo "[LINK] CLI: $@"
	@$(CC) $(OBJS) $(LDLIBS) -o $@ $(LDFLAGS)
	@ln -sf yai $(LEGACY_TARGET)

$(BUILD_DIR)/%.o: %.c | dirs
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

# -----------------------------------------
# Docs (Doxygen) — CLI surface only
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
test: sdk $(UNIT_TEST_BIN) $(VECTORS_TEST_BIN)
	@echo "[TEST] $(UNIT_TEST_BIN)"
	@$(UNIT_TEST_BIN)
	@echo "[TEST] $(VECTORS_TEST_BIN)"
	@$(VECTORS_TEST_BIN)
	@echo "--- [YAI-CLI] Tests Complete ---"

$(UNIT_TEST_BIN): tests/unit/parse_test.c | dirs sdk
	@mkdir -p $(TEST_BIN_DIR)
	@$(CC) $(CFLAGS) $< $(LDLIBS) -o $@

$(VECTORS_TEST_BIN): tests/vectors/rpc_vectors_test.c | dirs sdk
	@mkdir -p $(TEST_BIN_DIR)
	@$(CC) $(CFLAGS) $< $(LDLIBS) -o $@

-include $(DEPS)