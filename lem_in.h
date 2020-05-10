/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdeloise <kdeloise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:42:37 by kdeloise          #+#    #+#             */
/*   Updated: 2020/05/07 14:49:51 by kdeloise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

typedef struct s_room	t_room;
typedef struct s_link	t_link;

typedef struct			s_link_list
{
	t_link				*data;
	struct s_link_list	*next;
}						t_link_list;

typedef struct			s_llist
{
	t_room			*data;
	struct s_llist	*next;
}						t_llist;

struct					s_room
{
	char			*name;
	int				x;
	int				y;
	int				col_fl;
	t_link_list		*links;
	struct s_room	*parent;
	struct s_room	*pred;
};

struct					s_link
{
	int				weight;
	t_room			*dst;
};

typedef struct			s_graph
{
	int				ants;
	t_room			**value_for_free;
	t_llist			*rooms;
	t_room			*start;
	t_room			*end;
}						t_graph;

typedef struct			s_flags
{
	t_room			**array_of_rooms_ptr;
	int				count_of_ants;
	int				count_of_room;
	int				count_of_path;
	int				count_of_edges;
	int				ant;
	int				con;
	int				start;
	int				end;
	int				i;
	int				fl;
	t_llist			*first;
}						t_flags;

typedef	struct			s_path
{
	struct s_path	*prev;
	struct s_path	*next;
	t_room			*r;
}						t_path;

typedef	struct			s_rooms
{
	t_room				*r;
	struct s_rooms		*next;
}						t_rooms;

typedef struct			s_ants
{
	int					num;
	t_path				*curr;
	struct s_ants		*next;
}						t_ants;

typedef struct			s_paths_list
{
	int					ants;
	int					len;
	t_ants				*buf;
	t_ants				*last_ant;
	t_path				*path;
	struct s_paths_list	*next;
	struct s_paths_list *prev;
}						t_paths_list;

void					ft_exit(const char *const str);

void					ft_swap_for_sort(t_room **array, int i, int j);
int						ft_partition_coor(t_room **array, int start, int end);
void					ft_quick_sort_coor(t_room **array, int start, int end);
int						ft_partition(t_room **array, int start, int end);
void					ft_quick_sort(t_room **array, int start, int end);

void					find_paste_link(t_llist *start, \
						char *name_link, t_link *add_link);
int						ft_not_link(t_link_list *link_rooms, \
						char *name_room_for_link);
void					binary_search_links(char *r1, char *r2, \
						t_flags *flags);
void					create_links_binary(t_graph *graph, char *name_coor, \
						t_flags *flags);

void					create_array_of_rooms_ptr(t_flags *flag,
		t_graph *graph);
void					check_double_name(t_room **array_of_rooms_ptr,
		int count);
void					check_double_coor(t_room **array_of_rooms_ptr,
		int count);

void					add_to_graph_rooms(char **split_name_coor,
		t_graph *graph);
void					create_graph_rooms(char **split_name_coor,
		t_graph *graph);
void					create_rooms(t_graph *graph, char *name_coor);
void					create_start_room(t_graph *graph, char *name_coor);
void					create_end_room(t_graph *graph, char *name_coor);

int						is_links(char *str);
int						is_start(char *str);
int						is_end(char *str);
int						is_comment(char *str);
int						is_coordinate(char *str);

void					ft_exit(const char *const str);
int						atoi_for_lemin(const char *str);
int						is_str_digits(char *str);
void					validate_coor(char **split_coor);
int						is_count_ants(char *str, t_flags *fl);

void					check_con(char **split_buff, t_graph *graph, \
						t_flags *fl, int *i);
void					check_coor(char **split_buff, t_graph *graph, \
						t_flags *fl, int *i);
void					check_end(char **split_buff, t_graph *graph, \
						t_flags *fl, int *i);
void					check_start(char **split_buff, t_graph *graph, \
						t_flags *fl, int *i);
void					check_sec(char **split_buff, t_graph *graph, \
						t_flags *fl, int *i);

void					zero_struct_flags(t_flags *fl);
void					check_ants(char *ants, t_flags *fl, int *i);
t_graph					*validate_rows(char **split_buff);
t_graph					*validation(char	*buff);
char					*create_validation_buff(void);

t_paths_list			*suurbale(t_graph *graph);
int						collision_handle(t_paths_list *list,
		t_path *p, int ret);
void					mdf(t_path *p);
void					bubble_sort(t_paths_list *l);
t_paths_list			*check_steps(t_paths_list *p_list,
		t_paths_list *final, int ants);
t_path					*bfs(t_graph *g);
void					modify_graph(t_path *p);
void					restore(t_graph *graph, t_paths_list *p_list);
t_paths_list			*plist_push_back(t_paths_list *p_list, t_path *p);

/*
** queue.c
*/
void					q_add_links(t_rooms **q, t_link_list *l,
		t_room *parent, t_room *start);
void					q_add_room(t_rooms **q, t_link *l);
t_room					*q_get(t_rooms **q);

void					recount_len(t_paths_list *l);
t_link_list				*del_link(t_link_list *l, t_room *r);
int						count_links(t_room *r);
int						get_max_path(t_room *start, t_room *end);
int						p_len(t_path *p);

t_paths_list			*get_max(t_paths_list *l);
void					print_ants(t_paths_list *l, int ants);
void					fill_buf(t_paths_list *l);
void					free_path_list(t_paths_list *l);
#endif
