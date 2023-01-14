/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_shared_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:40:07 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 15:45:33 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

static int	get_shared_block(int size_block, int proj_id)
{
	int	key;
	int	id;

	key = ftok("Makefile", proj_id);
	if (key == ERROR)
		return (ERROR);
	id = shmget(key, size_block, 0644 | IPC_CREAT);
	if (id == ERROR)
		return (ERROR);
	return (id);
}

void	attach_memory_block(int size_block, int proj_id, t_huff *huff)
{
	int	id_block;

	id_block = get_shared_block(size_block, proj_id);
	if (id_block == ERROR)
		exit_msg_error(PERROR_MSG, "", huff);
	huff->mem.block = shmat(id_block, NULL, 0);
	if (huff->mem.block == (char *)ERROR)
		exit_msg_error(PERROR_MSG, "", huff);
}

int	detach_memory_block(char *block)
{
	int	result;

	result = shmdt(block);
	if (result == ERROR)
		return (ERROR);
	return (EXIT_SUCCESS);
}

int	destroy_memory_block(int proj_id)
{
	int	id_block;
	int	destroy_result;

	id_block = get_shared_block(0, proj_id);
	if (id_block == ERROR)
		return (ERROR);
	destroy_result = shmctl(id_block, IPC_RMID, NULL);
	if (destroy_result == ERROR)
		return (ERROR);
	return (destroy_result);
}
