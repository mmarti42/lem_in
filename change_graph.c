/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:56:04 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 16:56:04 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	restore_p_list(t_paths_list *l)
{
	while (l)
	{
		l->ants = 0;
		l = l->next;
	}
}

void	restore(t_graph *graph, t_paths_list *p_list)
{
	t_llist *rooms;

	rooms = graph->rooms;
	while (rooms)
	{
		rooms->data->parent = NULL;
		rooms->data->distance = INF;
		rooms = rooms->next;
	}
	graph->start->distance = 0;
	restore_p_list(p_list);
}

void	modify_graph(t_path *p)
{
	while (p->next)
	{
		p->r->links = del_link(p->r->links, p->next->r);
		p = p->next;
	}
}
