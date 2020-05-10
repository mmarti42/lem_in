#include "lem_in.h"

static t_paths_list	*get_min(t_paths_list *l)
{
	t_paths_list *ret;

	ret = l;
	while (l)
	{
		if (ret->ants + ret->len > l->ants + l->len)
			ret = l;
		l = l->next;
	}
	return (ret);
}

static int			count_steps(t_paths_list *l, int ants)
{
	t_paths_list *ret;

	while (ants--)
		(get_min(l)->ants)++;
	ret = get_max(l);
	return (ret->ants + ret->len - 2);
}

static t_path		*p_copy(t_path *p)
{
	t_path *tmp;
	t_path *new;

	new = NULL;
	while (p->next)
		p = p->next;
	while (p)
	{
		if (!(tmp = (t_path *)ft_memalloc(sizeof(t_path))))
			exit(1);
		tmp->r = p->r;
		tmp->next = new;
		if (new)
			new->prev = tmp;
		new = tmp;
		p = p->prev;
	}
	return (new);
}

static t_paths_list	*lst_copy(t_paths_list *l)
{
	t_paths_list *new;
	t_paths_list *tmp;

	new = NULL;
	while (l->next)
		l = l->next;
	while (l)
	{
		if (!(tmp = (t_paths_list *)ft_memalloc(sizeof(t_paths_list))))
			exit(1);
		tmp->len = l->len;
		tmp->path = p_copy(l->path);
		tmp->ants = l->ants;
		tmp->next = new;
		if (new)
			new->prev = tmp;
		new = tmp;
		l = l->prev;
	}
	return (new);
}

t_paths_list		*check_steps(t_paths_list *p_list,
		t_paths_list *final, int ants)
{
	static int	last_count_steps;
	int			tmp;

	if (!last_count_steps)
	{
		last_count_steps = count_steps(p_list, ants);
		return (lst_copy(p_list));
	}
	tmp = count_steps(p_list, ants);
	if (tmp < last_count_steps)
	{
		last_count_steps = tmp;
		return (lst_copy(p_list));
	}
	return (final);
}
