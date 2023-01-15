/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:40:09 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 12:17:14 by wportilh         ###   ########.fr       */
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
#include <sys/time.h>	// gettimeofday

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
# define ARG_ERROR "needed more than two arguments"
# define ARG_ERROR_2 "-unzip flag must have no arguments"
# define ARG_ERROR_3 "invalid argument"

/*includes the ordened list and the Huffman tree*/
typedef struct s_node
{
	int				frequency;
	unsigned char	character;
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*next;
}					t_node;

typedef struct s_list
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

/*variables that are used by texts, code or compressed texts*/
typedef struct s_text
{
	long			initial_time;
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
	int				uncompress_inicial_time;
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
	int					flag; // defines which flag is the user's choice (-zip or -unzip)
	t_file				file;
	t_text				txt;
	t_dictionary		dic;
	t_freq_tab			freq_tab;
	t_list				list;
	t_memory_go			*mem_a; // sending info from encoder to decoder 
	t_memory_back		*mem_b; // sending info from decoder to  encoder
	t_memory_go_back	mem_ab; // sending info by both
}					t_huff;

/**
 * @brief this function attach a block of memory between
 * twice independent programms, generating a pointer to the shared block
 * 
 * 03_memory.c
 * 
 * @param size_block size of memory
 * @param proj_id instance to connect in some file (0, 1, 2, 3 ...)
 * @param huff main struct with all informations
 */
void			*attach_memory_block(int size_block, int proj_id, t_huff *huff);

/**
 * @brief informs that this block has already been used, but not frezzes
 * 
 * 03_memory.c
 * 
 * @param block the block that will be detach
 */
int				detach_memory_block(void *block);

/**
 * @brief destroy the block
 * 
 * 03_memory.c
 * 
 * @param proj_id the instance that will be destryed
 */
int				destroy_memory_block(int proj_id);

/**
 * @brief gets a multiple files and put them in a string. When the number
 * of files are greater than 1, adds a delimiter ETX(3 - END OF TEXT) when
 * finds the end of file. All files are storage in the same string, but
 * with this delimiter. At the end of the program, this delimiter will help
 * us to knwow, how create uncompress files separately
 * 
 * 04_get_file.c
 * 
 * @param argc the number of arguments
 * @param argv the arguments
 * @param huff main struct with all informations
 */
void			get_file(int argc, char *argv[], t_huff *huff);

/**
 * @brief sort a linked list, inserting a new node in orden of
 * frequency. Is useful to construct a huffman tree
 * 
 * 05_sorted_list.c
 * 
 * @param node a struct with necessary informations to contruct
 * a huffman tree.
 * @param huff main struct with all informations
 * @param ascii_table table that has the characters frequency information
 */
void			sort_list(t_node *node, t_huff *huff);
void			sorted_list(unsigned int *ascii_table, t_huff *huff);

/**
 * @brief part of the huffman algorithm. has a next and a right node
 * in each parent node when are mount and storage a charactere in each leaf
 * and his frequecy. Is useful to create the dictionary
 * 
 * 06_huffman_tree.c
 * 
 * @param huff main struct with all informations
 */
void			huffman_tree(t_huff *huff);

/**
 * @brief part of the huffman algorithm. defines how a character will be
 * writed in code. storages the code of all the characters
 * 
 * 07_dictionary.c
 * 
 * @param huff main struct with all informations
 */
void			dictionary(t_huff *huff);

/**
 * @brief read the original text file and rewrite each character with
 * his new code represented by dictionary
 * 
 * 08_code.c
 * 
 * @param huff main struct with all informations
 */
void			coded_text(t_huff *huff);

/**
 * @brief read the coded text file and rewrite each number with
 * his letter represented by tree
 * 
 * 11_decode_text.c
 * 
 * @param huff main struct with all informations
 */
void			decoded_text(t_huff *huff);

/**
 * @brief read the coded text file and puts it, every 8 numbers,
 * in a byte (8 bit). (binary operations)
 * 
 * 09_compress_code.c
 * 
 * @param huff main struct with all informations
 */
void			compress_code(t_huff *huff);

/**
 * @brief read the compress text file and turns each byte index
 * into a number (1 or 0) again
 * 
 * 10_decompress_code.c
 * 
 * @param huff main struct with all informations
 */
void			decompress_code(t_huff *huff);


/**
 * @brief creates multiple files (one for each file given as an argument),
 * one compress with all texts, and one decoded with all texto too
 * 
 * 11_create_files.c
 * 
 * @param huff main struct with all informations
 */
void			create_files(t_huff *huff);

/**
 * @brief freezes all memory
 * 
 * 13_free_memory.c
 * 
 * @param huff main struct with all informations
 */
void			free_memory(t_huff *huff);
void			free_shared_memory_one(t_huff *huff);
void			free_shared_memory_two(t_huff *huff);

/**
 * @brief default message errors
 * 
 * 14_error.c
 * 
 * @param huff main struct with all informations
 */
void			exit_msg_error(int flag, char *message, t_huff *huff);
void			check_args_error(char *message);

/*Util functions (utils.c)*/
size_t			ft_strlen(char *s);
char			*ft_strjoin(char *s1, char *s2);
unsigned char	*ft_str_unsigned_join(unsigned char *s1, unsigned char *s2);
unsigned char	*ft_strjoin_free_s1(unsigned char **s1, unsigned char *s2);
int				check_if_is_a_directory(char *path);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_itoa(int n);
long			current_time(void);

#endif