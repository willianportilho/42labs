/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_decoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:43:40 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 04:41:23 by wportilh         ###   ########.fr       */
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

static void	get_info(t_huff *huff)
{
	huff->mem_b->n_bytes_compressed_code = huff->mem_a->size_compressed_code;
	huff->mem_b->n_bytes_decoded_txt = ft_strlen((char *)huff->txt.decoded_text);
	huff->mem_b->uncompress_time = 0;
}


int	main(void)
{
	t_huff	huff;

	init_memory(&huff);
	huff.mem_a = attach_memory_block(sizeof(t_memory_go *), 0, &huff);
	huff.mem_ab.cp_compressed_code = attach_memory_block((huff.mem_a->size_compressed_code + 1) * sizeof(unsigned char), 1, &huff);
	sorted_list(huff.mem_a->ascii_table, &huff);
	huffman_tree(&huff);
	dictionary(&huff);
	decompress_code(&huff);
	decoded_text(&huff);
	huff.mem_b = attach_memory_block(sizeof(t_memory_back *), 2, &huff);
	get_info(&huff);
	huff.mem_ab.cp_decoded_code = attach_memory_block((huff.mem_b->n_bytes_decoded_txt + 1) * sizeof(unsigned char), 300, &huff);
	memcpy(huff.mem_ab.cp_decoded_code, huff.txt.decoded_text, huff.mem_b->n_bytes_decoded_txt + 1);
	detach_memory_block(huff.mem_a);
	detach_memory_block(huff.mem_ab.cp_compressed_code);
	detach_memory_block(huff.mem_b);
	detach_memory_block(huff.mem_ab.cp_decoded_code);
	destroy_memory_block(0);
	destroy_memory_block(1);
	free_memory(&huff);
	return (0);
}
