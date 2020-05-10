#include "lem_in.h"

void	restore_col(t_path *st, t_path *end)
{
	t_path *prev;

	while (st != end)
	{
		prev = st;
		st->r->pred = NULL;
		st = st->next;
		free(prev);
	}
}

t_path	*get_first(t_path *p)
{
	while (p->prev)
		p = p->prev;
	return (p);
}

t_path	*remove_collision(t_path *col_start1, t_path *col_end2)
{
	t_path *col_start2;
	t_path *col_end1;

	col_start2 = col_end2;
	col_end1 = col_start1;
	while (col_start2->prev->r == col_end1->next->r)
	{
		col_start2 = col_start2->prev;
		col_end1 = col_end1->next;
	}
	restore_col(col_start1->next, col_end1);
	restore_col(col_start2->next, col_end2);
	col_start1->next = col_end2->next;
	col_start1->next->prev = col_start1;
	col_start2->next = col_end1->next;
	col_start2->next->prev = col_start2;
	mdf(get_first(col_start1));
	mdf(get_first(col_start2));
	free(col_end1);
	free(col_end2);
	return (col_start2);
}

t_path	*find_room(t_paths_list *l, t_room *tofind, t_path *ap)
{
	t_path *tmp;

	while (l)
	{
		if (l->path != ap)
		{
			tmp = l->path;
			while (tmp)
			{
				if (tmp->r == tofind)
					return (tmp);
				tmp = tmp->next;
			}
		}
		l = l->next;
	}
	return (NULL);
}

int		collision_handle(t_paths_list *list, t_path *p, int ret)
{
	t_path *tmp;
	t_path *first;

	first = get_first(p);
	while (p->next)
	{
		if ((tmp = find_room(list, p->r, first)))
		{
			ret = 1;
			p = remove_collision(p, tmp);
			first = get_first(p);
		}
		else
			p = p->next;
	}
	return (ret);
}
