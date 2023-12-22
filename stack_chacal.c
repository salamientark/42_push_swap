/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_chacal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:39:24 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/22 22:05:38 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

/*	Description
		Chacal version make all function with two arg
		to make a "one call recursvie" kind of function
	Exemple :
		func_chacal(a, b) = func(a) + func(b)
	This often implies a call with of func_chacal(a, NULL)
	to stop the function
*/

void	rotate_chacal(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a)
		*stack_a = (*stack_a)->next;
	if (stack_b)
		rotate_chacal(stack_b, NULL);
}

// Reverse rotate_chacal
void	r_rotate_chacal(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a)
		*stack_a = (*stack_a)->prev;
	if (stack_b)
		r_rotate_chacal(stack_b, NULL);
}

void	swap_chacal(t_stack **stack_a, t_stack **stack_b)
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
	if (stack_b)
		swap_chacal(stack_b, NULL);
}
