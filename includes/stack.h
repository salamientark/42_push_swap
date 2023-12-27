/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:39:37 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/27 22:47:25 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "../libft/libft.h"

// Double chained rotary structur allow push swap manipulation easily
typedef struct s_stack
{
	unsigned int	key;
	int				value;
	struct s_stack	*prev;
	struct s_stack	*next;
}				t_stack;

// Type containg push_swap opeartion and variable
typedef struct s_operation
{
	t_stack	**arg_a;
	t_stack	**arg_b;
	void	(*operation)(t_stack **, t_stack **);
}				t_operation;

// stack.c
t_stack	*add_stack(const unsigned int key, const int val, t_stack *stack);
void	free_stack(t_stack**stack);
int		stack_size(t_stack *stack);

// arg_parser.c
t_stack	*parse_arg(int ac, char **av);

//operation.c
void	push_old(t_stack **src, t_stack **dest);
void	swap_old(t_stack **stack);
void	rotate_old(t_stack **stack);
void	r_rotate_old(t_stack **stack);
int		operation(t_stack **a, t_stack **b, char *op);

// sort_stack.c
// t_stack_dict    stack_to_dict(t_stack *stack, int size);
void    sort_stack_key(t_stack **stack);

//analyze stack.c
int sorted_stack_a(t_stack *stack);

// old_operation.c
void	push(t_stack **src, t_stack **dest);
void	swap(t_stack **stack_a, t_stack **stack_b);
void	rotate(t_stack **stack_a, t_stack **stack_b);
void	r_rotate(t_stack **stack_a, t_stack **stack_b);

#endif
