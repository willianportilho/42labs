/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_decoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:43:40 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 18:10:30 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

/* Inicializa a memória para ser possível liberá-la a qualquer momento*/
static void init_memory(t_huff *huff)
{
	huff->txt.decompressed_code = NULL;
	huff->txt.compressed_code = NULL;
	huff->txt.decoded_text = NULL;
	huff->txt.coded_text = NULL;
	huff->txt.text = NULL;
	huff->dic.dictionary = NULL;
	huff->list.root = NULL;
}

int	main(void)
{
	//int		i;
	t_huff	huff;

	init_memory(&huff);
	huff.mem = attach_memory_block(sizeof(t_memory *), 0, &huff);
	/*printf("new: %ld\n", huff.mem->size_compressed_code);
	i = -1;
	while (++i < ASCII_SIZE)
	{
		if (huff.mem->ascii_table[i] > 0)
			printf("mem: %d %d\n", i, huff.mem->ascii_table[i]); //print tests
	}*/
	unsigned char *cp_compressed_code = attach_memory_block((huff.mem->size_compressed_code + 1) * sizeof(unsigned char), 1, &huff);
	int	j = -1;
	printf("\n\ndecoder: compress_code\n");
	while (++j < huff.mem->size_compressed_code)
		printf("'%c'", cp_compressed_code[j]);
	printf("\n");
	detach_memory_block(huff.mem);
	detach_memory_block(cp_compressed_code);
	//free_memory(&huff);
	return (0);
}
