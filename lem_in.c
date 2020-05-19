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

void	free_links(t_link_list *l)
{
	if (!l)
		return ;
	free_links(l->next);
	free(l->data);
	free(l);
}

void	free_data(t_room *r)
{
	if (!r)
		return ;
	free_links(r->links);
	free(r->name);
	free(r);
}

void	free_rooms(t_llist *r)
{
	if (!r)
		return ;
	free_rooms(r->next);
	free_data(r->data);
	free(r);
}

void	free_graph(t_graph *g)
{
	free_rooms(g->rooms);
	free(g->value_for_free);
	free(g);
}

int		main(void)
{
	char			*buff;
	t_graph			*graph;
	t_paths_list	*list;

	if (!(buff = create_validation_buff()))
		ft_exit("Error");
	graph = validation(buff);
	set_distance(graph->rooms);
	graph->start->distance = 0;
	if (!(list = suurbale(graph)))
		ft_exit("Error");
	ft_printf("%s", buff);
	free(buff);
	print_ants(list, graph->ants);
	free_graph(graph);
	return (0);
}
