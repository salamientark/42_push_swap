/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:39:37 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/22 22:08:20 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "../libft/libft.h"

// Double chained rotary structur allow push swap manipulation easily
typedef struct s_stack
{
	int				value;
	struct s_stack	*prev;
	struct s_stack	*next;
}				t_stack;

void	insert(t_stack **dest, t_stack *elem);

// stack.c
t_stack	*init_stack(void);
t_stack	*add_stack(const int val, t_stack *stack);
t_stack	*delete(t_stack *top);
t_stack	*remove(t_stack **stack);
void	free_stack(t_stack**stack);

// arg_parser.c
t_stack	*parse_arg(int ac, char **av);

void	push(t_stack **src, t_stack **dest);
void	swap(t_stack **stack);
void	rotate(t_stack **stack);
void	r_rotate(t_stack **stack);

void	push_chacal(t_stack **src, t_stack **dest);
void	swap_chacal(t_stack **stack_a, t_stack **stack_b);
void	rotate_chacal(t_stack **stack_a, t_stack **stack_b);
void	r_rotate_chacal(t_stack **stack_a, t_stack **stack_b);

#endif
