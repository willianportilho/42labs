# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 11:25:18 by wportilh          #+#    #+#              #
#    Updated: 2023/01/14 04:58:26 by wportilh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES_ENC	=	01_encoder.c			\
				03_get_file.c			\
				04_sorted_list.c		\
				05_huffman_tree.c		\
				06_dictionary.c			\
				07_coded_text.c			\
				08_compress_code.c		\
				09_decompress_code.c	\
				10_decoded_text.c		\
				11_create_files.c		\
				12_free_memory.c		\
				13_errors.c				\
				14_utils.c

SOURCES_DEC	=	02_decoder.c

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
				@${VAL} ./encoder src/encoder.c

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