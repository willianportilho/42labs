/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_decoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:43:40 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 07:12:46 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

/* Inicializa a memória para ser possível liberá-la a qualquer momento*/
static void init_memory(t_huff *huff)
{
	huff->txt.decompressed_code = NULL;
	huff->txt.compressed_code = NULL;
	huff->mem_ab.cp_compressed_code = NULL;
	huff->txt.decoded_text = NULL;
	huff->txt.coded_text = NULL;
	huff->txt.text = NULL;
	huff->dic.dictionary = NULL;
	huff->list.root = NULL;
}

static void	get_shared_memory_data(t_huff *huff)
{
	huff->mem_b->number_of_texts = huff->mem_a->number_of_texts;
	huff->mem_b->n_bytes_compressed_code = huff->mem_a->size_compressed_code;
	huff->mem_b->n_bytes_decoded_txt = ft_strlen((char *)huff->txt.decoded_text);
	huff->mem_b->uncompress_time = 0;
}

void	share_memory_one(t_huff *huff)
{
	huff->mem_a = attach_memory_block(sizeof(t_memory_go *), 0, huff);
	huff->mem_ab.cp_compressed_code = attach_memory_block\
	((huff->mem_a->size_compressed_code + 1) * sizeof(unsigned char), 1, huff);
}

void	share_memory_two(t_huff *huff)
{
	huff->mem_b = attach_memory_block(sizeof(t_memory_back *), 2, huff);
	get_shared_memory_data(huff);
	huff->mem_ab.cp_decoded_code = attach_memory_block\
	((huff->mem_b->n_bytes_decoded_txt + 1) * sizeof(unsigned char), 3, huff);
	memcpy(huff->mem_ab.cp_decoded_code, huff->txt.decoded_text, \
	huff->mem_b->n_bytes_decoded_txt + 1);
	free_shared_memory_one(huff);
}

int	main(void)
{
	t_huff	huff;

	init_memory(&huff);
	share_memory_one(&huff);
	sorted_list(huff.mem_a->ascii_table, &huff);
	huffman_tree(&huff);
	dictionary(&huff);
	decompress_code(&huff);
	decoded_text(&huff);
	share_memory_two(&huff);
	free_memory(&huff);
	return (0);
}
