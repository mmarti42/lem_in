/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurbale.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:38:41 by mmarti            #+#    #+#             */
/*   Updated: 2020/03/07 14:38:43 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			add_link(t_link_list **l, t_room *dst, int weight)
{
	t_link_list *new;

	if (!(new = (t_link_list *)ft_memalloc(sizeof(t_link_list))))
		exit(1);
	new->next = *l;
	*l = new;
	if (!(new->data = (t_link *)ft_memalloc(sizeof(t_link))))
		exit(1);
	new->data->dst = dst;
	new->data->weight = weight;
}

void			split_vertex(t_path *vert)
{
	t_room *out;

	if (!(out = (t_room *)ft_memalloc(sizeof(t_room))))
		exit(1);
	out->distance = INF;
	out->links = vert->r->links;
	vert->r->links = NULL;
	add_link(&out->links, vert->r, 0);
	add_link(&vert->r->links, vert->prev->r->out == NULL ?
	vert->prev->r : vert->prev->r->out, -1);
	vert->r->out = out;
	out->in = vert->r;
}

void			split(t_paths_list *p_list)
{
	t_path *p;

	if (!p_list)
		return ;
	while (p_list)
	{
		p = p_list->path->next;
		while (p->next)
		{
			split_vertex(p);
			p = p->next;
		}
		p_list = p_list->next;
	}
}

t_link_list		*del_zero_link(t_link_list *l)
{
	t_link_list *f;
	t_link_list *prev;

	f = l;
	prev = NULL;
	while (l)
	{
		if (l->data->weight == 0)
		{
			if (!prev)
				f = l->next;
			else
				prev->next = l->next;
			free(l->data);
			free(l);
			break ;
		}
		l = l->next;
		prev = l;
	}
	return (f);
}

t_paths_list	*suurbale(t_graph *graph)
{
	int				max_path;
	t_path			*p;
	t_paths_list	*p_list;
	t_paths_list	*final;

	final = NULL;
	max_path = get_max_path(graph->start, graph->end);
	p_list = NULL;
	while (max_path--)
	{
		split(p_list);
		if (!(p = bfs(graph)))
			break ;
		p_list = plist_push_back(p_list, p);
		merge(p_list);
		if (collision_handle(p_list, p->next, 0))
			recount_len(p_list);
		modify_graph(p);
		final = check_steps(p_list, final, graph->ants);
		restore(graph, p_list);
	}
	merge(p_list);
	free_path_list(p_list);
	bubble_sort(final);
	return (final);
}
