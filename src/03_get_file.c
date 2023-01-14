/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:05:23 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/13 22:07:11 by wportilh         ###   ########.fr       */
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
