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
	t_paths_list *p;

	buff = create_validation_buff();
	graph = validation(buff);
	if (!(p = suurbale(graph))) {
		printf("no paths\n");
		exit(1);
	}
	print_ants(p, graph->ants);
	//printf("%s", buff);
	return (0);
}