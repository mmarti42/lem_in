/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:56:21 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 16:56:21 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_empty(t_paths_list *l)
{
	while (l)
	{
		if (l->ants)
			return (1);
		l = l->next;
	}
	return (0);
}

void	add_to_buff(t_paths_list *l, int i)
{
	t_ants	*new;

	if (!(new = (t_ants *)ft_memalloc(sizeof(t_ants))))
		exit(1);
	new->num = i;
	new->curr = l->path;
	if (!l->last_ant)
		l->buf = new;
	else
		l->last_ant->next = new;
	l->last_ant = new;
}

void	fill_buf(t_paths_list *l)
{
	t_paths_list	*first;
	int				i;

	i = 1;
	first = l;
	while (1)
	{
		if (l->ants)
		{
			(l->ants)--;
			add_to_buff(l, i);
			i++;
		}
		if (!is_empty(first))
			break ;
		else if (!(l = l->next))
			l = first;
	}
}
