/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_decoded_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:22:19 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 12:25:44 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

static void	alloc_decoded_text(t_huff *huff)
{
	int				size;

	size = ft_strlen(huff->txt.decompressed_code) + 1;
	huff->txt.decoded_text = calloc(size + 1, sizeof(unsigned char));
	if (huff->txt.decoded_text == NULL)
		exit_msg_error(PERROR_MSG, "", huff);
}

void	decoded_text(t_huff *huff)
{
	int				pos;
	int				pos_2;
	t_node			*aux;

	pos = -1;
	pos_2 = -1;
	aux = huff->list.root;
	alloc_decoded_text(huff);
	while (huff->txt.decompressed_code[++pos])
	{
		if (huff->txt.decompressed_code[pos] == '0')
			aux = aux->left;
		else
			aux = aux->right;
		if ((aux->left == NULL) && (aux->right == NULL))
		{
			if (aux->frequency == 0) // treatment of remaining 0 bits
			{
				huff->txt.decoded_text[++pos_2] = '\0';
				return ;
			}	
			huff->txt.decoded_text[++pos_2] = aux->character;
			aux->frequency--; // treatment for leftover bits in last byte of uncompressed code
			aux = huff->list.root;
		}
	}
	huff->txt.decoded_text[++pos_2] = '\0';
}
