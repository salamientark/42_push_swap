/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 23:59:12 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/25 00:05:45 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.h"

/*	Description
		Alt version make all function with two arg
		to make a "one call recursvie" kind of function
	Exemple :
		func(a, b) = func(a) + func(b)
	This often implies a call with of func(a, NULL)
	to stop the function
*/

void	rotate(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a)
		*stack_a = (*stack_a)->next;
	if (stack_b && *stack_b)
		rotate(stack_b, NULL);
}

// Reverse rotate
void	r_rotate(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a)
		*stack_a = (*stack_a)->prev;
	if (stack_b && *stack_b)
		r_rotate(stack_b, NULL);
}

void	swap(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*new_top;

	if (!(*stack_a) || (*stack_a)->next == *stack_a)
		return ;
	new_top = (*stack_a)->next;
	if (*stack_a != new_top->next)
	{
		(*stack_a)->next = new_top->next;
		new_top->prev = (*stack_a)->prev;
		(*stack_a)->prev = new_top;
		new_top->next = (*stack_a);
		(*stack_a)->next->prev = (*stack_a);
		new_top->prev->next = new_top;
	}
	(*stack_a) = new_top;
	if (!stack_b)
		return ;
	swap(stack_b, NULL);
}

void	push(t_stack **src, t_stack **dest)
{
	t_stack	*elem;

	if (!(*src))
		return ;
	elem = *src;
	if (elem != elem->next)
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
		*src = elem->next;
	}
	if (elem == elem->next)
		*src = NULL;
	if (!(*dest))
		(*dest) = elem;
	elem->prev = (*dest)->prev;
	elem->next = (*dest);
	if ((*dest) == (*dest)->next)
		(*dest)->next = elem;
	else
		((*dest)->prev)->next = elem;
	(*dest)->prev = elem;
	*dest = elem;
}

void	operation(t_stack **a, t_stack **b, char *op)
{
	t_operation	op_env;

	op_env.arg_a = a;
	if (op[0] == 's')
		op_env.operation = &swap;
	else if (op[0] == 'p')
		op_env.operation = &push;
	else if (op[0] == 'r' && ft_strlen(op) == 2)
		op_env.operation = &rotate;
	else
		op_env.operation = &r_rotate;
	if (op_env.operation != &push)
		op_env.arg_b = NULL;
	else
		op_env.arg_b = b;
	if (op[1] == 'b' || (ft_strlen(op) == 3 && op[2] == 'b'))
	{
		op_env.arg_a = b;
		if (op_env.operation == &push)
			op_env.arg_b = a;
	}
	op_env.operation(op_env.arg_a, op_env.arg_b);
}