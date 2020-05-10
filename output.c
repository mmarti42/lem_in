/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:56:38 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 16:56:38 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	teleport_all(char *name, int ants)
{
	int i;

	i = 1;
	while (i <= ants)
	{
		ft_printf("L%d-%s ", i, name);
		i++;
	}
}

t_ants	*buf_delete_ant(t_ants **buf, t_ants *ant)
{
	t_ants *tmp;
	t_ants *ret;

	if (*buf == ant)
		*buf = (*buf)->next;
	else
	{
		tmp = *buf;
		while (tmp->next != ant)
			tmp = tmp->next;
		tmp->next = ant->next;
	}
	ret = ant->next;
	free(ant);
	return (ret);
}

int		print_step(t_ants **buf, int step)
{
	t_ants *tmp;

	if (!*buf)
		return (0);
	tmp = *buf;
	while (tmp && step--)
	{
		tmp->curr = tmp->curr->next;
		ft_printf("L%d-%s ", tmp->num, tmp->curr->r->name);
		if (!tmp->curr->prev->prev)
			return (1);
		if (!tmp->curr->next)
			tmp = buf_delete_ant(buf, tmp);
		else
			tmp = tmp->next;
	}
	return (1);
}

int		print_line(t_paths_list *l, int step)
{
	int ret;

	ret = 0;
	while (l)
	{
		ret += print_step(&l->buf, step);
		l = l->next;
	}
	return (ret);
}

void	print_ants(t_paths_list *l, int ants)
{
	int step;

	step = 0;
	if (l->len == 2)
	{
		teleport_all(l->path->next->r->name, ants);
		free_path_list(l);
		return ;
	}
	fill_buf(l);
	while (print_line(l, ++step))
		ft_printf("\n");
	free_path_list(l);
}
