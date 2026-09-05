# ---------------------------------------------------------------------------- #
# compile                                                                      #
# ---------------------------------------------------------------------------- #

ASM_CMP		:= nasm
C_CMP		:= cc
CFLAGS		:= -std=c23 -g3


# ---------------------------------------------------------------------------- #
# files                                                                        #
# ---------------------------------------------------------------------------- #

NAME		:= libasm
INC_DIR		:= include
SRC_DIR		:= source
OBJ_DIR		:= .object
LIBASM_A	:= $(NAME).a
TESTER_DIR	:= tester
TESTER		:= $(TESTER_DIR)/$(NAME)_tester

FILES	:= $(shell find $(SRC_DIR) -type f -wholename '*.asm')
OBJS	:= $(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.o, $(FILES))


# ---------------------------------------------------------------------------- #
# make                                                                         #
# ---------------------------------------------------------------------------- #

## Build libasm.a
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(LIBASM_A) $(OBJS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(OBJ_DIR)
	$(ASM_CMP) -f elf64 -g3 -F dwarf $< -o $@

## Call 'fclean' and 'all' targets
re:
	+$(MAKE) fclean
	+$(MAKE) all


# ---------------------------------------------------------------------------- #
# test                                                                         #
# ---------------------------------------------------------------------------- #

## Build the tester
test:
	+$(MAKE) all
	+$(MAKE) -C $(TESTER_DIR) all


# ---------------------------------------------------------------------------- #
# clean                                                                        #
# ---------------------------------------------------------------------------- #

## Delete the object folder
clean:
	rm -rf $(OBJ_DIR)

## Call 'clean' and delete the libasm.a file
fclean:
	+$(MAKE) clean
	+$(MAKE) -C $(TESTER_DIR) fclean
	rm -f $(LIBASM_A)



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


.PHONY: all re test clean fclean help