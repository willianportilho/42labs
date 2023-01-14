/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_compress_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:07:35 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 10:55:13 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

void	compress_code(t_huff *huff)
{
	int				i;
	int				j;
	int				k;
	int				size;
	unsigned char	mask;
	unsigned char	byte;

	i = -1;
	j = 7;
	k = -1;
	byte = 0;
	huff->txt.size_compress = 0;
	size = ft_strlen(huff->txt.coded_text) + 1; // A cada 8 bits, um char de alocação. *1 a mais para cálculos quebrados 
	huff->txt.compressed_code = calloc((size + 1), sizeof(char));
	if (huff->txt.compressed_code == NULL)
		exit_msg_error(PERROR_MSG, "", huff);
	while (huff->txt.coded_text[++i])
	{
		mask = 1;
		if (huff->txt.coded_text[i] == '1')
		{
			mask = mask << j;	// deslocamento para a posição j do byte
			byte = byte | mask;	// ativar o bit da posição j, de 0 para 1
		}
		j--;
		if (j < 0) // 8 bits foram preenchidos (1 byte). Temos um caractere
		{
			++k;
			huff->txt.size_compress++;
			huff->txt.compressed_code[k] = byte;
			byte = 0;
			j = 7;
		}
	}
	if (j != 7) // byte não está totalmente formado. ex: 1110 (será completado por 0's) 11100000 (1 byte)
		huff->txt.compressed_code[++k] = byte;
	huff->txt.compressed_code[++k] = '\0';
	j = -1;
	printf("\n\ncompress_code\n");
	while (++j < huff->txt.size_compress)
		printf("'%c'", huff->txt.compressed_code[j]);
	printf("\n\n");
}
