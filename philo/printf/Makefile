NAME	= libftprintf.a

SRCS 	=		ft_print_char.c \
				ft_putnbr.c \
				ft_putnbr_hexa.c \
				ft_print_str.c \
				ft_print_format.c \
				ft_print_ptr_adress.c \
				ft_putnbr_unsigned.c \
				ft_printf.c

OBJS			= $(SRCS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

all:			$(NAME)


clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
