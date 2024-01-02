/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:39:37 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/02 18:21:04 by dbaladro         ###   ########.fr       */
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
	int				size;
	int				min;
	int				max;
	t_stack_data	*head;
}				t_stack;

// typedef	struct s_op_buffer
// {

// }

typedef struct s_push_swap_env
{
	t_stack	stack_a;
	t_stack	stack_b;
	int		max_size;
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

// sort_stack_data.c
void			sort_stack_data_3(t_stack *stack);
void    		sort_stack_data_5(t_stack *stack);

//analyze stack.c
int 			follow(t_stack_data *elem_a, t_stack_data *elem_b, unsigned int total_stack_size);
int 			a_sorted(t_stack_data *stack, unsigned int stack_size);
int				r_sorted(t_stack_data *stack, unsigned int stack_size);

//old_operation.c
void			push_old(t_stack_data **src, t_stack_data **dest);
void			swap_old(t_stack_data **stack);
void			rotate_old(t_stack_data **stack);
void			r_rotate_old(t_stack_data **stack);

#endif
