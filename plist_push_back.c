/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plist_push_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:56:41 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 16:56:42 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				p_len(t_path *p)
{
	int len;

	len = 0;
	while (p)
	{
		p = p->next;
		len++;
	}
	return (len);
}

t_paths_list	*plist_push_back(t_paths_list *p_list, t_path *p)
{
	t_paths_list *first;
	t_paths_list *new;

	first = p_list;
	if (!(new = (t_paths_list *)ft_memalloc(sizeof(t_paths_list))))
		exit(1);
	new->len = p_len(p);
	new->path = p;
	if (!first)
		return (new);
	while (p_list->next)
		p_list = p_list->next;
	p_list->next = new;
	new->prev = p_list;
	return (first);
}
