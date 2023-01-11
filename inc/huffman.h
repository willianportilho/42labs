/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:40:09 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/11 15:15:24 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUFFMAN_H
# define HUFFMAN_H

# include <sys/ipc.h>
# include <sys/shm.h>
# include <unistd.h>	// read
# include <stdio.h>		// dprintf
# include <stdlib.h>	// exit
# include <fcntl.h>		// open
//# include <locale.h>

# define BUFFER_SIZE 1024
# define SIZE_ASCII 256
# define TRUE 1
# define FALSE 0

/*Tabela de frequencia (caracteres)*/
typedef struct s_freq_tab
{
	unsigned int	ascii_table[256];
	unsigned char	*str_file;
}					t_freq_tab;

/*Estrutura principal*/
typedef struct s_huff
{
	t_freq_tab		freq_tab;
}					t_huff;


/*Util functions*/
size_t	ft_strlen(char *s);
unsigned char	*ft_strjoin_free_s1(unsigned char **s1, unsigned char *s2);

#endif