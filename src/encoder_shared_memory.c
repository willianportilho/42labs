/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder_shared_memory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:49:23 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 18:15:34 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

static void	copy_freq_table(t_huff *huff)
{
	int				i;

	i = -1;
	while (++i < ASCII_SIZE)
		huff->mem->ascii_table[i] = huff->freq_tab.ascii_table[i];
	//printf("ori: %ld\n", huff->txt.size_compress);
	//printf("new: %ld\n", huff->mem->size_compressed_code);
	/*i = -1;
	while (++i < ASCII_SIZE)
	{
		if (huff->mem->ascii_table[i] > 0)
			printf("mem: %d %d\n", i, huff->mem->ascii_table[i]); //print tests
	}*/
}

void	encode_shared_memory(t_huff *huff)
{
	huff->mem = attach_memory_block(sizeof(t_memory *), 0, huff);
	huff->mem->size_compressed_code = huff->txt.size_compress; // tamanho da alocação do texto comprimido
	copy_freq_table(huff);

	unsigned char *cp_compressed_code = attach_memory_block((huff->mem->size_compressed_code + 1) * sizeof(unsigned char), 1, huff);
	memcpy(cp_compressed_code, huff->txt.compressed_code, (huff->mem->size_compressed_code + 1) * sizeof(unsigned char));
	/*int j = -1;
	printf("\n\nencoder: compress_code\n");
	while (++j < huff->mem->size_compressed_code)
		printf("'%c'", cp_compressed_code[j]);
	printf("\n");*/
	detach_memory_block(huff->mem);
	detach_memory_block(cp_compressed_code);
	//destroy_memory_block(int proj_id); // destruir memória compartilhada
}
