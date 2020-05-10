/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 14:31:42 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/07 14:35:47 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		ft_exit("Error\n");
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

int		is_count_ants(char *str, t_flags *fl)
{
	if (!is_str_digits(str))
		return (0);
	fl->count_of_ants = atoi_for_lemin(str);
	return (1);
}
