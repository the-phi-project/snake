##
SOURCE  = src
BUILD   = build
INCLUDE = include
BINARY  = minesweeper
##

##
SOURCES      = $(wildcard $(SOURCE)/*.c)
OBJECTS      = $(patsubst $(SOURCE)/%.c, $(BUILD)/%.o, $(SOURCES))
DEPENDENCIES = $(patsubst %.o, %.d, $(OBJECTS))
##

##
CC        = cc
WARNINGS  = -Wall -Wextra
LIBS      = -lncurses
STD       = -std=c17
DEP_FLAGS = -MP -MD
OPT       = -O2
DEFS      = -D VERSION="0.0.1b"
CFLAGS    = $(STD) $(OPT) $(WARNINGS) $(DEP_FLAGS) -I$(INCLUDE) $(DEFS)
##

##
RED    = \033[0;31m
ORANGE = \033[38;5;208m
YELLOW = \033[0;33m
GREEN  = \033[0;32m
BLUE   = \033[0;34m
PURPLE = \033[0;35m
BOLD   = \033[1m
RESET  = \033[0m
##

all: $(BINARY)

$(BINARY): $(OBJECTS)
	@echo "$(BOLD)$(BLUE)==== Linking ====$(RESET)"
	@echo "$(BLUE)Producing Binary$(RESET)"
	$(CC) $(OBJECTS) $(LIBS) -o $(BINARY)
	@echo "$(BOLD)$(GREEN)Binary Ready$(RESET)"

$(BUILD)/%.o: $(SOURCE)/%.c
	@echo "$(BOLD)$(YELLOW)==== Compiling ====$(RESET)"
	@echo "$(YELLOW)Building $<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BOLD)$(GREEN)OK$(RESET)"

clean:
	@echo "$(BOLD)$(ORANGE)==== Cleaning ====$(RESET)"
	@echo "$(ORANGE)Cycling Build Information$(RESET)"
	rm -rf $(BUILD)
	mkdir $(BUILD)
	@echo "$(ORANGE)Removing Helper Information$(RESET)"
	rm -rf $(BINARY).dSYM
	rm -f $(BINARY)
	@echo "$(BOLD)$(GREEN)Clean$(RESET)"

debug:
	@echo "$(BOLD)$(BLUE)==== Debug Build ====$(RESET)"
	@echo "$(BLUE)Compiling with Debug Symbols$(RESET)"
	@$(MAKE) CFLAGS="$(STD) -g -O0 $(WARNINGS) $(DEP_FLAGS) -I$(INCLUDE)" all
	@echo "$(BOLD)$(GREEN)Debug Binary Ready$(RESET)"

format:
	@echo "$(BOLD)$(PURPLE)==== Formatting ====$(RESET)"
	@echo "$(PURPLE)Running clang-format$(RESET)"
	find $(SOURCE) \( -name "*.c" -o -name "*.h" \) | xargs clang-format -i
	@echo "$(BOLD)$(GREEN)Done$(RESET)"

analyze:
	@echo "$(BOLD)$(BLUE)==== Analyzing ====$(RESET)"
	@echo "$(BLUE)Running clang-tidy$(RESET)"
	find $(SOURCE) -name "*.c" | xargs clang-tidy -- $(CFLAGS)
	@echo "$(BOLD)$(GREEN)Done$(RESET)"

.PHONY: all clean debug format analyze

-include $(DEPENDENCIES)
