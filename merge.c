/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:56:46 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 16:56:46 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_llist		*b_find(t_room *r, t_llist *buf)
{
	while (buf)
	{
		if (buf->data == r)
			break ;
		buf = buf->next;
	}
	return (buf);
}

static t_llist		*add_to_buf(t_room *r, t_llist *buf)
{
	t_llist *new;

	if (b_find(r, buf))
		return (buf);
	if (!(new = (t_llist *)ft_memalloc(sizeof(t_llist))))
		exit(1);
	new->next = buf;
	new->data = r;
	return (new);
}

static void			merge_vertex(t_path *vert, t_llist **buf)
{
	if (vert->r->out)
	{
		free_links(vert->r->links);
		vert->r->out->links = del_zero_link(vert->r->out->links);
		vert->r->links = vert->r->out->links;
	}
	else if (vert->r->in)
	{
		vert->r = vert->r->in;
		if (vert->r == vert->next->r)
		{
			vert->next = vert->next->next;
			free(vert->next->prev);
			if (vert->next)
				vert->next->prev = vert;
		}
	}
	*buf = add_to_buf(vert->r->out, *buf);
	vert->r->in = NULL;
	vert->r->out = NULL;
}

static void			free_buf(t_llist *buf)
{
	if (!buf)
		return ;
	free_buf(buf->next);
	free(buf->data);
	free(buf);
}

void				merge(t_paths_list *p_list)
{
	t_path	*p;
	t_llist	*buf;

	buf = NULL;
	if (!p_list)
		return ;
	while (p_list)
	{
		p = p_list->path->next;
		while (p->next)
		{
			merge_vertex(p, &buf);
			p = p->next;
		}
		p_list = p_list->next;
	}
	free_buf(buf);
}
