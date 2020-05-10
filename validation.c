/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_validation_buff.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:10:45 by kdeloise          #+#    #+#             */
/*   Updated: 2020/02/25 21:10:57 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	zero_struct_flags(t_flags *fl)
{
	fl->array_of_rooms_ptr = NULL;
	fl->count_of_path = 0;
	fl->count_of_ants = 0;
	fl->count_of_room = 0;
	fl->count_of_edges = 0;
	fl->ant = 0;
	fl->start = 0;
	fl->end = 0;
	fl->con = 0;
}

void	check_ants(char *ants, t_flags *fl, int *i)
{
	if (is_count_ants(ants, fl))
	{
		fl->count_of_ants = ft_atoi(ants);
		if (fl->count_of_ants == 0)
			ft_exit("Error <don't have ants>");
		fl->ant = 1;
		(*i)++;
	}
	else
		ft_exit("Error <don't have count of ants>");
}

t_graph	*validate_rows(char **split_buff)
{
	int		i;
	t_flags fl;
	t_graph *graph;

	if (!(graph = (t_graph*)ft_memalloc(sizeof(t_graph))))
		exit(1);
	zero_struct_flags(&fl);
	i = 0;
	while (split_buff[i])
	{
		while (is_comment(split_buff[i]))
			i++;
		if (fl.ant == 0)
			check_ants(split_buff[i], &fl, &i);
		else if (fl.ant == 1 && fl.start == 0 && fl.end == 0 && fl.con == 0)
			check_sec(split_buff, graph, &fl, &i);
		else if (fl.ant == 1 && fl.start == 1 && fl.end == 1)
			check_con(split_buff, graph, &fl, &i);
	}
	if (!(fl.ant == 1 && fl.start == 1 && fl.end == 1 && fl.con == 1))
		ft_exit("Error_validation");
	return (graph);
}

t_graph	*validation(char *buff)
{
	char	**split_buff;
	t_graph *graph;
	int		i;

	i = 0;
	split_buff = ft_strsplit(buff, '\n');
	graph = validate_rows(split_buff);
	graph->ants = (ft_atoi(*split_buff));
	while (split_buff[i])
		free(split_buff[i++]);
	free(split_buff);
	return (graph);
}

char	*create_validation_buff(void)
{
	char	*line;

	if (get_next_line(0, &line) < 0)
		return NULL;
	return (line);
}
