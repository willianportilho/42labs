/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_decoded_text.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:22:19 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/13 10:47:08 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

void	generate_decoded_text(t_huff *huff)
{
	int				size;
	int				pos;
	int				pos_2;
	t_node			*aux;

	size = ft_strlen(huff->txt.coded_text);
	huff->txt.decoded_text = calloc(size, sizeof(unsigned char));
	if (huff->txt.decoded_text == NULL)
		exit(EXIT_FAILURE);
	pos = -1;
	pos_2 = -1;
	aux = huff->list.root;
	while (huff->txt.coded_text[++pos])
	{
		if (huff->txt.coded_text[pos] == '0')
			aux = aux->left;
		else
			aux = aux->right;
		if ((aux->left == NULL) && (aux->right == NULL))
		{
			huff->txt.decoded_text[++pos_2] = aux->character;
			aux = huff->list.root;
		}
	}
	huff->txt.decoded_text[pos] = '\0';
	printf("\n result = %s\n", huff->txt.decoded_text);
}
