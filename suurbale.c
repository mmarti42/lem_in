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

// t_set	*set_find(t_set *root, t_room *r)
// {
// 	t_set *ret;
// 	int comp;

// 	ret = root;
// 	while ((comp = ft_strcmp(ret->room->name, r->name)))
// 	{
// 		if (comp > 0)
// 			ret = ret->left;
// 		else
// 			ret = ret->right;
// 	}
// 	return (ret);
// }

// t_set	*set_add_find(t_set *root, t_room *r)
// {
// 	t_set	*ret;
// 	int		comp;

// 	ret = root;
// 	while ((comp = ft_strcmp(ret->room->name, r->name)))
// 	{
// 		if (comp > 0)
// 		{
// 			if (!ret->left)
// 				return (ret);
// 			ret = ret->left;
// 		}
// 		else
// 		{
// 			if (!ret->right)
// 				return (ret);
// 			ret = ret->right;
// 		}
// 	}
// 	return (ret);
// }

// t_set	*set_new_node(t_room *r)
// {
// 	t_set *new;

// 	if (!(new = ft_memalloc(sizeof(t_set))))
// 		exit (1);
// 	new->room = r;
// 	return (new);
// }

// void	insert_node(t_set *parent, t_set *ins, int comp)
// {
// 	if (comp > 0)
// 		parent->left = ins;
// 	else
// 		parent->right = ins;
// }

// t_set	*grandparent(t_set *node)
// {
// 	if (node->parent)
// 		return (node->parent->parent);
// 	return (NULL);
// }

// t_set	*uncle(t_set *node)
// {
// 	t_set *gp;

// 	if (!(gp = grandparent(node)))
// 		return (NULL);
// 	if (node->parent == gp->left)
// 		return (gp->right);
// 	else
// 		return (gp->left);
// }

// void	rotate_left(t_set *n)
// {
//     t_set *pivot = n->right;
	
//     pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
//     if (n->parent != NULL) 
// 	{
//         if (n->parent->left==n)
//             n->parent->left = pivot;
//         else
//             n->parent->right = pivot;
//     }		
//     n->right = pivot->left;
//     if (pivot->left != NULL)
//         pivot->left->parent = n;
//     n->parent = pivot;
//     pivot->left = n;
// }

// void	rotate_right(t_set *n)
// {
//     t_set *pivot = n->left;
	
// 	pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
// 	if (n->parent != NULL) 
// 	{
// 		if (n->parent->left==n)
// 			n->parent->left = pivot;
// 		else
// 			n->parent->right = pivot;
// 	}
// 	n->left = pivot->right;
// 	if (pivot->right != NULL)
// 		pivot->right->parent = n;
// 	n->parent = pivot;
// 	pivot->right = n;
// }

// void	case5(t_set *n)
// {
// 	t_set *g = grandparent(n);

// 	n->parent->color = BLACK;
// 	g->color = RED;
// 	if ((n == n->parent->left) && (n->parent == g->left))
// 		rotate_right(g);
// 	else
// 		rotate_left(g);
// }

// void	case4(t_set *n)
// {
// 	t_set *g = grandparent(n);

// 	if ((n == n->parent->right) && (n->parent == g->left))
// 		rotate_left(n->parent);
// 	else if ((n == n->parent->left) && (n->parent == g->right))
// 	{
// 		rotate_right(n->parent);
// 		n = n->right;
// 	}
// 	case5(n);
// }

// void	case3(t_set *n)
// {
// 	t_set *u;
// 	t_set *gp;

// 	if ((u = uncle(n)) && u->color == RED)
// 	{
// 		n->parent->color = BLACK;
// 		u->color = BLACK;
// 		gp = grandparent(n);
// 		gp->color = RED;
// 		return (case1(gp));
// 	}
// 	else
// 		return (case4(n));
// }

// void	case2(t_set *n)
// {
// 	if (n->parent->color == BLACK)
// 		return ;
// 	else
// 		return (case3(n));
// }

// void	case1(t_set *n)
// {
// 	if (!n->parent)
// 		n->color = BLACK;
// 	else
// 		return (case2(n));
// }

// void	set_insert(t_set *root, t_room *r)
// {
// 	t_set	*ins;
// 	t_set	*parent;
// 	int		comp;

// 	if (!(comp = ft_strcmp(r->name, parent = set_add_find(root, r))))
// 		return ;
// 	ins = set_new_node(r);
// 	ins->parent = parent;
// 	insert_node(parent, ins, comp);
// 	return (case1(r));
// }

// int		is_left(t_set *node)
// {
// 	if (!node->parent || node->parent->left != node)
// 		return (0);
// 	return (1);
// }

// void	del_in_parent(t_set *node)
// {
// 	if (is_left(node))
// 		node->parent->left = NULL;
// 	else
// 		node->parent->right = NULL;
// }

// void	replace_in_parent(t_set *node)
// {
// 	t_set *tmp;

// 	if (!(tmp = node->left))
// 		tmp = node->right;
// 	if (is_left(node))
// 		node->parent->left = tmp;
// 	else
// 		node->parent->right = tmp;
// }

// void	delete_node(t_set *node)
// {
// 	if (!node->right && !node->left)
// 		del_in_parent(node);
// 	else if ((node->right && !node->left) || (!node->right && node->left))
// 		replace_in_parent(node);
// 	else
			
// }

// void	set_delete(t_set *root, t_room *r)
// {
// 	t_set *node;

// 	if (!(node = set_find(root, r)))
// 		return ;
// 	delete_node(node);
// }

// t_set	*set_init(t_room *r)
// {
// 	t_set	*root;

// 	if (!(root = (t_set *)ft_memalloc(sizeof(t_set))))
// 		exit (1);
// 	root->room = r;
// 	root->color = BLACK;
// 	return (root);
// }

//t_rooms	*set_find(t_rooms *s, t_room *r)
//{
//	while (s)
//	{
//		if (!ft_strcmp(s->r->name, r->name))
//			return (s);
//		s = s->next;
//	}
//	return (NULL);
//}
//
//void    set_add(t_rooms **s, t_room *r, int distance, t_room *p)
//{
//	t_rooms *new;
//	t_rooms *tmp;
//
//	if (!(tmp = set_find(*s, r)))
//	{
//		if (!(new = (t_rooms *)malloc(sizeof(t_rooms))))
//			exit (1);
//		r->distance = distance;
//		new->r = r;
//		new->next = *s;
//		*s = new;
//		r->parent = p;
//	}
//	else if (tmp->r->distance > distance) {
//        tmp->r->distance = distance;
//        r->parent = p;
//    }
//}

//t_rooms	*set_init(t_room *r)
//{
//	t_rooms *f;
//
//	if (!(f = (t_rooms *)malloc(sizeof(t_rooms))))
//		exit (1);
//	f->next = NULL;
//	f->r = r;
//	return (f);
//}

t_rooms	*set_min(t_rooms *s)
{
	int		distance;
	t_rooms	*ret;

	ret = NULL;
	distance = INF;
	while (s)
	{
		if (s->r->distance < distance)
		{
			ret = s;
			distance = s->r->distance;
		}
		s = s->next;
	}
	return (ret);
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

//void	step(t_rooms **s, t_room *w)
//{
//	t_link_list *l;
//
//	l = w->links;
//	while (l)
//	{
//	    if (w->parent != l->data->dst)
//	        set_add(s, l->data->dst, l->data->weight + w->distance, w);
//		l = l->next;
//	}
//}

//void	split_vertex(t_room *r)
//{

//}

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

//t_room *find_by_name(t_llist *r, char *name)
//{
//	while (r)
//	{
//		if (!strcmp(r->data->name, name))
//			return (r->data);
//		r = r->next;
//	}
//	return (0);
//}
//
//void    free_set(t_rooms **s)
//{
//    *s = NULL;
//}

//t_rooms	*q_init(t_room *start)
//{
//	t_rooms *new;
//
//	if (!(new = (t_rooms *)malloc(sizeof(t_rooms))))
//		exit (1);
//	new->r = start;
//	new->next = NULL;
//	return (new);
//}

//void	q_add_room(t_rooms **q, t_link *l, t_room *parent)
//{
//	t_rooms			*new;
//	t_rooms			*tmp;
//
//	if (!(new = (t_rooms *)malloc(sizeof(t_rooms))))
//		exit (1);
//	new->w = l->weight;
//	new->r = l->dst;
//	new->r->parent = parent;
//	new->next = NULL;
//	if (!*q)
//		*q = new;
//	else {
//		tmp = *q;
//		while (tmp->next && tmp->w <= l->weight)
//			tmp = tmp->next;
//		new->next = tmp->next;
//		tmp->next = new;
//	}
//}

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

// void	print_links(t_room *r)
// {

// }

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
		printf("%d\n", find_pn(list, col_end1->r->name));
		col_start0 = get_zero_start(p0, col_end1);
		col_end0 = get_zero_end(col_start0, col_start1);
		restore_col(col_start0, col_end0);
		//restore_col(col_start1, col_end1);
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
			printf("COOLLLL\n");
		pp = pp->next;
	}
	l = l->next;
	while (l)
	{
		pp = l->path;
		while (pp)
		{
			if (p == pp)
				printf("COOLLLL\n");
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

void    suurbale(t_graph *graph)
{
	int max_path;
	t_path *p;
	t_paths_list *p_list;

	max_path = get_max_path(graph->start, graph->end);
	p_list = NULL;
	while (max_path--)
	{
		if (!(p = bfs(graph)))			//поиск в ширину (т.к. граф неориентированный, Дийкстра не нужен)
			break ;
		collision_handle(p_list, p);	//разрешение коллизий
		modify_graph(p);				// удаление ребер, добавление информации о пути в структуры комнат
		p_list = plist_push_back(p_list, p); // добавление пути в список путей
		restore(graph->rooms);				// обнуление поля parent
	}
	cd(p_list);								//проверка наличия коллизий
//	while (p_list)
//	{
//		print_path(p_list->path);			//вывод путей в терминал
//		p_list = p_list->next;
//		i++;
//	}
}
