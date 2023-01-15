/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:40:09 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 07:18:20 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUFFMAN_H
# define HUFFMAN_H

# include <sys/ipc.h>	// shared memory
# include <sys/shm.h>	// shared memory
# include <unistd.h>	// read
# include <stdio.h>		// dprintf | perror
# include <stdlib.h>	// exit | malloc
# include <fcntl.h>		// open
# include <string.h>	// strcat | strcpy | memcpy
# include <locale.h>	// utf-8
# include <sys/types.h>	// opendir
# include <dirent.h>	// opendir


# define BUFFER_SIZE 1024		// used in the read function
# define ASCII_SIZE 256
# define TRUE 1
# define FALSE 0
# define ONE_FILE 2
# define ETX 3					// means end of text (number 3 in the ascii table)
# define ETX_DELIMITER "\003"	// unsigned char version
# define PERROR_MSG 0			// use perror message
# define SET_MSG 1				// use a personalized message
# define FILE_NAME "Makefile"	// file reference to shared memory
# define ERROR -1				// makes reference to error (-1)
# define TYPE_INT 4				// indicates the type of variable (int)
# define TYPE_CHAR_P 8			// indicates the type of variable (char *)
# define ZIP 1
# define UNZIP 2

/*includes the ordened list and the Huffman tree*/
typedef struct  s_node
{
	int				frequency;
	unsigned char	character;
	struct  s_node	*right;
	struct  s_node	*left;
	struct  s_node	*next;
}					t_node;

typedef struct  s_list
{
	int				size_list;
	t_node			*root; // first node in the list
}					t_list;

/*Tabela de frequencia (caracteres)*/
typedef struct s_freq_tab
{
	unsigned int	ascii_table[256];
}					t_freq_tab;

typedef struct s_dictionary
{
	int				lenght_col;
	char			**dictionary;
}					t_dictionary;

typedef struct s_text
{
	long			size_compress;
	unsigned char	*text;
	unsigned char	*decoded_text;
	char			*coded_text;
	unsigned char	*compressed_code;
	char			*decompressed_code;
	int				tmpin;
	int				tmpout;
}					t_text;

typedef struct s_file
{
	char			*name_new_file;
}					t_file;

typedef struct s_memory_go
{
	int				number_of_texts;
	unsigned int	ascii_table[256];
	long			size_compressed_code;
}					t_memory_go;

typedef struct s_memory_back
{
	int				uncompress_time;
	int				number_of_texts;
	int				n_bytes_compressed_code;
	int				n_bytes_decoded_txt;
}					t_memory_back;

typedef struct s_memory_go_back
{
	unsigned char	*cp_compressed_code;
	unsigned char	*cp_decoded_code;
}					t_memory_go_back;

/*Estrutura principal*/
typedef struct s_huff
{
	int					flag;
	t_file				file;
	t_text				txt;
	t_dictionary		dic;
	t_freq_tab			freq_tab;
	t_list				list;
	t_memory_go			*mem_a;
	t_memory_back		*mem_b;
	t_memory_go_back	mem_ab;
}					t_huff;

/*03_shared_memory.c*/
void			*attach_memory_block(int size_block, int proj_id, t_huff *huff);
int				detach_memory_block(void *block);
int				destroy_memory_block(int proj_id);
/*get_file.c*/
void			get_file(int argc, char *argv[], t_huff *huff);

/*sorted_list.c*/
void			sort_list(t_node *node, t_huff *huff);
void			sorted_list(unsigned int *ascii_table, t_huff *huff);

/*huffman_tree.c*/
void			huffman_tree(t_huff *huff);

/*dictionary.c*/
void			dictionary(t_huff *huff);

/*code.c*/
void			coded_text(t_huff *huff);

/*decode_text.c*/
void			decoded_text(t_huff *huff);

/*compress_code.c*/
void			compress_code(t_huff *huff);

/*decompress_code.c*/
void			decompress_code(t_huff *huff);

/*create_files.c*/
void			create_files(t_huff *huff);

/*free_memory.c*/
void			free_memory(t_huff *huff);
void			free_shared_memory_one(t_huff *huff);
void			free_shared_memory_two(t_huff *huff);

/*error.c*/
void			exit_msg_error(int flag, char *message, t_huff *huff);
void			check_args_error(char *message);

/*Util functions (utils.c)*/
size_t			ft_strlen(char *s);
char			*ft_strjoin(char *s1, char *s2);
unsigned char	*ft_strjoin_free_s1(unsigned char **s1, unsigned char *s2);
int				check_if_is_a_directory(char *path);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

#endif