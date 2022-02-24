# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/12 16:40:01 by rgelin            #+#    #+#              #
#    Updated: 2021/10/14 20:08:01 by rgelin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_printf.c \
		conversion_s.c \
		conversion_d.c \
		conversion_x.c

OBJS        =       $(SRCS:%.c=%.o)

CC          =       gcc

CFLAGS      =       -Wall -Wextra -Werror

REMOVE		=		rm -f

NAME        =       libftprintf.a

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
			
all:		$(NAME)

$(NAME):	$(OBJS)
			@ar rc  $(NAME) $(OBJS)

clean:
			@$(REMOVE) $(OBJS)

fclean:		clean
			@$(REMOVE) $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re .c.o