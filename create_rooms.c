/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 10:08:35 by kdeloise          #+#    #+#             */
/*   Updated: 2020/03/04 10:08:48 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//int		check_sort_stack(t_fl *fl)
//{
//	t_stack	*start;
//
//	start = fl->a;
//	while (fl->a && fl->a->next)
//	{
//		if (fl->a->data > fl->a->next->data)
//		{
//			fl->a = start;
//			return (0);
//		}
//		fl->a = fl->a->next;
//	}
//	fl->a = start;
//	if (fl->count_a == 0 && fl->count_b == 0)
//		exit(1);
//	return (1);
//}

int		ft_partition_coor(t_room **array, int start, int end)
{
	t_room *pivot;
	int i;
	t_room *temp;
	int j;

	pivot = array[end];
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (array[j]->x < pivot->x)
		{
			i++;
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
		else if (array[j]->x == pivot->x)
		{
			if (array[j]->y <= pivot->y)
			{
				i++;
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
		j++;
	}
	temp = array[i + 1];
	array[i + 1] = array[end];
	array[end] = temp;
	return (i + 1);
}

void	ft_quick_sort_coor(t_room **array, int start, int end)
{
	int q;

	if (start < end)
	{
		q = ft_partition_coor(array, start, end);
		ft_quick_sort_coor(array, start, q - 1);
		ft_quick_sort_coor(array, q + 1, end);
	}
}

int		ft_partition(t_room **array, int start, int end)
{
	t_room *pivot;
	int i;
	t_room *temp;
	int j;

	pivot = array[end];
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (ft_strcmp(array[j]->name, pivot->name) <= 0)
		{
			i++;
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
		j++;
	}
	temp = array[i + 1];
	array[i + 1] = array[end];
	array[end] = temp;
	return (i + 1);
}

void	ft_quick_sort(t_room **array, int start, int end)
{
	int q;

	if (start < end)
	{
		q = ft_partition(array, start, end);
		ft_quick_sort(array, start, q - 1);
		ft_quick_sort(array, q + 1, end);
	}
}

void	create_array_of_rooms_ptr(t_flags *fl, t_graph *graph)
{
	t_llist *start;
	int i = 0;

	start = graph->rooms;
	if (!(fl->array_of_rooms_ptr = (t_room **)ft_memalloc(sizeof(t_room *) * fl->count_of_room + 1)))
		ft_exit("Error <malloc>");
	while (graph->rooms)
	{
		fl->array_of_rooms_ptr[i++] = graph->rooms->data;
		graph->rooms = graph->rooms->next;
	}
	fl->array_of_rooms_ptr[i] = NULL;
	graph->rooms = start;
}

void	check_double_name(t_room **array_of_rooms_ptr, int count)
{
	int i;

	i = -1;
	while (++i < count - 1)
	{
		if (!(ft_strcmp(array_of_rooms_ptr[i]->name,array_of_rooms_ptr[i + 1]->name)))
			ft_exit("Error <double name_room>");
	}
}

void	check_double_coor(t_room **array_of_rooms_ptr, int count)
{
	int i;

	i = -1;
	while (++i < count - 1)
	{
		if (array_of_rooms_ptr[i]->x == array_of_rooms_ptr[i + 1]->x)
		{
			if (array_of_rooms_ptr[i]->y == array_of_rooms_ptr[i + 1]->y)
				ft_exit("Error <double coordinate>");
		}
	}
}

void	check_double_room_coor(t_graph *graph, char *name_coor)
{
	char	**split_name_coor;
	t_llist *start;

	split_name_coor = ft_strsplit(name_coor, ' ');
	if (graph)
	{
		start = graph->rooms;
		while (graph->rooms)
		{
			if (!(ft_strcmp(graph->rooms->data->name, split_name_coor[0])))
				ft_exit("Error <duplicate name_room>");
			if (graph->rooms->data->x == ft_atoi(split_name_coor[1]) && graph->rooms->data->y == ft_atoi(split_name_coor[2]))
				ft_exit("Error <duplicate coordinate>");
			graph->rooms = graph->rooms->next;
		}
		graph->rooms = start;
	}
}

void	find_paste_link(t_llist *start, char *name_link, t_link *add_link)
{
	t_llist		*new_start;
	int			fl;

	fl = 0;
	new_start = start;
	while (start)
	{
		if (!(ft_strcmp(start->data->name, name_link)))
		{
			fl = 1;
			add_link->weight = 1;
			add_link->dst = start->data;
			start = new_start;
			break ;
		}
		start = start->next;
	}
	if (fl == 0)
		ft_exit("Error <Room does not exist>");
	start = new_start;
}

int		ft_not_link(t_link_list *link_rooms, char *name_room_for_link)
{
	t_link_list		*start;

	start = link_rooms;
	if (!link_rooms)
		return (1);
	while (link_rooms)
	{
		if (!(ft_strcmp(name_room_for_link, link_rooms->data->dst->name)))
			return (0);
		link_rooms = link_rooms->next;
	}
	link_rooms = start;
	return (1);
}

void	create_links_binary(t_graph *graph, char *name_coor, t_flags *flags)
{
	char		**split_link;
	t_link_list	*add;
	t_link		*add_link;
	t_llist		*start;
	int			fl;
	int			i;
	int			mid;
	int			end;

	fl = 0;
	i = 0;
	end = flags->count_of_room - 1;
	flags->count_of_room = end;
	start = graph->rooms;
	split_link = ft_strsplit(name_coor, '-');
	while (i <= flags->count_of_room)
	{
		mid = (i + flags->count_of_room) / 2;
		if (ft_strcmp(split_link[0], flags->array_of_rooms_ptr[mid]->name) > 0)
			i = mid + 1;
		else if (ft_strcmp(split_link[0], flags->array_of_rooms_ptr[mid]->name) < 0)
			flags->count_of_room = mid - 1;
		else
		{
			fl = 1;
			if (ft_not_link(flags->array_of_rooms_ptr[mid]->links, split_link[1]))
			{
				if (!(add = (t_link_list *)malloc(sizeof(t_link_list))))
					ft_exit("Error <malloc>");
				if (!(add_link = (t_link *)malloc(sizeof(t_link))))
					ft_exit("Error <malloc>");
				find_paste_link(start, split_link[1], add_link);
				add->data = add_link;
				add->next = flags->array_of_rooms_ptr[mid]->links;
				flags->array_of_rooms_ptr[mid]->links = add;
			}
			break ;
		}
	}
	i = 0;
	flags->count_of_room = end;
	while (i <= flags->count_of_room)
	{
		mid = (i + flags->count_of_room) / 2;
		if (ft_strcmp(split_link[1], flags->array_of_rooms_ptr[mid]->name) > 0)
			i = mid + 1;
		else if (ft_strcmp(split_link[1], flags->array_of_rooms_ptr[mid]->name) < 0)
			flags->count_of_room = mid - 1;
		else
		{
			fl = 1;
			if (ft_not_link(flags->array_of_rooms_ptr[mid]->links, split_link[0]))
			{
				if (!(add = (t_link_list *)malloc(sizeof(t_link_list))))
					ft_exit("Error <malloc>");
				if (!(add_link = (t_link *)malloc(sizeof(t_link))))
					ft_exit("Error <malloc>");
				find_paste_link(start, split_link[0], add_link);
				add->data = add_link;
				add->next = flags->array_of_rooms_ptr[mid]->links;
				flags->array_of_rooms_ptr[mid]->links = add;
			}
			break ;
		}
	}
	flags->count_of_room = end + 1;
	if (fl == 0)
		ft_exit("Error <Room does not exist>");
	graph->rooms = start;
}

void	create_links(t_graph *graph, char *name_coor)
{
	char		**split_link;
	t_link_list	*add;
	t_link		*add_link;
	t_llist		*start;
	int			fl;

	fl = 0;
	start = graph->rooms;
	split_link = ft_strsplit(name_coor, '-');
	while (graph->rooms)
	{
		if (!(ft_strcmp(split_link[0], graph->rooms->data->name)))
		{
			fl = 1;
			if (ft_not_link(graph->rooms->data->links, split_link[1]))
			{
				if (!(add = (t_link_list *)malloc(sizeof(t_link_list))))
					ft_exit("Error <malloc>");
				if (!(add_link = (t_link *)malloc(sizeof(t_link))))
					ft_exit("Error <malloc>");
				find_paste_link(start, split_link[1], add_link);
				add->data = add_link;
				add->next = graph->rooms->data->links;
				graph->rooms->data->links = add;
			}
		}
		else if (!(ft_strcmp(split_link[1], graph->rooms->data->name)))
		{
			fl = 1;
			if (ft_not_link(graph->rooms->data->links, split_link[0]))
			{
				if (!(add = (t_link_list *)malloc(sizeof(t_link_list))))
					ft_exit("Error <malloc>");
				if (!(add_link = (t_link *)malloc(sizeof(t_link))))
					ft_exit("Error <malloc>");
				find_paste_link(start, split_link[0], add_link);
				add->data = add_link;
				add->next = graph->rooms->data->links;
				graph->rooms->data->links = add;
			}
		}
		graph->rooms = graph->rooms->next;
	}
	if (fl == 0)
		ft_exit("Error <Room does not exist>");
	graph->rooms = start;
}

void	create_rooms(t_graph *graph, char *name_coor)
{
	char	**split_name_coor;
	t_llist	*add;
	t_room	*add_room;

	split_name_coor = ft_strsplit(name_coor, ' ');
	if (graph->rooms == NULL)
	{
		if (!(graph->rooms = (t_llist *)ft_memalloc(sizeof(t_llist))))
			ft_exit("Error <malloc>");
		if (!(add_room = (t_room *)ft_memalloc(sizeof(t_room))))
			ft_exit("Error <malloc>");
		add_room->name = split_name_coor[0];
		add_room->x = ft_atoi(split_name_coor[1]);
		add_room->y = ft_atoi(split_name_coor[2]);
		graph->rooms->data = add_room;
		graph->rooms->next = NULL;
	}
	else
	{
		if (!(add = (t_llist *)ft_memalloc(sizeof(t_llist))))
			ft_exit("Error <malloc>");
		if (!(add_room = (t_room *)ft_memalloc(sizeof(t_room))))
			ft_exit("Error <malloc>");
		add_room->name = split_name_coor[0];
		add_room->x = ft_atoi(split_name_coor[1]);
		add_room->y = ft_atoi(split_name_coor[2]);
		add->data = add_room;
		add->next = graph->rooms;
		graph->rooms = add;
	}
	add_room->distance = INF;
}

void	create_start_room(t_graph *graph, char *name_coor)
{
	char	**split_name_coor;
	t_llist	*tmp;
	split_name_coor = ft_strsplit(name_coor, ' ');
	if (!(graph->start = (t_room *)ft_memalloc(sizeof(t_room))))
		ft_exit("Error <malloc>");
	if (!(tmp = ft_memalloc(sizeof(t_llist))))
		ft_exit("Error <malloc>");
	graph->start->name = split_name_coor[0];
	graph->start->x = ft_atoi(split_name_coor[1]);
	graph->start->y = ft_atoi(split_name_coor[2]);
	tmp->data = graph->start;
	tmp->next = graph->rooms;
	graph->rooms = tmp;
}

void	create_end_room(t_graph *graph, char *name_coor)
{
	char	**split_name_coor;
	t_llist *tmp;

	split_name_coor = ft_strsplit(name_coor, ' ');
	if (!(graph->end = (t_room *)ft_memalloc(sizeof(t_room))))
		ft_exit("Error <malloc>");
	if (!(tmp = ft_memalloc(sizeof(t_llist))))
		ft_exit("Error <malloc>");
	graph->end->name = split_name_coor[0];
	graph->end->x = ft_atoi(split_name_coor[1]);
	graph->end->y = ft_atoi(split_name_coor[2]);
	tmp->data = graph->end;
	tmp->next = graph->rooms;
	graph->rooms = tmp;
	graph->end->distance = INF;
}