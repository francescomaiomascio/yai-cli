# ==========================================
# YAI CLI Build System (Modular Fix #2)
# ==========================================

CC ?= cc
ROOT_DIR := $(abspath .)

OUT_BUILD_DIR ?= $(ROOT_DIR)/build
OUT_BIN_DIR   ?= $(ROOT_DIR)/dist/bin

BUILD_DIR := $(OUT_BUILD_DIR)
BIN_DIR   := $(OUT_BIN_DIR)

TARGET := $(BIN_DIR)/yai
LEGACY_TARGET := $(BIN_DIR)/yai-cli

# ---- DIPENDENZE (Assetto Piatto) ----
SDK_DIR   := $(ROOT_DIR)/deps/yai-sdk
# NOTA: Ora puntiamo al Law fratello nella CLI, non più dentro l'SDK!
LAW_DIR   := $(ROOT_DIR)/deps/yai-law

# Librerie generate dall'SDK (Fix #2)
# Linkiamo ENTRAMBE per avere sia il protocollo che la logica SDK
SDK_LIB   := $(SDK_DIR)/dist/lib/libyai_sdk.a
PROTO_LIB := $(SDK_DIR)/dist/lib/libruntime_protocol.a

# ---- Path di Include ----
SDK_INC   := $(SDK_DIR)/include
LAW_INC_PROTOCOL := $(LAW_DIR)/contracts/protocol/include
LAW_INC_VAULT    := $(LAW_DIR)/contracts/vault/include
LAW_INC_RUNTIME  := $(LAW_DIR)/contracts/protocol/runtime/include

# ---- Flags ----
CFLAGS ?= -Wall -Wextra -O2 -std=c11 -MMD -MP
CFLAGS += -I$(ROOT_DIR)/include -I$(SDK_INC)
CFLAGS += -I$(LAW_INC_PROTOCOL) -I$(LAW_INC_VAULT) -I$(LAW_INC_RUNTIME)

# Importante: Linkiamo le librerie statiche
# L'ordine conta: prima la CLI, poi l'SDK, poi il Protocollo (base)
LDLIBS  := $(SDK_LIB) $(PROTO_LIB)

# ---- Sorgenti (Solo logica CLI) ----
SRCS := \
  src/main.c \
  src/porcelain/porcelain.c \
  src/porcelain/porcelain_errors.c \
  src/porcelain/porcelain_help.c \
  src/porcelain/porcelain_output.c \
  src/porcelain/porcelain_parse.c \
  src/util/fmt.c

OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean dirs sdk test

all: dirs sdk $(TARGET)
	@echo "--- [YAI-CLI] Build Complete (Architecture Clean) ---"

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Chiamiamo il target 'libs' dell'SDK che abbiamo creato prima
sdk:
	@echo "[SDK] Building Modular Libraries..."
	@$(MAKE) -C $(SDK_DIR) libs

$(TARGET): $(OBJS)
	@echo "[LINK] CLI: $@"
	@$(CC) $(OBJS) $(LDLIBS) -o $@ $(LDFLAGS)
	@ln -sf yai $(LEGACY_TARGET)

$(BUILD_DIR)/%.o: %.c | dirs
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@# Non puliamo l'SDK qui per velocità, ma puoi aggiungere sdk-clean se vuoi

-include $(DEPS)