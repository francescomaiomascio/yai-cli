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
# Prefer SDK-pinned law, fallback to workspace-level deps/yai-law.
LAW_DIR := $(SDK_DIR)/deps/yai-law
ifeq ($(wildcard $(LAW_DIR)/contracts/protocol/include/protocol.h),)
LAW_DIR := $(ROOT_DIR)/deps/yai-law
endif
LAW_INC_PROTOCOL := $(LAW_DIR)/contracts/protocol/include
LAW_INC_VAULT    := $(LAW_DIR)/contracts/vault/include
LAW_INC_RUNTIME  := $(LAW_DIR)/contracts/protocol/runtime/include
# ---- Flags ----
CFLAGS ?= -Wall -Wextra -O2 -std=c11 -MMD -MP
CFLAGS += -I$(ROOT_DIR)/include
CFLAGS += -I$(SDK_INC)
CFLAGS += -I$(SDK_DIR)/third_party/cjson
CFLAGS += -I$(LAW_INC_PROTOCOL) -I$(LAW_INC_VAULT) -I$(LAW_INC_RUNTIME)
LDFLAGS ?=
LDLIBS  ?= $(SDK_LIB)
# ---- Sources (CLI only) ----
SRCS := \
  src/main.c \
  src/app/app.c \
  src/app/errors.c \
  src/help/help.c \
  src/parse/parse.c \
  src/term/color.c \
  src/render/display_map.c \
  src/render/style_map.c \
  src/app/control_call.c \
  src/app/lifecycle.c \
  src/render/render.c \
  src/watch/watch.c \
  src/watch/watch_model.c \
  src/watch/watch_ui.c \
  src/term/keys.c \
  src/term/screen.c \
  src/term/term.c \
  src/term/pager.c \
  src/util/fmt.c
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
test: sdk $(TARGET) $(UNIT_TEST_BIN) $(VECTORS_TEST_BIN)
	@echo "[TEST] $(UNIT_TEST_BIN)"
	@$(UNIT_TEST_BIN)
	@echo "[TEST] $(VECTORS_TEST_BIN)"
	@$(VECTORS_TEST_BIN)
	@echo "[TEST] tests/integration/output_contract_v1_guardrail.sh"
	@tests/integration/output_contract_v1_guardrail.sh
	@echo "[TEST] tests/integration/help_guardrail.sh"
	@tests/integration/help_guardrail.sh
	@echo "[TEST] tests/integration/porcelain_help_guardrail.sh"
	@tests/integration/porcelain_help_guardrail.sh
	@echo "--- [YAI-CLI] Tests Complete ---"
$(UNIT_TEST_BIN): tests/unit/parse_test.c | dirs sdk
	@mkdir -p $(TEST_BIN_DIR)
	@$(CC) $(CFLAGS) $< src/parse/parse.c $(LDLIBS) -o $@
$(VECTORS_TEST_BIN): tests/vectors/rpc_vectors_test.c | dirs sdk
	@mkdir -p $(TEST_BIN_DIR)
	@$(CC) $(CFLAGS) $< $(LDLIBS) -o $@
-include $(DEPS)
