/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:55:57 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 16:55:59 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths_list	*get_max(t_paths_list *l)
{
	t_paths_list *ret;

	ret = l;
	while (l)
	{
		if (ret->ants + ret->len < l->ants + l->len && l->ants)
			ret = l;
		l = l->next;
	}
	return (ret);
}

static void		swap(t_paths_list *l1, t_paths_list *l2)
{
	t_paths_list tmp;

	tmp.len = l1->len;
	tmp.path = l1->path;
	tmp.ants = l1->ants;
	l1->len = l2->len;
	l1->path = l2->path;
	l1->ants = l2->ants;
	l2->len = tmp.len;
	l2->path = tmp.path;
	l2->ants = tmp.ants;
}

void			bubble_sort(t_paths_list *l)
{
	int				sorted;
	t_paths_list	*first;

	first = l;
	if (!l)
		return ;
	while (1)
	{
		sorted = 1;
		while (l->next)
		{
			if (l->len > l->next->len)
			{
				swap(l, l->next);
				sorted = 0;
			}
			l = l->next;
		}
		if (sorted)
			break ;
		l = first;
	}
}
