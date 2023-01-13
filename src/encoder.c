/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:21 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/13 10:04:31 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

unsigned char *read_file(int fd)
{
	unsigned char	*str_file;
	unsigned char	*buffer;
	int				bytes_read;

	bytes_read = TRUE;
	str_file = NULL;
	while (bytes_read > 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
		{
			free (buffer);
			exit(EXIT_FAILURE);
		}
		buffer[BUFFER_SIZE] = '\0';
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
			str_file = ft_strjoin_free_s1(&str_file, buffer);
		free (buffer);
	}
	return (str_file);
}

void	get_file(int argc, char *argv[], t_huff *huff)
{
	int i;
	int	fd;

	i = 1;
	huff->txt.text = NULL;
	while (i < argc)
	{
	fd = open(argv[i++], O_RDONLY);
	if (fd == -1)
	{
		dprintf(2, "file error\n");
		free (huff->txt.text);
		exit (EXIT_FAILURE);
	}
	huff->txt.text = read_file(fd);
	}
	//printf("%s\n", huff->txt.text); //printa na tela
}

/*
	Inicializa uma tabela de tamanho 255, que representa cada símbolo da tabela
	ASCII. Cada index é inicializado com o valor 0. Cada vez que uma letra
	correspondente a um index for encontrada, o index correspondente será
	incrementado, gerando assim os dados de frequencia de cada símbolo. 
*/
void	generate_frequence_table(t_huff *huff)
{
	int				i;

	i = -1;
	while (++i < ASCII_SIZE)
		huff->freq_tab.ascii_table[i] = 0;
	i = -1;
	while (huff->txt.text[++i])
	{
		//if (huff->txt.text[i] < ASCII_SIZE)
			huff->freq_tab.ascii_table[huff->txt.text[i]]++;
	}
	/*i = -1;
	while (++i < ASCII_SIZE)
	{
		if (huff->freq_tab.ascii_table[i] > 0)
			printf("%d %d\n", i, huff->freq_tab.ascii_table[i]); //print tests
	}*/
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
	get_file(argc, argv, &huff);
	generate_frequence_table(&huff);
	generate_sorted_list(&huff);
	generate_huffman_tree(&huff);
	generate_dictionary(&huff);
	generate_coded_text(&huff);
	generate_decoded_text(&huff);
	return (0);
}
