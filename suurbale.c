/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurbale.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:38:41 by mmarti            #+#    #+#             */
/*   Updated: 2020/03/07 14:38:43 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <string.h>
int		count_links(t_room *r)
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

int get_max_path(t_room *start, t_room *end)
{
    int s_links;
    int e_links;

    s_links = count_links(start);
    e_links = count_links(end);
    if (s_links > e_links)
        return e_links;
    return s_links;
}

t_rooms	*p_find(t_rooms *p, t_room *r)
{
	while (p)
	{
		if (p->r == r)
			return (p);
		p = p->next;
	}
	return (NULL);
}

t_link	*find_link(t_link_list *l, t_room *r)
{
	while (l)
	{
		if (l->data->dst == r)
			return (l->data);
		l = l->next;
	}
	return (NULL);
}

t_link_list	*del_link(t_link_list *l, t_room *r)
{
	t_link_list *prev;
	t_link_list *first;

	prev = NULL;
	first = l;
	if (!l || !l->next)
		return NULL;
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

t_path	*p_push_begin(t_room *r, t_path *p)
{
	t_path *new;

	if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
		exit (1);
	new->r = r;
	new->next = p;
	return (new);
}

t_path	*assemble_path(t_room *end, t_room *start)
{
	static int i;
	t_path	*p = NULL;
	int	len = 0;

	while (end != start)
	{
		p = p_push_begin(end, p);
		end = end->parent;
		len++;
	}
	p = p_push_begin(start, p);
	i++;
	return (p);
}

void	q_add_room(t_rooms **q, t_link *l)
{
	t_rooms			*new;
	static t_rooms	*last;

	if (!(new = (t_rooms *)ft_memalloc(sizeof(t_rooms))))
		exit (1);
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
	t_room *ret;
	t_rooms *tmp;

	if (!*q)
		return NULL;
	ret = (*q)->r;
	tmp = *q;
	*q = (*q)->next;
	free(tmp);
	return ret;
}

void	recursive_add(t_room *w, t_room *p, t_room *start, t_rooms **q)
{
	if (w == start)
		return ;
	w->parent = p;
	recursive_add(w->pred, w, start, q);
	q_add_links(q, w->links, w, start);
}

t_path  *bfs(t_graph *g)
{
	t_room	*w = g->start;
	t_rooms *q = NULL;

	q_add_links(&q, w->links, w, g->start);
	if (!(w = q_get(&q)))
		return NULL;
	while (w != g->end)
	{
		if (w->pred)
			recursive_add(w->pred, w, g->start, &q);
		else
			q_add_links(&q, w->links, w, g->start);
		if (!(w = q_get(&q)))
			return NULL;
	}
	return (assemble_path(w, g->start));
}

void	print_path(t_path *p)
{
	while (p->next)
	{
		printf("%s - ", p->r->name);
		p = p->next;
	}
	printf("%s", p->r->name);
	printf("\n");
}

int 		p_len(t_path *p)
{
	int len = 0;

	while (p)
	{
		p = p->next;
		len++;
	}
	return (len);
}

t_paths_list *plist_push_back(t_paths_list *p_list, t_path *p)
{
	t_paths_list *first;
	t_paths_list *new;

	first = p_list;
	if (!(new = (t_paths_list *)ft_memalloc(sizeof(t_paths_list))))
		exit (1);
	new->path = p;
	if (!first)
		return (new);
	while (p_list->next)
		p_list = p_list->next;
	p_list->next = new;
	return (first);
}

void	restore(t_llist *rooms)
{
	while (rooms)
	{
		rooms->data->parent = NULL;
		rooms = rooms->next;
	}
}

void	modify_graph(t_path *p)
{
	static int i;

	while (p->next)
	{
		p->r->links = del_link(p->r->links, p->next->r);
		p->r->pred = p->r->parent;
		p->r->succ = p->next->r;
		p->r->path_num = i;
		p = p->next;
	}
	i++;
}

t_path *get_col_start(t_path *p)
{
	while (p)
	{
		if (p->r->pred)
			break ;
		p = p->next;
	}
	return (p);
}

t_path *get_col_end(t_path *col_start)
{
	while (col_start->next->r->pred)
		col_start = col_start->next;
	return (col_start);
}

t_path  *get_zero_path(t_paths_list *list, int path_num)
{
	while (path_num--)
		list = list->next;
	return (list->path);
}

t_path	*get_zero_start(t_path *p0, t_path *end1)
{
	while (p0->r != end1->r)
		p0 = p0->next;
	return (p0);
}

t_path	*get_zero_end(t_path *p0, t_path *start1)
{
	while (p0->r != start1->r)
		p0 = p0->next;
	return (p0);
}

int find_pn(t_paths_list *l, char *name)
{
	int i = 0;

	while (l)
	{
		t_path *p = l->path;
		while (p)
		{
			if (!strcmp(name, p->r->name))
				return i;
			p = p->next;
		}
		i++;
		l = l->next;
	}
	return (-1);
}

void	restore_col(t_path *st, t_path *end)
{
	st = st->next;
	while (st != end)
	{
		st->r->pred = NULL;
		st = st->next;
	}
}

int	collision_handle(t_paths_list *list, t_path *p1)
{
	t_path *p0;
	t_path *col_start1 = p1;
	t_path *col_start0;
	t_path *col_end1;
	t_path *col_end0;

	if ((col_start1 = get_col_start(p1->next))) {
		p0 = get_zero_path(list, col_start1->r->path_num);
		col_end1 = get_col_end(col_start1);
		//printf("%d\n", find_pn(list, col_end1->r->name));
		col_start0 = get_zero_start(p0, col_end1);
		col_end0 = get_zero_end(col_start0, col_start1);
		restore_col(col_start0, col_end0);
		col_start0->next = col_end1->next;
		col_start1->next = col_end0->next;
		return (collision_handle(list, col_end1));
	}
	return (0);
}

void	check(t_paths_list *l, t_path *p) {

	t_path *pp = p->next;
	while (pp)
	{
		if (p == pp)
			printf("Collision detected\n");
		pp = pp->next;
	}
	l = l->next;
	while (l)
	{
		pp = l->path;
		while (pp)
		{
			if (p == pp)
				printf("Collision detected\n");
			pp = pp->next;
		}
		l = l->next;
	}
}

void	cd(t_paths_list *l)
{
	while (l) {
		t_path *p = l->path;
		while (p)
		{
			check(l, p);
			p = p->next;
		}
		l = l->next;
	}
	printf("finish\n");
}

void	swap(t_paths_list *l1, t_paths_list *l2)
{
	t_paths_list tmp;

	tmp.len = l1->len;
	tmp.path = l1->path;
	l1->len = l2->len;
	l1->path = l2->path;
	l2->len = tmp.len;
	l2->path = tmp.path;
}

void	get_len(t_paths_list *l)
{
	while (l)
	{
		l->len = p_len(l->path);
		l = l->next;
	}
}

void	bubble_sort(t_paths_list *l)
{
	int sorted;
	t_paths_list *first = l;

	get_len(l);
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

void print_paths(t_paths_list *p_list, int max_path)
{
	int i = 0;
	while (p_list)
	{
		print_path(p_list->path);			//вывод путей в терминал
		p_list = p_list->next;
		i++;
	}
	printf("count of paths: %d\nmaximum paths: %d", i, max_path);
}

t_paths_list  *suurbale(t_graph *graph)
{
	int max_path;
	t_path *p;
	t_paths_list *p_list;

	max_path = get_max_path(graph->start, graph->end);
	p_list = NULL;
	int c = 0;
	while (c <= max_path)
	{
		c++;
		if (!(p = bfs(graph)))			//поиск в ширину (т.к. граф неориентированный, Дийкстра не нужен)
			break ;
		collision_handle(p_list, p);	//разрешение коллизий
		modify_graph(p);				// удаление ребер, добавление информации о пути в структуры комнат
		p_list = plist_push_back(p_list, p); // добавление пути в список путей
//		if (check_steps(p_list, graph->ants))
//			break ;
		restore(graph->rooms);				// обнуление поля parent
	}
	bubble_sort(p_list);
	//cd(p_list);								//проверка наличия коллизий
	//printf("ants: %d\n", graph->ants);
	print_paths(p_list, max_path);
	return (p_list);
}
