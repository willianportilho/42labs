/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_sorted_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:10:16 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/11 18:24:29 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

static void	start_list(t_huff *huff)
{
	huff->list.root = NULL;
	huff->list.size_list = 0;
}

static void	fill_table(int i, t_node **node, t_huff *huff)
{
	*node = malloc(sizeof(t_node));
	if (!*node)
	{
		dprintf(2, "encoder: error: allocation (fill_table)");
		exit (EXIT_FAILURE);
	}
	(*node)->character = i;
	(*node)->frenquence = huff->freq_tab.ascii_table[i];
	(*node)->right = NULL;
	(*node)->left = NULL;
	(*node)->next = NULL;	
}

static void	sort_list(t_node *node, t_huff *huff)
{
	t_node	*aux;

	if (huff->list.root == NULL)
		huff->list.root = node;
	else if (node->frenquence < huff->list.root->frenquence)
	{
		node->next = huff->list.root;
		huff->list.root = node;
	}
	else
	{
		aux = huff->list.root;
		while (aux->next && (aux->next->frenquence <= node->frenquence))
			aux = aux->next;
		node->next = aux->next;
		aux->next = node;
	}
	huff->list.size_list++;
}

void	generate_sorted_list(t_huff *huff)
{
	int		i;
	t_node	*node;

	i = -1;
	start_list(huff);
	while (++i < SIZE_ASCII)
	{
		if (huff->freq_tab.ascii_table[i] > 0)
		{
			fill_table(i, &node, huff);
			sort_list(node, huff);
		}
	}
	/*t_node	*aux = huff->list.root;
	while (aux)
	{
		printf("character: %c / frequence: %d\n", aux->character, aux->frenquence); // print tests
		aux = aux->next;
	}*/
}
