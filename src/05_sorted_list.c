/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_sorted_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:10:16 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 08:52:14 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

static void	init_list(t_huff *huff)
{
	huff->list.root = NULL;
	huff->list.size_list = 0;
}

static void	fill_table(int i, unsigned int *ascii_table, t_node **node, t_huff *huff)
{
	*node = malloc(sizeof(t_node));
	if (!*node)
		exit_msg_error(PERROR_MSG, "", huff);
	(*node)->character = i;
	(*node)->frequency = ascii_table[i];
	(*node)->right = NULL;
	(*node)->left = NULL;
	(*node)->next = NULL;
}

void	sort_list(t_node *node, t_huff *huff)
{
	t_node	*aux;

	if (huff->list.root == NULL)
		huff->list.root = node;
	else if (node->frequency < huff->list.root->frequency)
	{
		node->next = huff->list.root;
		huff->list.root = node;
	}
	else
	{
		aux = huff->list.root;
		while (aux->next && (aux->next->frequency <= node->frequency))
			aux = aux->next;
		node->next = aux->next;
		aux->next = node;
	}
	huff->list.size_list++;
}

void	sorted_list(unsigned int *ascii_table, t_huff *huff)
{
	int		i;
	t_node	*node;

	i = -1;
	init_list(huff);
	while (++i < ASCII_SIZE)
	{
		if (ascii_table[i] > 0)
		{
			fill_table(i, ascii_table, &node, huff);
			sort_list(node, huff);
		}
	}
}
