/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:05:23 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 04:20:11 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

static unsigned char *read_file(int fd)
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
	int 			i;
	int				fd;
	unsigned char	*text_tmp;

	i = 0;
	huff->txt.text = NULL;
	while (++i < argc)
	{
		if (i > ONE_FILE)
			huff->txt.text = ft_strjoin_free_s1(&huff->txt.text, (unsigned char *)ETX_DELIMITER); // adiciona um separador (int 1) a cada arquivo de texto
		fd = open(argv[i], O_RDONLY);
		if (fd == -1)
		{
			dprintf(2, "file error\n");
			free_memory(huff);
			exit (EXIT_FAILURE);
		}
		text_tmp = read_file(fd);
		huff->txt.text = ft_strjoin_free_s1(&huff->txt.text, text_tmp); // une mais de um arquivo de texto
		free (text_tmp);
	}
	//printf("%s\n", huff->txt.text); //printa na tela
}
