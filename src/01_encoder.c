/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_encoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:21 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 01:09:31 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

/* Inicializa a memória para ser possível liberá-la a qualquer momento*/
static void init_memory(t_huff *huff)
{
	huff->txt.decompressed_code = NULL;
	huff->txt.compressed_code = NULL;
	huff->mem_ab->cp_compressed_code = NULL;
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
}

static void	copy_freq_table(t_huff *huff)
{
	int				i;

	i = -1;
	while (++i < ASCII_SIZE)
		huff->mem_a->ascii_table[i] = huff->freq_tab.ascii_table[i];
}

static void	encode_shared_memory(t_huff *huff)
{
	huff->mem_a = attach_memory_block(sizeof(t_memory_go *), 0, huff);
	huff->mem_a->size_compressed_code = huff->txt.size_compress; // tamanho da alocação do texto comprimido
	copy_freq_table(huff);

	huff->mem_ab->cp_compressed_code = attach_memory_block((huff->mem_a->size_compressed_code + 1) * sizeof(unsigned char), 1, huff);
	memcpy(huff->mem_ab->cp_compressed_code, huff->txt.compressed_code, (huff->mem_a->size_compressed_code + 1) * sizeof(unsigned char));
	
	huff->mem_b = attach_memory_block(sizeof(t_memory_back *), 2, huff);
	printf("compress bytes = %d\n", huff->mem_b->n_bytes_compressed_code);
	printf(" decoded bytes = %d\n", huff->mem_b->n_bytes_decoded_txt);
	printf("          time = %d\n", huff->mem_b->uncompress_time);
	huff->mem_ab->cp_decoded_code = attach_memory_block((huff->mem_b->n_bytes_decoded_txt + 1) * sizeof(unsigned char), 300, huff);
	printf("result encoder= %s\n", huff->mem_ab->cp_decoded_code);
	detach_memory_block(huff->mem_a);
	detach_memory_block(huff->mem_ab->cp_compressed_code);
	
	//destroy_memory_block(int proj_id); // destruir memória compartilhada
}

int	main(int argc, char *argv[])
{
	t_huff	huff;

	if (argc < 3)
	{
		dprintf(2, "encoder: error: needed more than two arguments\nexample: ./encoder -zip txt.txt ...\n");
		exit (EXIT_FAILURE);
	}
	if (!ft_strncmp(argv[1], "-zip", 5))
		huff.flag = ZIP;
	else if (!ft_strncmp(argv[1], "-info", 6))
		huff.flag = INFO;
	else
	{
		dprintf(2, "encoder: error: needed the a flag\nexample: ./encoder -zip\n");
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
	create_files(argc, argv, &huff);
	detach_memory_block(huff.mem_b);
	detach_memory_block(huff.mem_ab->cp_decoded_code);
	destroy_memory_block(2);
	destroy_memory_block(300);
	//free_memory(&huff);
	return (0);
}

	/*int j = -1;
	printf("\n\nencoder: compress_code\n");
	while (++j < huff->mem_a->size_compressed_code)
		printf("'%c'", cp_compressed_code[j]);
	printf("\n");*/

	//printf("ori: %ld\n", huff->txt.size_compress);
	//printf("new: %ld\n", huff->mem_a->size_compressed_code);
	/*i = -1;
	while (++i < ASCII_SIZE)
	{
		if (huff->mem_a->ascii_table[i] > 0)
			printf("mem: %d %d\n", i, huff->mem_a->ascii_table[i]); //print tests
	}*/

	/*i = -1;
	while (++i < ASCII_SIZE)
	{
		if (huff->freq_tab.ascii_table[i] > 0)
			printf("ori: %d %d\n", i, huff->freq_tab.ascii_table[i]); //print tests
	}*/