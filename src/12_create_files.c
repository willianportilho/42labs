/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_create_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 02:04:35 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 05:56:20 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

static void	restaure_file_descriptors(t_text fd)
{
	dup2(fd.tmpin, 0);
	dup2(fd.tmpout, 1);
	close(fd.tmpin);
	close(fd.tmpout);
}

static int	open_file(char *extension, char *file_name, t_huff *huff)
{
	int		fd;
	char	*unzipped_file_name;

	unzipped_file_name = ft_strjoin(file_name, extension);
	fd = open(unzipped_file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == ERROR)
		exit_msg_error(PERROR_MSG, "", huff);
	free (unzipped_file_name);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

void	create_files(t_huff *huff)
{
	int	i;
	int	j;
	int	fd;

	i = -1;
	j = -1;
	huff->txt.tmpin = dup(0);
	huff->txt.tmpout = dup(1);
	if (huff->flag == INFO)
	{
		while (++i < huff->mem_b->number_of_texts)
		{
			fd = open_file(".42", "willian", huff);
			if (huff->mem_ab.cp_decoded_code)
			{
				while(huff->mem_ab.cp_decoded_code[++j])
				{
					if (huff->mem_ab.cp_decoded_code[j] == ETX) // (int)3 ETX delimitador de término de textos
						break ;
					dprintf(1, "%c", huff->mem_ab.cp_decoded_code[j]);
				}
			}
			close(fd);
		}
		j = -1;
		fd = open_file(".all", "unzipped", huff); // all means all unzipped texts in one file
		if (huff->mem_ab.cp_decoded_code)
		{
			while(huff->mem_ab.cp_decoded_code[++j])
			{
				if (huff->mem_ab.cp_decoded_code[j] == ETX) // (int)3 ETX delimitador de término de textos
					j++;
				if (huff->mem_ab.cp_decoded_code[j])
					dprintf(1, "%c", huff->mem_ab.cp_decoded_code[j]);
			}
		}
		close(fd);
	}
	else
	{
		fd = open_file(".all", "zipped", huff); // all means all zipped texts in one file
		if (huff->txt.size_compress)
		{
			while(++j < huff->txt.size_compress)
					dprintf(1, "%c", huff->txt.compressed_code[j]);
		}
		close(fd);
		restaure_file_descriptors(huff->txt);
	}
}
