/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_encoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:21 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 21:10:27 by wportilh         ###   ########.fr       */
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

/*
	Inicializa uma tabela de tamanho 255, que representa cada símbolo da tabela
	ASCII. Cada index é inicializado com o valor 0. Cada vez que uma letra
	correspondente a um index for encontrada, o index correspondente será
	incrementado, gerando assim os dados de frequencia de cada símbolo. 
*/
static void	frequence_table(t_huff *huff)
{
	int				i;

	i = -1;
	while (++i < ASCII_SIZE)
		huff->freq_tab.ascii_table[i] = 0;
	i = -1;
	while (huff->txt.text[++i])
		huff->freq_tab.ascii_table[huff->txt.text[i]]++;
	/*i = -1;
	while (++i < ASCII_SIZE)
	{
		if (huff->freq_tab.ascii_table[i] > 0)
			printf("ori: %d %d\n", i, huff->freq_tab.ascii_table[i]); //print tests
	}*/
}

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

static void	encode_shared_memory(t_huff *huff)
{
	huff->mem = attach_memory_block(sizeof(t_memory_go *), 0, huff);
	huff->mem->size_compressed_code = huff->txt.size_compress; // tamanho da alocação do texto comprimido
	copy_freq_table(huff);

	huff->txt.cp_compressed_code = attach_memory_block((huff->mem->size_compressed_code + 1) * sizeof(unsigned char), 1, huff);
	memcpy(huff->txt.cp_compressed_code, huff->txt.compressed_code, (huff->mem->size_compressed_code + 1) * sizeof(unsigned char));
	/*int j = -1;
	printf("\n\nencoder: compress_code\n");
	while (++j < huff->mem->size_compressed_code)
		printf("'%c'", cp_compressed_code[j]);
	printf("\n");*/
	detach_memory_block(huff->mem);
	detach_memory_block(huff->txt.cp_compressed_code);
	//destroy_memory_block(int proj_id); // destruir memória compartilhada
}

int	main(int argc, char *argv[])
{
	t_huff	huff;

	if (argc == 1)
	{
		dprintf(2, "encoder: error: needed more than one argument\n");
		exit (EXIT_FAILURE);
	}
	setlocale(LC_ALL, "utf8");
	init_memory(&huff);
	get_file(argc, argv, &huff);
	frequence_table(&huff);
	sorted_list(huff.freq_tab.ascii_table, &huff);
	huffman_tree(&huff);
	dictionary(&huff);
	coded_text(&huff);
	compress_code(&huff);
	encode_shared_memory(&huff);
	
	//decompress_code(&huff);
	//decoded_text(&huff);
	//create_files(argc, argv, &huff);
	//free_memory(&huff);
	return (0);
}
