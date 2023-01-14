/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_huffman_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:17:28 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/14 10:34:09 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

/* detaches and return a node*/
static t_node	*detach_a_node(t_huff *huff)
{
	t_node	*detached_node;

	detached_node = NULL;
	if (huff->list.root == NULL)
		return (detached_node);
	detached_node = huff->list.root;
	huff->list.root = huff->list.root->next;
	detached_node->next = NULL;
	huff->list.size_list--;
	return (detached_node);
}

void	print_tree(t_node *root, int size_list)
{
	if ((root->left == NULL) && (root->right == NULL))
		printf("leaf = %c | heigth = %d\n", root->character, size_list);
	else
	{
		print_tree(root->left, size_list + 1);
		print_tree(root->right, size_list + 1);
	}
}

void	huffman_tree(t_huff *huff)
{
	t_node	*parent;
	t_node	*child_left;
	t_node	*child_right;

	while (huff->list.size_list > 1)
	{
		child_left = detach_a_node(huff);
		child_right = detach_a_node(huff);
		parent = (t_node *)malloc(sizeof(t_node));
		if (!parent)
			exit_msg_error(PERROR_MSG, "", huff);
		parent->left = child_left;
		parent->right = child_right;
		parent->character = 'p'; // can be any character
		parent->frequency = child_left->frequency + child_right->frequency;
		parent->next = NULL; // here we detaches the parent node
		sort_list(parent, huff); // and here, we reinsert in sort mode
	}
	//printf("\nÁrvore montada\n");
	//print_tree(huff->list.root, 0);
}
