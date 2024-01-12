/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:39:37 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/13 00:24:41 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "../libft/libft.h"

// Double chained rotary structur allow push swap manipulation easily
typedef struct s_stack_data
{
	unsigned int		key;
	int					value;
	struct s_stack_data	*prev;
	struct s_stack_data	*next;
}				t_stack_data;

typedef struct s_stack
{
	char			id;
	unsigned int	size;
	unsigned int	min;
	unsigned int	max;
	t_stack_data	*head;
}				t_stack;

// typedef	struct s_op_buffer
// {

// }

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

// stack.c
t_stack			init_stack(char id);
void			free_stack_data(t_stack_data**stack);
t_stack_data	*add_stack_data(const int val, t_stack_data *stack);
int				stack_size(t_stack_data *stack);

//stack_utils.c
unsigned int smallest_key(t_stack *stack);
unsigned int biggest_key(t_stack *stack);

// arg_parser.c
t_push_swap_env	init_push_swap(int ac, char **av);

// operation.c
void			push(t_stack *src, t_stack *dest);
void			swap(t_stack *stack_a, t_stack *stack_b);
void			rotate(t_stack *stack_a, t_stack *stack_b);
void			r_rotate(t_stack *stack_a, t_stack *stack_b);

// push_swap.c
int				operation(t_stack *a, t_stack *b, char *op);
void			push_swap(int ac, char **av);

// sort_stack_data.c
t_list	*sort_small_stack(t_stack *stack_a, unsigned int size);

//analyze stack.c
int 			follow(t_stack_data *elem_a, t_stack_data *elem_b, unsigned int total_stack_size);
int 			a_sorted(t_stack *stack);
int				is_r_sorted(t_stack *stack);
int				is_sorted(t_stack *stack);

// op_bufer.c
void			free_op_buffer(t_list **list, void (*free_content)(void *));
t_list  		*init_op_buffer(char *op);
t_list  		*add_op_buffer(t_list *op_buffer, char *op);
t_list  		*make_op_buffer(unsigned int size, char *content);
t_list  		*prev_op_buffer(t_list *op_buffer);

// op_buffer_utils.c
unsigned int	op_buffer_size(t_list *op_buffer);

// lst_replace.c
t_list  		*lst_remove(t_list *head, unsigned int to_remove);
t_list  		*lst_insert(t_list *dest_head, t_list *to_insert);
t_list  		*lst_replace(t_list *dest, t_list *replace, unsigned int replace_size);

// lst_join.c
t_list  *lst_join(t_list *dest_head, t_list *to_join);

// unstack.c
t_list	*unstack_a(t_stack *stack_a, t_stack *stack_b);

// optimize_unstack.c
t_list  *optimize_unstack(t_list *op_buffer, unsigned int op_buffer_size);

// math.c
int 			ft_min(int a, int b);
int 			ft_max(int a, int b);
unsigned int 	ft_abs(int n);


//old_operation.c
void			push_old(t_stack_data **src, t_stack_data **dest);
void			swap_old(t_stack_data **stack);
void			rotate_old(t_stack_data **stack);
void			r_rotate_old(t_stack_data **stack);

#endif
