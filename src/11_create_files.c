/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_create_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 02:04:35 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 10:35:01 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

void	create_files(int argc, char *argv[], t_huff *huff)
{
	int	i;
	int	j;
	int	new_file;

	i = 0;
	j = -1;
	while ((++i < argc) && (argc > 2))
	{
		huff->file.name_new_file = ft_strjoin(argv[i], ".dec"); // dec significa descompactado
		new_file = open(huff->file.name_new_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (new_file == -1)
			exit_msg_error(PERROR_MSG, "", huff);
		dup2(new_file, STDOUT_FILENO);
		close(new_file);
		if (huff->txt.decoded_text)
		{
			while(huff->txt.decoded_text[++j])
			{
				if (huff->txt.decoded_text[j] == ETX) // (int)3 ETX delimitador de término de textos
					break ;
				dprintf(1, "%c", huff->txt.decoded_text[j]);
			}
		}
		close(new_file);
		free(huff->file.name_new_file);
	}
	j = -1;
	huff->file.name_new_file = ft_strjoin("decompress_txt", ".all"); // all means all decompress texts in one file
	new_file = open(huff->file.name_new_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_file == -1)
		exit_msg_error(PERROR_MSG, "", huff);
	dup2(new_file, STDOUT_FILENO);
	close(new_file);
	if (huff->txt.decoded_text)
	{
		while(huff->txt.decoded_text[++j])
		{
			if (huff->txt.decoded_text[j] == ETX) // (int)3 ETX delimitador de término de textos
				j++;
			if (huff->txt.decoded_text[j])
				dprintf(1, "%c", huff->txt.decoded_text[j]);
		}
	}
	close(new_file);
	free(huff->file.name_new_file);
	j = -1;
	huff->file.name_new_file = ft_strjoin("compress_txt", ".all"); // all means all decompress texts in one file
	new_file = open(huff->file.name_new_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_file == -1)
		exit_msg_error(PERROR_MSG, "", huff);
	dup2(new_file, STDOUT_FILENO);
	close(new_file);
	if ((huff->txt.compressed_code) || (huff->txt.size_compress))
	{
		while((huff->txt.compressed_code[++j]) || (j < huff->txt.size_compress))
				dprintf(1, "%c", huff->txt.compressed_code[j]);
	}
	close(new_file);
	free(huff->file.name_new_file);
}
