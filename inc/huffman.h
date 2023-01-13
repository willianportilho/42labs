/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:40:09 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/12 23:51:13 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUFFMAN_H
# define HUFFMAN_H

# include <sys/ipc.h>	// shared memory
# include <sys/shm.h>	// shared memory
# include <unistd.h>	// read
# include <stdio.h>		// dprintf
# include <stdlib.h>	// exit - malloc
# include <fcntl.h>		// open
# include <string.h>	// strcat strcpy
//# include <locale.h>

# define BUFFER_SIZE 1024 // used in the read function
# define ASCII_SIZE 256
# define TRUE 1
# define FALSE 0

/*includes the ordened list and the Huffman tree*/
typedef struct  s_node
{
	int				frenquence;
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
	int		lenght_col;
	char	**dictionary;
}					t_dictionary;

typedef struct s_text
{
	unsigned char	*text;
	unsigned char	*decoded_text;
	char			*coded_text;
}					t_text;

/*Estrutura principal*/
typedef struct s_huff
{
	t_text			txt;
	t_dictionary	dic;
	t_freq_tab		freq_tab;
	t_list			list;
}					t_huff;

/*generate_sorted_list.c*/
void			sort_list(t_node *node, t_huff *huff);
void			generate_sorted_list(t_huff *huff);

/*generate_huffman_tree.c*/
void			generate_huffman_tree(t_huff *huff);

/*generate_dictionary.c*/
void    		generate_dictionary(t_huff *huff);

/*code.c*/
void			generate_coded_text(t_huff *huff);

/*decode_text.c*/
void			generate_decoded_text(t_huff *huff);

/*Util functions (utils.c)*/
size_t			ft_strlen(char *s);
unsigned char	*ft_strjoin_free_s1(unsigned char **s1, unsigned char *s2);

#endif