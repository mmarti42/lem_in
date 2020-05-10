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
