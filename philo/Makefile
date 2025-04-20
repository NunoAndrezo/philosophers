# Executable Name
NAME = philo

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
CYAN = \033[0;36m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NOCOLOR = \033[0m

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -pthread -fsanitize=thread

# Dependency Generation Flags
# -MMD: Generates dependency files (.d) while compiling
# -MF: Specifies where to write the dependency file
# -MP: Adds phony targets for headers (prevents errors if headers are deleted)
# -MT: Sets the target name in the dependency file
DEPFLAGS = -MT $@ -MMD -MP -MF $(OBJ_DIR)/$*.d

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = libft
PRINTF_DIR = printf

# Source files
SRC_FILES =	src/checkers_and_changers.c src/cleaners_and_frees.c \
			src/initiate.c src/monitor_routine.c src/mutexes.c \
			src/routine.c src/start.c \
			src/time.c src/utils.c src/main.c \

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEPS = $(OBJ_FILES:.o=.d)

# Main targets
.PHONY: all clean fclean re libs

all: $(NAME)

# Create object directory
$(OBJ_DIR):
	@mkdir -p $@

# Compile objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(DEPFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@printf "$(CYAN)Compiled:$(NOCOLOR) %s\n" "$<"

# Libraries (silent mode)
$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR) --no-print-directory >/dev/null 2>&1

$(PRINTF_DIR)/libftprintf.a:
	@make -C $(PRINTF_DIR) --no-print-directory >/dev/null 2>&1

libs: $(LIBFT_DIR)/libft.a $(PRINTF_DIR)/libftprintf.a

# Final linking
$(NAME): libs $(OBJ_FILES)
	@if [ "$(OBJ_FILES)" != "" ] && [ "$(filter-out libs,$?)" != "" ]; then \
		$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT_DIR)/libft.a $(PRINTF_DIR)/libftprintf.a -o $@ && \
		printf "$(GREEN)✓ $(NAME) built successfully$(NOCOLOR)\n" || \
		printf "$(RED)✗ Failed to build $(NAME)$(NOCOLOR)\n"; \
	elif [ ! -f $(NAME) ]; then \
		$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT_DIR)/libft.a $(PRINTF_DIR)/libftprintf.a -o $@ && \
		printf "$(GREEN)✓ $(NAME) built successfully$(NOCOLOR)\n" || \
		printf "$(RED)✗ Failed to build $(NAME)$(NOCOLOR)\n"; \
	else \
		printf "$(BLUE)Nothing to be done$(NOCOLOR)\n"; \
	fi

# Clean rules with precise messaging
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR) >/dev/null 2>&1; \
		printf "$(BLUE)✓ Object files removed$(NOCOLOR)\n"; \
	else \
		printf "$(BLUE)✓ Object files were already removed$(NOCOLOR)\n"; \
	fi
	@make clean -C $(LIBFT_DIR) --no-print-directory >/dev/null 2>&1
	@make clean -C $(PRINTF_DIR) --no-print-directory >/dev/null 2>&1

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME) >/dev/null 2>&1; \
		rm_flag=1; \
	fi; \
	if [ -f "$(LIBFT_DIR)/libft.a" ]; then \
		make fclean -C $(LIBFT_DIR) --no-print-directory >/dev/null 2>&1; \
		rm_flag=1; \
	fi; \
	if [ -f "$(PRINTF_DIR)/libftprintf.a" ]; then \
		make fclean -C $(PRINTF_DIR) --no-print-directory >/dev/null 2>&1; \
		rm_flag=1; \
	fi; \
	if [ "$$rm_flag" = "1" ]; then \
		printf "$(BLUE)✓ All files cleaned$(NOCOLOR)\n"; \
	else \
		printf "$(BLUE)✓ Everything was already removed$(NOCOLOR)\n"; \
	fi

re: fclean all

-include $(DEPS)