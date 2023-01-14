/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:07:35 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/13 21:30:33 by wportilh         ###   ########.fr       */
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
	size = (ft_strlen(huff->txt.coded_text) / 8) + 1; // A cada 8 bits, um char de alocação. *1 a mais para cálculos quebrados 
	huff->txt.compressed_code = calloc((size + 1), sizeof(char));
	if (huff->txt.compressed_code == NULL)
		exit(EXIT_FAILURE);
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
			huff->txt.compressed_code[++k] = byte;
			byte = 0;
			j = 7;
		}
	}
	if (j != 7) // byte não está totalmente formado. ex: 1110 (será completado por 0's) 11100000 (1 byte)
		huff->txt.compressed_code[++k] = byte;
	huff->txt.compressed_code[++k] = '\0';
	//printf("\ncompresscode = %s\n", huff->txt.compressed_code);
}
