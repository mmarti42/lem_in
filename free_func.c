/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:56:29 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/10 16:56:29 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_path(t_path *p)
{
	if (!p)
		return ;
	free_path(p->next);
	free(p);
}

void	free_path_list(t_paths_list *l)
{
	if (!l)
		return ;
	free_path_list(l->next);
	free_path(l->path);
	free(l);
}
