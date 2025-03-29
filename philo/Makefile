# Executable Name
NAME			= philo

# Directories
PRINTF		= ./printf/libftprintf.a
LIBFT			= ./libft/libft.a
INC			= include
SRC_DIR		= src
OBJ_DIR		= obj

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall -Werror -Wextra -g -O3 -pthread -lpthread

rm					= rm -f

# Source and Object Files
SRC					=	src/checkers_and_changers.c src/initiate.c src/main.c \
						src/mutexes.c src/routine.c src/monitor_routine.c src/start.c \
						src/threads.c src/time.c src/utils.c \

OBJ					=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Build rules
start:
					@make all

$(PRINTF):
					@make -C ./printf
$(LIBFT):
					@make -C ./libft

all:				$(NAME)

$(NAME):			loading_bar $(OBJ) $(PRINTF) $(LIBFT)
					@$(CC) $(CFLAGS) $(OBJ) $(PRINTF) $(LIBFT) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

# Loading bar implementation
loading_bar:
					@if [ ! -f $(NAME) ] || [ "$(MAKECMDGOALS)" = "re" ]; then \
						echo "Building project..."; \
						for i in $$(seq 0 1 100); do \
							sleep 0.01; \
							printf "\rLoading: %3d%% [%-50s]" $$i $$(printf '#%.0s' $$(seq 1 $$((i / 2)))); \
						done; \
						printf "\n"; \
					else \
						echo "Nothing to be made!"; \
					fi

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./printf
					@make clean -C ./libft

fclean:				clean
					@$(RM) $(NAME)
					@make fclean -C ./printf
					@make fclean -C ./libft

re:					fclean all

# Phony targets represent actions not files
.PHONY:				start all clean fclean re loading_bar




#.PHONY specifies targets that are not actual files.
#This helps ensure that make runs these commands when specified
#even if files with these names exist.