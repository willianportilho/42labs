/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_shared_memory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:49:23 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 16:52:41 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

void	encode_shared_memory(t_huff *huff)
{
	huff->mem = attach_memory_block(sizeof(t_memory *), 1, huff);
	huff->mem->ascii_table[0] = 12;
	huff->mem->ascii_table[1] = 13;
	huff->mem->ascii_table[2] = 14;
	huff->mem->ascii_table[3] = 15;
	printf("encoder: %d\n", huff->mem->ascii_table[0]);
	printf("encoder: %d\n", huff->mem->ascii_table[1]);
	printf("encoder: %d\n", huff->mem->ascii_table[2]);
	printf("encoder: %d\n", huff->mem->ascii_table[3]);
	detach_memory_block(huff->mem);
}
