/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:59:14 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 08:49:17 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

void	exit_msg_error(int flag, char *message, t_huff *huff)
{
	if (flag == PERROR_MSG)
		perror("encoder: error");
	else
		dprintf(2, "encoder: error: %s\n", message);
	free_memory(huff);
	exit (EXIT_FAILURE);
}

int	check_if_is_a_directory(char *path)
{
	DIR	*directory;

	directory = opendir(path);
	if (directory != NULL) // means tha it is a directory
	{
		closedir(directory);
		return (TRUE);
	}
	return (FALSE);
}

void	check_args_error(char *message)
{
	dprintf(2, "encoder: error: %s\n", message);
	dprintf(2, "\nHOW TO USE THE PROGRAMM\n\n");
	dprintf(2, "first: if you ever want to zip one or more text files:\n");
	dprintf(2, "./encoder -zip your_text_to_zip your_another_text_to_zip ...");
	dprintf(2, " (a zipped file (.zip) is generated)");
	dprintf(2, "\nsecond: to unzip your texts:\n");
	dprintf(2, "./decode (without flags or arguments)\n");
	dprintf(2, "third: to get the files separated (.42 extension), and one file");
	dprintf(2, " with all of them togheter (.all extension):\n");
	dprintf(2, "./encoder -unzip\n");
	dprintf(2, "\n*you can use 'ipcrm -a' command if a memory error occur\n");
	dprintf(2, "ENJOY\n");
	exit (EXIT_FAILURE);
}
