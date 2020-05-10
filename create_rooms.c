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

void	add_to_graph_rooms(char **split_name_coor, t_graph *graph)
{
	t_llist	*add;
	t_room	*add_room;

	if (!(add = (t_llist *)ft_memalloc(sizeof(t_llist))))
		ft_exit("Error <malloc>");
	if (!(add_room = (t_room *)ft_memalloc(sizeof(t_room))))
		ft_exit("Error <malloc>");
	add_room->name = ft_strnew(ft_strlen(split_name_coor[0]));
	ft_strcpy(add_room->name, split_name_coor[0]);
	add_room->x = ft_atoi(split_name_coor[1]);
	add_room->y = ft_atoi(split_name_coor[2]);
	free(split_name_coor[0]);
	free(split_name_coor[1]);
	free(split_name_coor[2]);
	free(split_name_coor);
	add->data = add_room;
	add->next = graph->rooms;
	graph->rooms = add;
}

void	create_graph_rooms(char **split_name_coor, t_graph *graph)
{
	t_room	*add_room;

	if (!(graph->rooms = (t_llist *)ft_memalloc(sizeof(t_llist))))
		ft_exit("Error <malloc>");
	if (!(add_room = (t_room *)ft_memalloc(sizeof(t_room))))
		ft_exit("Error <malloc>");
	add_room->name = ft_strnew(ft_strlen(split_name_coor[0]));
	ft_strcpy(add_room->name, split_name_coor[0]);
	add_room->x = ft_atoi(split_name_coor[1]);
	add_room->y = ft_atoi(split_name_coor[2]);
	free(split_name_coor[0]);
	free(split_name_coor[1]);
	free(split_name_coor[2]);
	free(split_name_coor);
	graph->rooms->data = add_room;
	graph->rooms->next = NULL;
}

void	create_rooms(t_graph *graph, char *name_coor)
{
	char	**split_name_coor;

	split_name_coor = ft_strsplit(name_coor, ' ');
	if (graph->rooms == NULL)
		create_graph_rooms(split_name_coor, graph);
	else
		add_to_graph_rooms(split_name_coor, graph);
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
	graph->start->name = ft_strnew(ft_strlen(split_name_coor[0]));
	ft_strcpy(graph->start->name, split_name_coor[0]);
	graph->start->x = ft_atoi(split_name_coor[1]);
	graph->start->y = ft_atoi(split_name_coor[2]);
	free(split_name_coor[0]);
	free(split_name_coor[1]);
	free(split_name_coor[2]);
	free(split_name_coor);
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
	graph->end->name = ft_strnew(ft_strlen(split_name_coor[0]));
	ft_strcpy(graph->end->name, split_name_coor[0]);
	graph->end->x = ft_atoi(split_name_coor[1]);
	graph->end->y = ft_atoi(split_name_coor[2]);
	free(split_name_coor[0]);
	free(split_name_coor[1]);
	free(split_name_coor[2]);
	free(split_name_coor);
	tmp->data = graph->end;
	tmp->next = graph->rooms;
	graph->rooms = tmp;
}
