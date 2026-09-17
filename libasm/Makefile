# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/13 16:42:36 by fox               #+#    #+#              #
#    Updated: 2026/09/17 12:39:26 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ---------------------------------------------------------------------------- #
# compile                                                                      #
# ---------------------------------------------------------------------------- #

ASM_CMP			:= nasm
C_CMP			:= cc
CFLAGS			:= -std=c23 -g3


# ---------------------------------------------------------------------------- #
# files                                                                        #
# ---------------------------------------------------------------------------- #

# Librairies
NAME			:= libasm
SRC_DIR			:= source
COM_DIR			:= common
OBJ_DIR			:= .object
OBJ_COM_DIR		:= $(OBJ_DIR)/common
ARCHIVE_A		:= $(NAME).a
BONUS_STAMP		:= $(OBJ_DIR)/.bonus

# Files
FILES			:= $(shell find $(SRC_DIR) -type f -name '*.asm')
FILES_MANDATORY	:= $(filter-out %_bonus.asm,$(FILES))
FILES_BONUS		:= $(filter %_bonus.asm,$(FILES))

OBJS_MANDATORY	:= $(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/%.o,$(FILES_MANDATORY))
OBJS_BONUS		:= $(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/%.o,$(FILES_BONUS))
OBJS			:= $(OBJS_MANDATORY) $(OBJS_BONUS)


# ---------------------------------------------------------------------------- #
# build                                                                        #
# ---------------------------------------------------------------------------- #

## Build libasm.a
all: $(ARCHIVE_A)

$(ARCHIVE_A): $(OBJS_MANDATORY)
	ar rcs $@ $^

## Build libasm.a with bonus functions
bonus: $(BONUS_STAMP)

$(BONUS_STAMP): $(OBJS) $(ARCHIVE_A)
	ar rcs $(ARCHIVE_A) $(OBJS)
	touch $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_COM_DIR)
	$(ASM_CMP) -f elf64 -g3 -F dwarf $< -o $@

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

## Call 'clean' and delete the libasm.a file
fclean:
	+$(MAKE) clean
	rm -f $(ARCHIVE_A)


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


.PHONY: all re test clean fclean help bonus