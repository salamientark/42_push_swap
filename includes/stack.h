/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:39:37 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 09:54:49 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "../libft/libft.h"

/*
	Double chained rotary structur allow push swap manipulation easily
*/
typedef struct s_stack_data
{
	unsigned int		key;
	int					value;
	struct s_stack_data	*prev;
	struct s_stack_data	*next;
}				t_stack_data;

/*
	Stack_param;
	id : 'a' || 'b'
	size
	min value
	mac value
	pointer to data;
*/
typedef struct s_stack
{
	char			id;
	unsigned int	size;
	unsigned int	min;
	unsigned int	max;
	t_stack_data	*head;
}				t_stack;

/*
	Push_swap_environment
*/
typedef struct s_push_swap_env
{
	t_stack				stack_a;
	t_stack				stack_b;
	unsigned int		max_size;
}				t_push_swap_env;

// Type containg push_swap opeartion and variable
typedef struct s_operation
{
	t_stack			*arg_a;
	t_stack			*arg_b;
	void			(*operation)(t_stack *, t_stack *);
}				t_operation;

/*
	UNSTACK limit structure for block division
*/
typedef struct s_limit
{
	unsigned int	a_low_lim;
	unsigned int	a_high_lim;
	unsigned int	b_low_lim;
	unsigned int	b_high_lim;
}				t_limit;

// stack.c
t_stack			init_stack(char id);
void			free_stack_data(t_stack_data**stack);
t_stack_data	*add_stack_data(const int val, t_stack_data *stack);
int				stack_size(t_stack_data *stack);

//stack_utils.c
unsigned int	smallest_key(t_stack *stack);
unsigned int	biggest_key(t_stack *stack);

// arg_parser.c
t_push_swap_env	init_push_swap(int ac, char **av);

// operation.c
void			push(t_stack *src, t_stack *dest);
void			swap(t_stack *stack_a, t_stack *stack_b);
void			rotate(t_stack *stack_a, t_stack *stack_b);
void			r_rotate(t_stack *stack_a, t_stack *stack_b);

// push_swap.c
int				operation(t_stack *a, t_stack *b, char *op);

// sort_stack_data.c
t_list			*sort_small_stack(t_stack *stack_a, unsigned int size);
t_list			*sort_big_stack(t_push_swap_env ps_env);
char			*best_a_rotate(int rot, int size);

//analyze stack.c
int				a_sorted(t_stack *stack);
int				is_sorted(t_stack *stack);

// op_bufer.c
void			free_op_buffer(t_list **list, void (*free_content)(void *));
t_list			*init_op_buffer(char *op);
t_list			*add_op_buffer(t_list *op_buffer, char *op);
t_list			*make_op_buffer(unsigned int size, char *content);
t_list			*prev_op_buffer(t_list *op_buffer);

// op_buffer_utils.c
unsigned int	op_buffer_size(t_list *op_buffer);
void			execute_op_buffer(t_stack *stack_a, t_stack *stack_b,
					t_list *op_buffer);

// lst_utils.c
t_list			*lst_remove(t_list *head, unsigned int to_remove);
t_list			*lst_insert(t_list *dest_head, t_list *to_insert);
t_list			*lst_replace(t_list *dest, t_list *replace,
					unsigned int replace_size);
t_list			*lst_join(t_list *dest, t_list *src);
t_list			*lst_concat(t_list *dest, t_list *src);

// lst_join.c
t_list			*lst_join(t_list *dest_head, t_list *to_join);

// unstack_utils.c
int				is_in_bound(t_limit limit, unsigned int val);
int				is_in_block(unsigned int low_block_lim,
					unsigned int high_block_lim, unsigned int val);
int				are_in_same_block(unsigned int val_a, unsigned int val_b,
					t_limit limit);
int				both_bound_in_block(t_limit limit, t_stack_data *stack);

// unstack.c
t_list			*unstack_a(t_stack *stack_a, t_stack *stack_b);

// optimize_unstack.c
void			optimize_unstack(t_list **op_buffer,
					unsigned int op_buffer_size);

// math.c
int				ft_min(int a, int b);
int				ft_max(int a, int b);
unsigned int	ft_abs(int n);

// restack_utils.c
int				dist_from_head(t_stack *stack, unsigned int value);
int				good_pos_in_stack(t_stack *stack, unsigned int val);
int				best_dist(int stack_a_size, int stack_b_size,
					int rot_a, int rot_b);

// restack.c
t_list			*restack(t_stack *dest, t_stack *src);
void			execute_op_buffer(t_stack *stack_a, t_stack *stack_b,
					t_list *op_buffer);

// optimize_restack.c
void			optimize_restack(t_list **op_buffer);

#endif
