# ---------------------------------------------------------------------------- #
# compile                                                                      #
# ---------------------------------------------------------------------------- #

CXX			:= c++
CXXFLAGS	:= -std=c++23 -Wall -Wextra -Werror -g3 -O0


# ---------------------------------------------------------------------------- #
# files                                                                        #
# ---------------------------------------------------------------------------- #

# Librairies
LIBCPP		:= libcpp
LIBCPP_INC	:= ../$(LIBCPP)/include
LIBCPP_A	:= ../$(LIBCPP)/$(LIBCPP).a

LIBASM		:= libasm
LIBASM_A	:= ../$(LIBASM)/$(LIBASM).a

LIBS		:= $(LIBCPP_A) $(LIBASM_A) 

# Files
RUNNER_NAME	:= $(LIBASM)_tester

INC_DIR			:= include
INC_TESTED		:= $(INC_DIR)/tested
SRC_DIR			:= source
OBJ_DIR			:= .object
OBJ_TESTED_DIR	:= $(OBJ_DIR)/tested
BONUS_STAMP		:= $(OBJ_DIR)/.bonus

FILES			:= $(shell find $(SRC_DIR) -type f -name '*.cpp')
FILES_MANDATORY	:= $(filter-out %_bonus.cpp,$(FILES))
FILES_BONUS		:= $(filter %_bonus.cpp,$(FILES))

OBJS_MANDATORY	:= $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(FILES_MANDATORY))
OBJS_BONUS		:= $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(FILES_BONUS))
OBJS			:= $(OBJS_MANDATORY) $(OBJS_BONUS)


# ---------------------------------------------------------------------------- #
# build                                                                        #
# ---------------------------------------------------------------------------- #

## Build the tester
all: $(RUNNER_NAME)

$(RUNNER_NAME): $(OBJS_MANDATORY) $(LIBS)
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -I $(LIBCPP_INC) -I $(INC_TESTED) $^ -o $@

## Build the tester with bonus tests
bonus: $(BONUS_STAMP)

$(BONUS_STAMP): $(OBJS) $(LIBS) $(RUNNER_NAME)
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -I $(LIBCPP_INC) -I $(INC_TESTED) $(OBJS) $(LIBS) -o $(RUNNER_NAME)
	@touch $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_TESTED_DIR)
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -I $(LIBCPP_INC) -I $(INC_TESTED) -c $< -o $@

## Call 'fclean' and 'all' targets
re:
	+$(MAKE) fclean
	+$(MAKE) all


# ---------------------------------------------------------------------------- #
# clean                                                                        #
# ---------------------------------------------------------------------------- #

## Delete the object folder
clean:
	@rm -rf $(OBJ_DIR)

## Call 'clean' and delete all executables and archive files
fclean:
	+$(MAKE) clean
	@rm -f $(RUNNER_NAME)


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

.PHONY: all bonus re test clean c fclean fc

.SECONDARY: $(RUNNER_OBJ) $(TEST_OBJ)