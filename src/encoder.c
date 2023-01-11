/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:21 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/10 23:43:27 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/huffman.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

/*
	Inicializa uma tabela de tamanho 255, que representa cada símbolo da tabela
	ASCII. Cada index é inicializado com o valor 0. Cada vez que uma letra
	correspondente a um index for encontrada, o index correspondente será
	incrementado, gerando assim os dados de frequencia de cada símbolo. 
*/
void	frequence_table(t_huff *huff)
{
	int		i;

	i = -1;
	while (++i < 256)
		huff->ascii_table[i] = 0;
}

int	main(void)
{
	t_huff	huff;

	frequence_table(&huff);
	return (0);
}
