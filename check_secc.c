/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_secc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 14:35:51 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/07 14:35:59 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_con(char **split_buff, t_graph *graph, t_flags *fl, int *i)
{
	while (split_buff[*i])
	{
		if (is_comment(split_buff[*i]))
			(*i)++;
		else if (is_links(split_buff[*i]))
		{
			create_links_binary(graph, split_buff[(*i)++], fl);
			fl->con = 1;
			fl->count_of_edges++;
		}
		else
			ft_exit("Error <don't have correct link>");
	}
}

void	check_coor(char **split_buff, t_graph *graph, t_flags *fl, int *i)
{
	create_rooms(graph, split_buff[*i]);
	(*i)++;
	fl->count_of_room++;
}

void	check_end(char **split_buff, t_graph *graph, t_flags *fl, int *i)
{
	(*i)++;
	while (is_comment(split_buff[*i]))
		(*i)++;
	if (is_coordinate(split_buff[*i]))
	{
		create_end_room(graph, split_buff[(*i)++]);
		fl->end = 1;
		fl->count_of_room++;
	}
	else
		ft_exit("Error <don't have coor for end>");
}

void	check_start(char **split_buff, t_graph *graph, t_flags *fl, int *i)
{
	(*i)++;
	while (is_comment(split_buff[*i]))
		(*i)++;
	if (is_coordinate(split_buff[*i]))
	{
		create_start_room(graph, split_buff[(*i)++]);
		fl->start = 1;
		fl->count_of_room++;
	}
	else
		ft_exit("Error <don't have coor for start>");
}

void	check_sec(char **split_buff, t_graph *graph, t_flags *fl, int *i)
{
	while (split_buff[*i])
	{
		if (is_comment(split_buff[*i]))
			(*i)++;
		else if (is_start(split_buff[*i]) && fl->start == 0)
			check_start(split_buff, graph, fl, i);
		else if (is_end(split_buff[*i]) && fl->end == 0)
			check_end(split_buff, graph, fl, i);
		else if (is_coordinate(split_buff[*i]))
			check_coor(split_buff, graph, fl, i);
		else if (is_links(split_buff[*i]) && fl->start == 1 && \
				fl->end == 1 && fl->ant == 1)
		{
			create_array_of_rooms_ptr(fl, graph);
			ft_quick_sort_coor(fl->array_of_rooms_ptr, 0, \
					fl->count_of_room - 1);
			check_double_coor(fl->array_of_rooms_ptr, fl->count_of_room);
			ft_quick_sort(fl->array_of_rooms_ptr, 0, fl->count_of_room - 1);
			check_double_name(fl->array_of_rooms_ptr, fl->count_of_room);
			break ;
		}
		else
			ft_exit("Error: not valid info after coor!");
	}
}
