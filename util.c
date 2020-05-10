/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:56:53 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 16:56:53 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		recount_len(t_paths_list *l)
{
	while (l)
	{
		l->len = p_len(l->path);
		l = l->next;
	}
}

t_link_list	*del_link2(t_link_list *l, t_room *r)
{
	t_link_list *prev;
	t_link_list *first;

	prev = NULL;
	first = l;
	while (l)
	{
		if (l->data->dst == r)
		{
			if (prev)
				prev->next = l->next;
			else
				first = first->next;
			free(l->data);
			free(l);
			break ;
		}
		prev = l;
		l = l->next;
	}
	return (first);
}

t_link_list	*del_link(t_link_list *l, t_room *r)
{
	if (!l)
		return (NULL);
	if (!l->next)
	{
		free(l->data);
		free(l);
		return (NULL);
	}
	return (del_link2(l, r));
}

int			count_links(t_room *r)
{
	t_link_list	*tmp;
	int			ret;

	ret = 0;
	tmp = r->links;
	while (tmp)
	{
		tmp = tmp->next;
		ret++;
	}
	return (ret);
}

int			get_max_path(t_room *start, t_room *end)
{
	int s_links;
	int e_links;

	s_links = count_links(start);
	e_links = count_links(end);
	if (s_links > e_links)
		return (e_links);
	return (s_links);
}
