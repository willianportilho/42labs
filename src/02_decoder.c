/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_decoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:43:40 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 16:58:01 by wportilh         ###   ########.fr       */
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
	t_huff	huff;

	init_memory(&huff);
	huff.mem = attach_memory_block(sizeof(t_memory *), 1, &huff);
	printf("decoder: %d\n", huff.mem->ascii_table[0]);
	printf("decoder: %d\n", huff.mem->ascii_table[1]);
	printf("decoder: %d\n", huff.mem->ascii_table[2]);
	printf("decoder: %d\n", huff.mem->ascii_table[3]);
	detach_memory_block(huff.mem);
	//free_memory(&huff);
	return (0);
}
