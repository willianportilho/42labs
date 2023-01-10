# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 11:25:18 by wportilh          #+#    #+#              #
#    Updated: 2023/01/10 11:50:11 by wportilh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES =		main.c

NAME =			huffman

CC =			cc
CFLAGS =		-g3 -Wall -Wextra -Werror
RM =			rm -f
RM_ALL =		rm -rf

VAL =			valgrind --leak-check=full --show-leak-kinds=all

INC =			inc/

SRC_PATH =		src/

OBJ_PATH =		obj/

SRCS =			src/

OBJS =			${addprefix ${OBJ_PATH}, ${SOURCES:.c=.o}}

CYAN =			\033[36m
RESET =			\033[0m

all:			${NAME}

${NAME}:		${OBJS}
				@echo "${CYAN}--------------------------"
				@echo " objs ok!     "
				@echo "--------------------------"
				@${CC} ${OBJS} -o ${NAME}
				@echo "--------------------------"
				@echo " program created!"
				@echo "--------------------------${RESET}"

${OBJ_PATH}%.o:	${SRC_PATH}%.c
				@mkdir -p obj
				@${CC} ${CFLAGS} -c $< -o $@

val:			${NAME}
				${VAL} ./huffman

clean:		
				@${RM_ALL} ${OBJ_PATH}
				@echo "${CYAN}--------------------------"
				@echo " clean completed!"
				@echo "--------------------------${RESET}"

fclean:			clean
				@${RM} ${NAME}
				@echo "${CYAN}--------------------------"
				@echo " fclean completed!"
				@echo "--------------------------${RESET}"

re:				fclean all
				@echo "${CYAN}--------------------------"
				@echo " re completed!"
				@echo "--------------------------${RESET}"

norm:
				norminette ${SRCS}

.PHONY:			all clean fclean re norm val