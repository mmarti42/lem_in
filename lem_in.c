/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:42:09 by kdeloise          #+#    #+#             */
/*   Updated: 2020/02/25 20:42:16 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int main(int argc, char **argv)
{
	char	*buff;
	t_graph *graph;

	buff = create_validation_buff();
	graph = validation(buff);
	suurbale(graph);
	//printf("%s", buff);
	return (0);
}