# ---------------------------------------------------------------------------- #
# compile                                                                      #
# ---------------------------------------------------------------------------- #

CC			:= cc
CFLAGS		:= -std=c23 -Wall -Wextra -Werror -g3


# ---------------------------------------------------------------------------- #
# files                                                                        #
# ---------------------------------------------------------------------------- #

LIBASM_A  := libasm.a

INC_DIR	:= include

RUNNER_SRC_DIR	:= source
RUNNER_OBJ_DIR	:= .object
RUNNER_EXE_DIR	:= executable

TEST_SRC_DIR	:= $(RUNNER_SRC_DIR)/test
TEST_OBJ_DIR	:= $(RUNNER_OBJ_DIR)/test
TEST_EXE_DIR	:= $(RUNNER_EXE_DIR)

RUNNER_NAME		:= libasm_tester
RUNNER_SRC		:= $(RUNNER_SRC_DIR)/$(RUNNER_NAME).c
RUNNER_OBJ		:= $(RUNNER_OBJ_DIR)/$(RUNNER_NAME).o
RUNNER_EXE		:= $(RUNNER_NAME)

TEST_SRC		:= $(shell find $(TEST_SRC_DIR) -type f -wholename '*.c')
TEST_OBJ		:= $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC))
TEST_EXE		:= $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_EXE_DIR)/%, $(TEST_SRC))


# ---------------------------------------------------------------------------- #
# make                                                                         #
# ---------------------------------------------------------------------------- #

## Build the tester
all: $(RUNNER_EXE) $(TEST_EXE)

$(RUNNER_EXE): $(RUNNER_SRC)
	@cp ../$(LIBASM_A) .
	@mkdir -p $(RUNNER_OBJ_DIR)
	@mkdir -p $(RUNNER_EXE_DIR)
	$(CC) $(CFLAGS) -c $(RUNNER_SRC) -o $(RUNNER_OBJ)
	$(CC) $(CFLAGS) $(RUNNER_OBJ) -o $(RUNNER_EXE)

$(TEST_EXE_DIR)/%: $(TEST_OBJ_DIR)/%.o $(LIBASM_A)
	$(CC) $(CFLAGS) -I $(INC_DIR) $< $(LIBASM_A) -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	@cp ../$(LIBASM_A) .
	@mkdir -p $(TEST_OBJ_DIR)
	@mkdir -p $(TEST_EXE_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

## Call 'fclean' and 'all' targets
re:
	+$(MAKE) fclean
	+$(MAKE) all


# ---------------------------------------------------------------------------- #
# clean                                                                        #
# ---------------------------------------------------------------------------- #

## Delete the object folder
clean:
	@rm -rf $(RUNNER_OBJ_DIR)


## Call 'clean' and delete all executables and archive files
fclean:
	+$(MAKE) clean
	@rm -rf $(RUNNER_EXE_DIR)
	@rm -f $(LIBASM_A)
	@rm -f $(RUNNER_EXE)


# ---------------------------------------------------------------------------- #
# misc                                                                         #
# ---------------------------------------------------------------------------- #

# Provided by https://gitlab.com/depressiveRobot/make-help/blob/master/help.mk
## Show this help
help:
	@printf "\nAvailable targets:\n"
	@awk '/^[a-zA-Z\-_0-9]+:/ { \
		helpMessage = match(lastLine, /^## (.*)/); \
		if (helpMessage) { \
			helpCommand = substr($$1, 0, index($$1, ":")-1); \
			helpMessage = substr(lastLine, RSTART + 3, RLENGTH); \
			printf "  %-20s %s\n", helpCommand, helpMessage; \
		} \
	} \
	{ lastLine = $$0 }' $(MAKEFILE_LIST)
	@echo

.PHONY: all re test clean c fclean fc

.SECONDARY: $(RUNNER_OBJ) $(TEST_OBJ)