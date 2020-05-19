/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:56:46 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 16:56:46 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	q_insert(t_rooms *q, t_rooms *new)
{
	while (q->next && q->r->distance <= new->r->distance)
		q = q->next;
	if (!q->next && q->r->distance <= new->r->distance)
	{
		q->next = new;
		new->prev = q;
	}
	else
	{
		if (q->prev)
			q->prev->next = new;
		new->prev = q->prev;
		new->next = q;
		q->prev = new;
	}
}

void	q_add_room(t_rooms **q, t_room *r)
{
	t_rooms			*new;

	if (!(new = (t_rooms *)ft_memalloc(sizeof(t_rooms))))
		exit(1);
	new->r = r;
	if (!*q || r->distance < (*q)->r->distance)
	{
		if (*q)
			(*q)->prev = new;
		new->next = *q;
		*q = new;
	}
	else
		q_insert(*q, new);
}

void	q_add_links(t_rooms **q, t_link_list *l, t_room *parent)
{
	while (l)
	{
		if (l->data->dst->distance == INF)
		{
			l->data->dst->distance = parent->distance + l->data->weight;
			l->data->dst->parent = parent;
			q_add_room(q, l->data->dst);
		}
		l = l->next;
	}
}

t_room	*q_get(t_rooms **q)
{
	t_room	*ret;
	t_rooms *tmp;

	if (!*q)
		return (NULL);
	ret = (*q)->r;
	tmp = *q;
	*q = (*q)->next;
	free(tmp);
	return (ret);
}
