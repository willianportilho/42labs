/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_compress_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:07:35 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 12:24:58 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

static void	alloc_compress_code(t_huff *huff)
{
	int				size;

	size = ft_strlen(huff->txt.coded_text) + 1; // Every 8 bits, an allocation char. *1 more for broken calculations
	huff->txt.compressed_code = calloc((size + 1), sizeof(char));
	if (huff->txt.compressed_code == NULL)
		exit_msg_error(PERROR_MSG, "", huff);
}

void	compress_code(t_huff *huff)
{
	int				i;
	int				j;
	int				k;
	unsigned char	mask;
	unsigned char	byte;

	i = -1;
	j = 7;
	k = -1;
	huff->txt.size_compress = 0;
	alloc_compress_code(huff);
	while (huff->txt.coded_text[++i])
	{
		mask = 1;
		if (huff->txt.coded_text[i] == '1')
		{
			mask = mask << j; // offset to byte position j
			byte = byte | mask; // turn j position bit from 0 to 1
		}
		j--;
		if (j < 0) // 8 bits were placed (1 byte). we have a character
		{
			++k;
			huff->txt.size_compress++;
			huff->txt.compressed_code[k] = byte;
			byte = 0;
			j = 7;
		}
	}
	if (j != 7) // byte is not fully formed. ex: 1110 (will be completed by 0's) 11100000 (1 byte)
	{
		huff->txt.size_compress++;
		huff->txt.compressed_code[++k] = byte;
	}
	huff->txt.compressed_code[++k] = '\0';
}
