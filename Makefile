# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 11:25:18 by wportilh          #+#    #+#              #
#    Updated: 2023/01/10 23:41:26 by wportilh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES_ENC	=	encoder.c
SOURCES_DEC	=	decoder.c

NAME_ENC =		encoder
NAME_DEC =		decoder

CC =			cc
CFLAGS =		-g3 -Wall -Wextra -Werror
RM =			rm -f
RM_ALL =		rm -rf

VAL =			valgrind --leak-check=full --show-leak-kinds=all

INC =			inc/

SRC_PATH =		src/

OBJ_PATH =		obj/

SRCS =			src/

OBJS_ENC =			${addprefix ${OBJ_PATH}, ${SOURCES_ENC:.c=.o}}
OBJS_DEC =			${addprefix ${OBJ_PATH}, ${SOURCES_DEC:.c=.o}}

CYAN =			\033[36m
RESET =			\033[0m

all:			${NAME_ENC} ${NAME_DEC}

${NAME_ENC}:	${OBJS_ENC}
				@echo "${CYAN}--------------------------"
				@echo " objs encoder ok!     "
				@echo "--------------------------"
				@${CC} ${OBJS_ENC} -o ${NAME_ENC}
				@echo "--------------------------"
				@echo " encoder program created!"
				@echo "--------------------------${RESET}"

${NAME_DEC}:	${OBJS_DEC}
				@echo "${CYAN}--------------------------"
				@echo " objs decoder ok!     "
				@echo "--------------------------"
				@${CC} ${OBJS_DEC} -o ${NAME_DEC}
				@echo "--------------------------"
				@echo " decoder program created!"
				@echo "--------------------------${RESET}"

${OBJ_PATH}%.o:	${SRC_PATH}%.c
				@mkdir -p obj
				@${CC} ${CFLAGS} -c $< -o $@

run:			${NAME_ENC} ${NAME_DEC}
				@./encoder
				@./decoder

clean:		
				@${RM_ALL} ${OBJ_PATH}
				@echo "${CYAN}--------------------------"
				@echo " clean completed!"
				@echo "--------------------------${RESET}"

fclean:			clean
				@${RM} ${NAME_ENC} ${NAME_DEC} 
				@echo "${CYAN}--------------------------"
				@echo " fclean completed!"
				@echo "--------------------------${RESET}"

re:				fclean all
				@echo "${CYAN}--------------------------"
				@echo " re completed!"
				@echo "--------------------------${RESET}"

norm:
				norminette ${SRCS} ${INC}

.PHONY:			all clean fclean re norm run