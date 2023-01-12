/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_dictionary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:43:19 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/12 20:26:34 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"

/*	Checks the tree height. The return defines the lenght of the dictionary*/
static int	tree_heigth(t_node *root)
{
	int	left;
	int	right;

	if (root == NULL)
		return (-1);
	left = tree_heigth(root->left) + 1;
	right = tree_heigth(root->right) + 1;
	if (left > right)
		return (left);
	return (right);
}

static void    alloc_dictionary(t_dictionary *dic)
{
	int	i;

	i = -1;
	dic->dictionary = malloc((ASCII_SIZE + 1) * sizeof(char **));
	if (dic->dictionary == NULL)
		exit(EXIT_FAILURE);
	while (++i < ASCII_SIZE)
	{
		dic->dictionary[i] = calloc((dic->lenght_col + 1), sizeof(char));
		if (dic->dictionary[i] == NULL)
			exit(EXIT_FAILURE);
	}
	dic->dictionary[i] = NULL;
}

static void	fill_dictionary(int lengh_col, char *path, char **dictionary, t_node *root)
{
	char left[lengh_col];
	char right[lengh_col];

	if ((root->left == NULL) && (root->right == NULL))
		strcpy(dictionary[root->character], path);
	else
	{
		strcpy(left, path);
		strcpy(right, path);
		strcat(left, "0");
		strcat(right, "1");
		fill_dictionary(lengh_col, left, dictionary, root->left);
		fill_dictionary(lengh_col, right, dictionary, root->right);
	}
}

void	print_dictionary(unsigned int *ascii_table, char **dictionary)
{
	int	i;

	i = -1;
	printf("\nDicionário\n");
	while (++i < ASCII_SIZE)
	{
		if (ascii_table[i] > 0)
				printf("%3d: %s\n", i, dictionary[i]);
	}
}

void    generate_dictionary(t_huff *huff)
{
	huff->dic.lenght_col = tree_heigth(huff->list.root) + 1;
	alloc_dictionary(&huff->dic);
	fill_dictionary(huff->dic.lenght_col, "", huff->dic.dictionary, huff->list.root);
	print_dictionary(huff->freq_tab.ascii_table, huff->dic.dictionary);
}
