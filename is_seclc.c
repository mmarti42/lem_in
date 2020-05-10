/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_seclc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 14:36:58 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/07 14:37:24 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_links(char *str)
{
	int		cntwd;

	cntwd = ft_cntword(str, '-');
	if (cntwd != 2)
		return (0);
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

int		is_coordinate(char *str)
{
	int		cntwd;
	char	**split_coor;

	cntwd = ft_cntword(str, ' ');
	if (cntwd != 3 || *str == 'L' || *str == '-')
		return (0);
	split_coor = ft_strsplit(str, ' ');
	validate_coor(split_coor);
	free(split_coor[0]);
	free(split_coor[1]);
	free(split_coor[2]);
	free(split_coor);
	return (1);
}
