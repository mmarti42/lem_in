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

void	pp(t_path *p)
{
	while (p->next)
	{
		if (p->prev)
			p->r->pred = p->prev->r;
		p = p->next;
	}
}

void	restore_p_list(t_paths_list *l)
{
	while (l)
	{
		pp(l->path);
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
		rooms->data->pred = NULL;
		rooms->data->col_fl = 0;
		rooms = rooms->next;
	}
	restore_p_list(p_list);
}

void	modify_graph(t_path *p)
{
	while (p->next)
	{
		p->r->links = del_link(p->r->links, p->next->r);
		if (p->prev)
			p->r->pred = p->prev->r;
		p = p->next;
	}
}

void	mdf(t_path *p)
{
	while (p->next)
	{
		if (p->prev)
			p->r->pred = p->prev->r;
		p = p->next;
	}
}
