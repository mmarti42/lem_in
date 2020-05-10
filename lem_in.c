/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:42:09 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/07 14:37:59 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	char			*buff;
	t_graph			*graph;
	t_paths_list	*list;

	buff = create_validation_buff();
	graph = validation(buff);
	if (!(list = suurbale(graph)))
	{
		ft_putstr("Error\n");
		exit(0);
	}
	printf("%s", buff);
	free(buff);
	print_ants(list, graph->ants);
	return (0);
}
