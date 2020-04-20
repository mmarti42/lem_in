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
#include "string.h"

void	ft_exit(const char *const str)
{
    ft_putendl(str);
    exit(1);
}

int		atoi_for_lemin(const char *str)
{
	int				i;
	long			nbr;
	int				negative;
	int				x;

	i = 0;
	nbr = 0;
	negative = 1;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == '\v') ||
		   (str[i] == ' ') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	(str[i] == '-') ? negative *= -1 : negative;
	if (str[i] == '-' || str[i] == '+')
		i++;
	x = 0;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		nbr = (nbr * 10) + str[i++] - 48;
		if (nbr != 0)
			x++;
	}
	nbr = nbr * negative;
	if (nbr > 2147483647 || nbr < -2147483648 || x > 9 || nbr < 0)
	{
		ft_putstr("Error\n");
		exit(1);
	}
	return ((int)nbr);
}

int		is_str_digits(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i++])))
            return (0);
	}
	return (1);
}

void	validate_com(char **split_com)
{
	//проверить связи с комнат
	//1)Cуществуют ли такие комнаты
	//2)Нет ли дублей
}

int		is_links(char *str)
{
	int		cntwd;
	char	**split_com;

	cntwd = ft_cntword(str, '-');
	if (cntwd != 2)
		return (0);
	split_com = ft_strsplit(str, '-');
	return (1);
}

int		is_start(char *str)
{
    return (!(ft_strcmp(str, "##start")) ? 1 : 0);
}

int		is_end(char *str)
{
    return (!(ft_strcmp(str, "##end")) ? 1 : 0);
}

int		is_comment(char *str)
{
    if (*str == '#' && !is_start(str) && !is_end(str))
        return (1);
    else
        return (0);
}

void	validate_coor(char **split_coor)
{
	int		i;

	i = 1;
	while (split_coor[i])
	{
		atoi_for_lemin(split_coor[i]);
		if (is_str_digits(split_coor[i]))
			i++;
		else
			ft_exit("Error <name_room && coor>");
	}
}

int		is_coordinate(char *str)
{
	int		cntwd;
	char	**split_coor;

	cntwd = ft_cntword(str, ' ');
	if (cntwd != 3 || *str == 'L' || *str == '-')
		return (0);
	split_coor = ft_strsplit(str, ' ');
	validate_coor(split_coor);
	return (1);
}

int		is_count_ants(char *str, t_flags *fl)
{
    if (!is_str_digits(str))
	   	return (0);
	fl->count_of_ants = atoi_for_lemin(str);
    return (1);
}

t_graph	*validate_rows(char **split_buff)
{
	int		i;
	t_flags fl;
	t_llist	*list;
	t_graph *graph;

	if (!(graph = (t_graph*)ft_memalloc(sizeof(t_graph))))
		exit (1);
	fl.array_of_rooms_ptr = NULL;
	fl.count_of_path = 0;
	fl.count_of_ants = 0;
	fl.count_of_room = 0;
	fl.count_of_edges = 0;
	fl.ant = 0;
	fl.start = 0;
	fl.end = 0;
	fl.con = 0;
	list = NULL;
	i = 0;
	while (split_buff[i])
	{
	    //1.Необходимо найти муравьев, если нашли что-то кроме комментариев и положительного инта Error
        while (is_comment(split_buff[i]))
            i++;
        if (fl.ant == 0)
        {
			if (is_count_ants(split_buff[i], &fl))
			{
				fl.count_of_ants = ft_atoi(split_buff[i]);
				if (fl.count_of_ants == 0)
					ft_exit("Error <don't have ants>");
				fl.ant = 1;
				i++;
			}
			else
				ft_exit("Error <don't have count of ants>");
        }
		// 2.Далее у нас могут идти только комааетарии, ##start || ##end название комнаты и координаты (<name room> <int x> <int y>)
		//   Исключить дубли названий и дубли координат, записать все это куда-то чтобы потом проверить их наличие
		//   скорее всего с помощью хэш-таблиц
        else if (fl.ant == 1 && fl.start == 0 && fl.end == 0 && fl.con == 0)
		{
        	while (split_buff[i])
			{
        		if (is_comment(split_buff[i]))
        			i++;
				else if (is_start(split_buff[i]) && fl.start == 0)
				{
					i++;
					while (is_comment(split_buff[i]))
						i++;
					if (is_coordinate(split_buff[i]))
					{
//						check_double_room_coor(graph, split_buff[i]);
						//create_rooms(graph, split_buff[i]);
						create_start_room(graph, split_buff[i++]);
						fl.start = 1;
						fl.count_of_room++;
					}
					else
						ft_exit("Error <don't have coor for start>");
				}
				else if (is_end(split_buff[i]) && fl.end == 0)
				{
					i++;
					while (is_comment(split_buff[i]))
						i++;
					if (is_coordinate(split_buff[i]))
					{
//						check_double_room_coor(graph, split_buff[i]);
						//create_rooms(graph, split_buff[i]);
						create_end_room(graph, split_buff[i++]);
						fl.end = 1;
						fl.count_of_room++;
					}
					else
						ft_exit("Error <don't have coor for end>");
				}
				else if (is_coordinate(split_buff[i]))
				{
//					check_double_room_coor(graph, split_buff[i]);
					create_rooms(graph, split_buff[i]);
					i++;
					fl.count_of_room++;
				}
				else if (is_links(split_buff[i]) && fl.start == 1 && fl.end == 1 && fl.ant == 1)
				{
					create_array_of_rooms_ptr(&fl, graph);
					ft_quick_sort_coor(fl.array_of_rooms_ptr, 0, fl.count_of_room - 1);
					check_double_coor(fl.array_of_rooms_ptr, fl.count_of_room);
					ft_quick_sort(fl.array_of_rooms_ptr, 0, fl.count_of_room - 1);
					check_double_name(fl.array_of_rooms_ptr, fl.count_of_room);
					break ;
				}
				else
					ft_exit("Error: not valid info after coor!");
			}
		}
        //3.И последнее, все теже комментарии (они могут быть где угодно), и
		else if (fl.ant == 1 && fl.start == 1 && fl.end == 1)
		{
			while (split_buff[i])
			{
				if (is_comment(split_buff[i]))
					i++;
				else if (is_links(split_buff[i]))
				{
//					create_links(graph, split_buff[i++]);
					create_links_binary(graph, split_buff[i++], &fl);
					fl.con = 1;
					fl.count_of_edges++;
				}
				else
					ft_exit("Error <don't have correct link>");
			}
		}
	}
	if (!(fl.ant == 1 && fl.start == 1 && fl.end == 1 && fl.con == 1))
		ft_exit("Error_validation");
	return (graph);
}

t_graph	*validation(char *buff)
{
	char **split_buff;
	t_graph *graph;

	split_buff = ft_strsplit(buff, '\n');
	graph = validate_rows(split_buff);
	return (graph);
}

char	*create_validation_buff(void)
{
	char	*line;
	int		fd;

	fd = open("../checker/maps/valid/big_sup/map_big_sup_10" , O_RDONLY);
//	fd = open("../checker/maps/valid/map_slack", O_RDONLY);
	//fd = 0;
//	fd = open("../42_lem-in_tools/maps/valid/big_sup/map_big_sup_10", O_RDONLY);
//	fd = open("../42_lem-in_tools/maps/valid/big_sup/map_big_sup_1", O_RDONLY);
	if (fd < 0)
		exit (1);
	while(get_next_line(fd, &line))
		;
	return (line);
}