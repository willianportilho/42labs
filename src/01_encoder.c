/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_encoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:21 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 05:54:23 by wportilh         ###   ########.fr       */
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
	huff->mem_ab.cp_decoded_code = NULL;
	huff->txt.compressed_code = NULL;
	huff->mem_ab.cp_decoded_code = NULL;
	huff->mem_b = NULL;
	huff->txt.size_compress = 0;
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
	if (huff->txt.text)
	{
		while (huff->txt.text[++i])
			huff->freq_tab.ascii_table[huff->txt.text[i]]++;
	}		
}

static void	copy_freq_table(t_huff *huff)
{
	int				i;

	i = -1;
	while (++i < ASCII_SIZE)
		huff->mem_a->ascii_table[i] = huff->freq_tab.ascii_table[i];
}

static void	encode_shared_memory(int argc, t_huff *huff)
{
	if (huff->flag == ZIP)
	{
		huff->mem_a = attach_memory_block(sizeof(t_memory_go *), 0, huff);
		huff->mem_a->size_compressed_code = huff->txt.size_compress; // tamanho da alocação do texto comprimido
		huff->mem_a->number_of_texts = argc - 2;
		copy_freq_table(huff);
		huff->mem_ab.cp_compressed_code = attach_memory_block((huff->mem_a->size_compressed_code + 1) * sizeof(unsigned char), 1, huff);
		memcpy(huff->mem_ab.cp_compressed_code, huff->txt.compressed_code, (huff->mem_a->size_compressed_code + 1) * sizeof(unsigned char));
		detach_memory_block(huff->mem_a);
		detach_memory_block(huff->mem_ab.cp_compressed_code);
	}
	else
	{
		huff->mem_b = attach_memory_block(sizeof(t_memory_back *), 2, huff);
		huff->mem_ab.cp_decoded_code = attach_memory_block((huff->mem_b->n_bytes_decoded_txt + 1) * sizeof(unsigned char), 3, huff);
	}
}

static void	check_args(int argc, char *argv[], t_huff *huff)
{
	if (argc < 2)
	{
		dprintf(2, "encoder: error: needed more than two arguments\nexample: ./encoder -zip txt.txt ...\n");
		exit (EXIT_FAILURE);
	}
	else if (!ft_strncmp(argv[1], "-info", 6))
	{
		if (argc > 2)
		{
			dprintf(2, "encoder: error: -info flag has no arguments\n");
			exit (EXIT_FAILURE);
		}
		huff->flag = INFO;
	}
	else if (!ft_strncmp(argv[1], "-zip", 5))
		huff->flag = ZIP;
	else
	{
		dprintf(2, "encoder: error: needed the a flag\nexample: ./encoder -zip or ./encoder -info\n");
		exit (EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	t_huff	huff;

	check_args(argc, argv, &huff);
	setlocale(LC_ALL, "utf8");
	init_memory(&huff);
	if (huff.flag == ZIP)
	{
		get_file(argc, argv, &huff);
		frequence_table(&huff);
		sorted_list(huff.freq_tab.ascii_table, &huff);
		huffman_tree(&huff);
		dictionary(&huff);
		coded_text(&huff);
		compress_code(&huff);
		encode_shared_memory(argc, &huff);
		create_files(&huff);
	}
	if (huff.flag == INFO)
	{
		encode_shared_memory(argc, &huff);		
		create_files(&huff);
		detach_memory_block(huff.mem_b);
		detach_memory_block(huff.mem_ab.cp_decoded_code);
		destroy_memory_block(2);
		destroy_memory_block(3);
	}
	free_memory(&huff);
	return (0);
}
