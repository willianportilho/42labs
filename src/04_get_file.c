/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:05:23 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 12:22:18 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

static unsigned char	*read_file(int fd, t_huff *huff)
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
			exit_msg_error(PERROR_MSG, "", huff);
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
	int				i;
	int				fd;
	unsigned char	*text_tmp;

	i = 1;
	huff->txt.text = NULL;
	while (++i < argc)
	{
		if (i > ONE_FILE)
			huff->txt.text = ft_strjoin_free_s1(&huff->txt.text, (unsigned char *)ETX_DELIMITER); // adds a separator (int 1) to each text file
		if (check_if_is_a_directory(argv[i]) == TRUE)
			exit_msg_error(SET_MSG, "Is a directory", huff);
		fd = open(argv[i], O_RDONLY);
		if (fd == ERROR)
			exit_msg_error(PERROR_MSG, "", huff);
		text_tmp = read_file(fd, huff);
		huff->txt.text = ft_strjoin_free_s1(&huff->txt.text, text_tmp); // merge more than one text file
		free (text_tmp);
	}
}
