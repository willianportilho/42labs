/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_encoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:21 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 12:21:16 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

/* Initialize memory. You can release it at any time*/
static void	init_memory(t_huff *huff)
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
	Initializes a table of size 255, which represents each symbol in the table
ASCII. Each index is initialized with the value 0. Each time that a letter
corresponding to an index is founded, the corresponding index will be
incremented, generating the frequency data of each symbol. 
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

static void	shared_memory(int argc, t_huff *huff)
{
	if (huff->flag == ZIP)
	{
		huff->mem_a = attach_memory_block(sizeof(t_memory_go *), 0, huff);
		huff->mem_a->size_compressed_code = huff->txt.size_compress; // Compressed text allocation size
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
		check_args_error(ARG_ERROR);
	else if (!ft_strncmp(argv[1], "-unzip", 7))
	{
		if (argc > 2)
			check_args_error(ARG_ERROR_2);
		huff->flag = UNZIP;
	}
	else if (!ft_strncmp(argv[1], "-zip", 5))
		huff->flag = ZIP;
	else
		check_args_error(ARG_ERROR_3);
}

static void	print_info(t_huff *huff)
{
	huff->mem_b->uncompress_inicial_time = current_time() - huff->mem_b->uncompress_inicial_time;
	dprintf(1, "----------------------------------------\n");
	dprintf(1, "\ninfo.\n\n");
	dprintf(1, "total decompressed: %10d bits\n", huff->mem_b->n_bytes_decoded_txt * 8);
	dprintf(1, "total   compressed: %10d bits\n", huff->mem_b->n_bytes_compressed_code * 8);
	dprintf(1, "time to uncompress: %10d   ms\n", huff->mem_b->uncompress_inicial_time);
	dprintf(1, "\n----------------------------------------\n");
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
		shared_memory(argc, &huff);
		create_files(&huff);
	}
	if (huff.flag == UNZIP)
	{
		shared_memory(argc, &huff);
		print_info(&huff);
		create_files(&huff);
		free_shared_memory_two(&huff);
	}
	free_memory(&huff);
	return (0);
}
