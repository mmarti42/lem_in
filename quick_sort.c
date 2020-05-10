/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 14:37:19 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/07 14:37:22 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_swap_for_sort(t_room **array, int i, int j)
{
	t_room *temp;

	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

int		ft_partition_coor(t_room **array, int start, int end)
{
	int		i;
	int		j;
	t_room	*pivot;

	pivot = array[end];
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (array[j]->x < pivot->x)
			ft_swap_for_sort(array, ++i, j);
		else if (array[j]->x == pivot->x)
		{
			if (array[j]->y <= pivot->y)
				ft_swap_for_sort(array, ++i, j);
		}
		j++;
	}
	ft_swap_for_sort(array, i + 1, end);
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
	int		i;
	int		j;
	t_room	*pivot;
	t_room	*temp;

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
