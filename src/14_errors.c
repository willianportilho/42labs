/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:59:14 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 12:35:03 by wportilh         ###   ########.fr       */
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
	DIR* directory;

	directory = opendir(path);
	if (directory != NULL) // means tha it is a directory
	{
		closedir(directory);
		return (TRUE);
	}
	return (FALSE);
}
