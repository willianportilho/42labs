/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompress_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:27:40 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/13 20:52:24 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

/* Will return 0 or a value greather than 0*/
unsigned int	check_bit_value(unsigned char byte, int i)
{
	unsigned char	mask;

	mask = 1 << i;
	return (byte & mask); // 10000000, next 01000000 next 00100000 ...
}

void	decompress_code(t_huff *huff)
{
	int				i;
	int				j;
	int				k;
	int				size;

	i = -1;
	k = -1;
	size = ft_strlen(huff->txt.coded_text); // A cada byte, 8 chars de alocação.
	huff->txt.decompressed_code = calloc((size + 1), sizeof(char));
	if (huff->txt.decompressed_code == NULL)
		exit(EXIT_FAILURE);
	while (huff->txt.compressed_code[++i])
	{
		j = 7;
		while (j >= 0)
		{
			if (check_bit_value(huff->txt.compressed_code[i], j) > 0)
				huff->txt.decompressed_code[++k] = '1';
			else
				huff->txt.decompressed_code[++k] = '0';
			j--;
		}
	}
	huff->txt.decompressed_code[++k] = '\0';
	printf("\ndecompresscode = %s\n", huff->txt.decompressed_code);
}
