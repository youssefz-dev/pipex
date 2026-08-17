# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 12:23:38 by yzoullik          #+#    #+#              #
#    Updated: 2025/03/08 13:14:51 by yzoullik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
HEADER = pipex.h

SRC =	pipex.c\
		split.c\
		utils.c\
		utils1.c\
		pipex_utils.c

NAMEB = pipex_bonus
HEADERB = bonus/pipex_bonus.h

SRCB =	bonus/pipex_bonus.c\
		bonus/split_bonus.c\
		bonus/get_next_line_bonus.c\
		bonus/get_next_line_utils_bonus.c\
		bonus/utils_bonus.c\
		bonus/here_doc.c\
		bonus/utils2_bonus.c\
		bonus/pipex_utils_bonus.c
		
OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus : $(NAMEB)

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME)

$(NAMEB): $(OBJB)
	cc $(OBJB) -o $(NAMEB)

%.o: %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c $(HEADERB)
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME) $(NAMEB)

re: fclean all

.PHONY: clean