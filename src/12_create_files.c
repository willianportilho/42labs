/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_create_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 02:04:35 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 10:16:31 by wportilh         ###   ########.fr       */
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

static int	open_file(unsigned char *extension, unsigned char *file_name, unsigned char *number_file, t_huff *huff)
{
	int				fd;
	unsigned char	*unzipped_file_name;

	unzipped_file_name = NULL;
	unzipped_file_name = ft_str_unsigned_join(file_name, number_file);
	unzipped_file_name = ft_strjoin_free_s1(&unzipped_file_name, extension);
	fd = open((char *)unzipped_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == ERROR)
		exit_msg_error(PERROR_MSG, "", huff);
	free (unzipped_file_name);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

static void	create_zipped_file(t_huff *huff)
{
	int	i;
	int	fd;

	i = -1;
	fd = open_file((unsigned char *)".all", (unsigned char *)"zipped", (unsigned char *)"", huff); // all means all zipped texts in one file
	if (huff->txt.size_compress)
	{
		while (++i < huff->txt.size_compress)
			dprintf(1, "%c", huff->txt.compressed_code[i]);
	}
	close(fd);
}

static void	create_all_unzipped_in_one_file(t_huff *huff)
{
	int	i;
	int	fd;

	i = -1;
	fd = open_file((unsigned char *)".all", (unsigned char *)"unzipped", (unsigned char *)"", huff); // all means all unzipped texts in one file
	if (huff->mem_ab.cp_decoded_code)
	{
		while (huff->mem_ab.cp_decoded_code[++i])
		{
			if (huff->mem_ab.cp_decoded_code[i] == ETX) // (int)3 ETX delimitador de término de textos
				i++;
			if (huff->mem_ab.cp_decoded_code[i])
				dprintf(1, "%c", huff->mem_ab.cp_decoded_code[i]);
		}
	}
	close(fd);
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
	if (huff->flag == UNZIP)
	{
		while (++i < huff->mem_b->number_of_texts) // creates the files one by one
		{
			fd = open_file((unsigned char *)".42", (unsigned char *)"unzipped_", (unsigned char *)ft_itoa(i), huff);
			if (huff->mem_ab.cp_decoded_code)
			{
				while (huff->mem_ab.cp_decoded_code[++j])
				{
					if (huff->mem_ab.cp_decoded_code[j] == ETX) // (int)3 ETX delimitador de término de textos
						break ;
					dprintf(1, "%c", huff->mem_ab.cp_decoded_code[j]);
				}
			}
			close(fd);
		}
		create_all_unzipped_in_one_file(huff);
	}
	else
		create_zipped_file(huff);
	restaure_file_descriptors(huff->txt);
}
