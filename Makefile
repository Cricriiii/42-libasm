# ---------------------------------------------------------------------------- #
# files                                                                        #
# ---------------------------------------------------------------------------- #

NAME	:= libasm
INC_DIR	:= $(NAME)/include
SRC_DIR	:= $(NAME)/source
OBJ_DIR	:= $(NAME)/.object
ARCHIVE	:= $(NAME).a

FILES	:= $(shell find $(SRC_DIR) -type f -wholename '*.asm')
OBJS	:= $(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.o, $(FILES))


# ---------------------------------------------------------------------------- #
# make                                                                         #
# ---------------------------------------------------------------------------- #

## Build the archive
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(ARCHIVE) $(OBJS)

$(OBJS): $(FILES)
	@mkdir -p $(OBJ_DIR)
	nasm -f elf64 -g3 -F dwarf $< -o $@

## Call 'fclean' and 'all' targets
re:
	+$(MAKE) fclean
	+$(MAKE) all


# ---------------------------------------------------------------------------- #
# clean                                                                        #
# ---------------------------------------------------------------------------- #

## Delete the object folder
clean:
	rm -rf $(OBJ_DIR)

## Call 'clean' and delete the archive file'
fclean:
	+$(MAKE) clean
	rm -f $(ARCHIVE)


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


.PHONY: all re clean fclean