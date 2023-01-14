/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_encoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:21 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 15:50:16 by wportilh         ###   ########.fr       */
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
	//i = -1;
	//while (++i < ASCII_SIZE)
	//{
	//	if (huff->freq_tab.ascii_table[i] > 0)
	//		printf("%d %d\n", i, huff->freq_tab.ascii_table[i]); //print tests
	//}
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
	sorted_list(&huff);
	huffman_tree(&huff);
	dictionary(&huff);
	coded_text(&huff);
	compress_code(&huff);
	decompress_code(&huff);
	decoded_text(&huff);
	create_files(argc, argv, &huff);

	attach_memory_block((23 + 1) * sizeof(char), 1, &huff);
	strncpy(huff.mem.block, "Teste de funcionamento", 23 * sizeof(char));
	printf("encoder: %s\n", huff.mem.block);
	detach_memory_block(huff.mem.block);
	free_memory(&huff);
	return (0);
}
