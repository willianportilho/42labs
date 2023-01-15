/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:31:44 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/15 01:50:04 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

static void	free_tree(t_node *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}

static void	free_vector(char **vector)
{
	int	i;

	i = -1;
	if (vector == NULL)
		return ;
	while (vector[++i])
	{
		free(vector[i]);	
	}
	free(vector);
}

void	free_memory(t_huff *huff)
{
	free_tree(huff->list.root);
	free_vector(huff->dic.dictionary);
	free(huff->txt.decompressed_code);
	free(huff->txt.compressed_code);
	free(huff->txt.decoded_text);
	free(huff->txt.coded_text);
	free(huff->txt.text);
}
