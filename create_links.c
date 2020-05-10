/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 14:36:03 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/07 14:36:11 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		ft_exit("Error <Room for link does not exist>");
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
		{
			link_rooms = start;
			return (0);
		}
		link_rooms = link_rooms->next;
	}
	link_rooms = start;
	return (1);
}

void	binary_search_links(char *r1, char *r2, t_flags *flags)
{
	int			mid;
	t_link_list	*add;
	t_link		*add_link;

	mid = (flags->i + flags->count_of_room) / 2;
	if (ft_strcmp(r1, flags->array_of_rooms_ptr[mid]->name) > 0)
		flags->i = mid + 1;
	else if (ft_strcmp(r1, flags->array_of_rooms_ptr[mid]->name) < 0)
		flags->count_of_room = mid - 1;
	else
	{
		flags->fl = 1;
		if (ft_not_link(flags->array_of_rooms_ptr[mid]->links, r2))
		{
			if (!(add = (t_link_list *)malloc(sizeof(t_link_list))))
				ft_exit("Error <malloc>");
			if (!(add_link = (t_link *)malloc(sizeof(t_link))))
				ft_exit("Error <malloc>");
			find_paste_link(flags->first, r2, add_link);
			add->data = add_link;
			add->next = flags->array_of_rooms_ptr[mid]->links;
			flags->array_of_rooms_ptr[mid]->links = add;
		}
		flags->i = flags->count_of_room + 1;
	}
}

void	create_links_binary(t_graph *graph, char *name_coor, t_flags *flags)
{
	char		**split_link;
	int			last;

	flags->fl = 0;
	flags->i = 0;
	last = flags->count_of_room - 1;
	flags->count_of_room = last;
	flags->first = graph->rooms;
	split_link = ft_strsplit(name_coor, '-');
	while (flags->i <= flags->count_of_room)
		binary_search_links(split_link[0], split_link[1], flags);
	flags->i = 0;
	flags->count_of_room = last;
	while (flags->i <= flags->count_of_room)
	{
		binary_search_links(split_link[1], split_link[0], flags);
	}
	flags->count_of_room = last + 1;
	if (flags->fl == 0)
		ft_exit("Error <Room for link does not exist>");
	graph->rooms = flags->first;
	free(split_link[0]);
	free(split_link[1]);
	free(split_link);
}
