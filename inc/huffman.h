/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:40:09 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/10 23:41:00 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUFFMAN_H
# define HUFFMAN_H

# define ERROR -1

# include <sys/ipc.h>
# include <sys/shm.h>
# include <stdio.h>
# include <stdlib.h> // exit

/*
	Estrutura principal
*/
typedef struct s_huff
{
	int		ascii_table[256];
}			t_huff;

#endif