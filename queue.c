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

void	q_add_room(t_rooms **q, t_link *l)
{
	t_rooms			*new;
	static t_rooms	*last;

	if (!(new = (t_rooms *)ft_memalloc(sizeof(t_rooms))))
		exit(1);
	new->r = l->dst;
	new->next = NULL;
	if (!*q)
		*q = new;
	else
		last->next = new;
	last = new;
}

void	q_add_links(t_rooms **q, t_link_list *l, t_room *parent, t_room *start)
{
	while (l)
	{
		if (!l->data->dst->parent &&
			l->data->dst != parent->parent && l->data->dst != start)
		{
			l->data->dst->parent = parent;
			q_add_room(q, l->data);
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
