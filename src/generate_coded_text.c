/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_coded_text.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:37:08 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/13 00:46:00 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

void	generate_coded_text(t_huff *huff)
{
	int pos;
	int	col;
	int	col_2;
	int	size_text;

	pos = -1;
	size_text = 0;
	while (huff->txt.text[++pos])
		size_text += ft_strlen(huff->dic.dictionary[huff->txt.text[pos]]);
	huff->txt.coded_text = malloc((size_text + 1) * sizeof(char));
	if (huff->txt.coded_text == NULL)
		exit(EXIT_FAILURE);
	pos = -1;
	col_2 = -1;
	while (huff->txt.text[++pos])
	{
		col = -1;
		while (huff->dic.dictionary[huff->txt.text[pos]][++col])
			huff->txt.coded_text[++col_2] = huff->dic.dictionary[huff->txt.text[pos]][col];
	}
	huff->txt.coded_text[++col_2] = '\0';
	printf("\n   size_text = %d\n", size_text);
	printf("encoded_text = %s\n", huff->txt.coded_text);
}
