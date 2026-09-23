# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fox <fox@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/13 17:50:35 by fox               #+#    #+#              #
#    Updated: 2026/09/23 22:20:41 by fox              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ---------------------------------------------------------------------------- #
# files                                                                        #
# ---------------------------------------------------------------------------- #

LIBASM_DIR		:= libasm
LIBCPP_DIR		:= libcpp
TESTER_CPP_DIR	:= tester_cpp
TESTER_RUNNER	:= $(TESTER_CPP_DIR)/libasm_tester


# ---------------------------------------------------------------------------- #
# build                                                                        #
# ---------------------------------------------------------------------------- #

## Build libasm 'mandatory' archive and tester
all:
	+$(MAKE) -C $(LIBASM_DIR) all -j $(nproc)
	+$(MAKE) -C $(LIBCPP_DIR) all -j $(nproc)
	+$(MAKE) -C $(TESTER_CPP_DIR) all -j $(nproc)

## Build libasm 'bonus' archive and tester
bonus:
	+$(MAKE) -C $(LIBASM_DIR) bonus -j $(nproc)
	+$(MAKE) -C $(LIBCPP_DIR) all -j $(nproc)
	+$(MAKE) -C $(TESTER_CPP_DIR) bonus -j $(nproc)

## Build the Docker version with bonuses
docker:
	+$(MAKE) fclean
	docker build -t $(TESTER_CPP_DIR):1.0 .

## Clear every directory and rebuild everything
re:
	+$(MAKE) fclean
	+$(MAKE) bonus


# ---------------------------------------------------------------------------- #
# build                                                                        #
# ---------------------------------------------------------------------------- #

## Launch the test executable
test:
	@./$(TESTER_RUNNER) || true


## Launch the Dockerized test executable
test_docker:
	docker run -it --rm localhost/$(TESTER_CPP_DIR):1.0
	
# ---------------------------------------------------------------------------- #
# clean                                                                        #
# ---------------------------------------------------------------------------- #

## Call all the 'clean' targets
clean:
	+$(MAKE) -C $(LIBASM_DIR) clean
	+$(MAKE) -C $(LIBCPP_DIR) clean
	+$(MAKE) -C $(TESTER_CPP_DIR) clean

## Call all the 'fclean' targets
fclean:
	+$(MAKE) -C $(LIBASM_DIR) fclean
	+$(MAKE) -C $(LIBCPP_DIR) fclean
	+$(MAKE) -C $(TESTER_CPP_DIR) fclean


# ---------------------------------------------------------------------------- #
# misc                                                                         #
# ---------------------------------------------------------------------------- #

## Format files
format:
	@find . -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i

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


.PHONY: all bonus re docker test test_docker clean fclean format help