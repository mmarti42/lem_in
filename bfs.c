#include "lem_in.h"

void	recursive_add(t_room *w, t_room *p, t_room *start, t_rooms **q)
{
	if (w == start || w->col_fl)
		return ;
	w->parent = p;
	w->col_fl = 1;
	recursive_add(w->pred, w, start, q);
	q_add_links(q, w->links, w, start);
}

t_path	*p_push_begin(t_room *r, t_path *p)
{
	t_path *new;

	if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
		exit(1);
	new->r = r;
	new->next = p;
	if (p)
		p->prev = new;
	return (new);
}

t_path	*assemble_path(t_room *end, t_room *start)
{
	t_path	*p;
	int		len;

	p = NULL;
	len = 0;
	while (end != start)
	{
		p = p_push_begin(end, p);
		end = end->parent;
		len++;
	}
	p = p_push_begin(start, p);
	return (p);
}

void	q_free(t_rooms *q)
{
	if (!q)
		return ;
	q_free(q->next);
	free(q);
}

t_path	*bfs(t_graph *g)
{
	t_room	*w;
	t_rooms *q;

	w = g->start;
	q = NULL;
	q_add_links(&q, w->links, w, g->start);
	if (!(w = q_get(&q)))
		return (NULL);
	while (w != g->end)
	{
		if (w->pred)
		{
			w->col_fl = 1;
			recursive_add(w->pred, w, g->start, &q);
		}
		else
			q_add_links(&q, w->links, w, g->start);
		if (!(w = q_get(&q)))
			return (NULL);
	}
	q_free(q);
	return (assemble_path(w, g->start));
}
