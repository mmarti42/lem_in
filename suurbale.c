/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurbale.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:38:41 by mmarti            #+#    #+#             */
/*   Updated: 2020/03/07 14:38:43 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths_list	*suurbale(t_graph *graph)
{
	int				max_path;
	t_path			*p;
	t_paths_list	*p_list;
	t_paths_list	*final;

	final = NULL;
	max_path = get_max_path(graph->start, graph->end);
	p_list = NULL;
	while (max_path--)
	{
		if (!(p = bfs(graph)))
			break ;
		p_list = plist_push_back(p_list, p);
		if (collision_handle(p_list, p->next, 0))
			recount_len(p_list);
		modify_graph(p);
		final = check_steps(p_list, final, graph->ants);
		restore(graph, p_list);
	}
	free_path_list(p_list);
	bubble_sort(final);
	return (final);
}
