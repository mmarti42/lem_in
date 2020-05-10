/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dbl_create_arr_rooms.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 14:33:48 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/07 14:35:48 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_array_of_rooms_ptr(t_flags *fl, t_graph *graph)
{
	t_llist	*start;
	int		i;

	i = 0;
	start = graph->rooms;
	if (!(fl->array_of_rooms_ptr = \
	(t_room **)ft_memalloc(sizeof(t_room *) * fl->count_of_room + 1)))
		ft_exit("Error <malloc>");
	graph->value_for_free = fl->array_of_rooms_ptr;
	while (graph->rooms)
	{
		fl->array_of_rooms_ptr[i++] = graph->rooms->data;
		graph->rooms = graph->rooms->next;
	}
	graph->rooms = start;
}

void	check_double_name(t_room **array_of_rooms_ptr, int count)
{
	int i;

	i = -1;
	while (++i < count - 1)
	{
		if (!(ft_strcmp(array_of_rooms_ptr[i]->name, \
				array_of_rooms_ptr[i + 1]->name)))
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
