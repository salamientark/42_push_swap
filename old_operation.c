/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:03:56 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/29 13:51:34 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.h"


void	rotate_old(t_stack_data **stack)
{
	if (*stack)
		*stack = (*stack)->next;
}

// Reverse rotate
void	r_rotate_old(t_stack_data **stack)
{
	if (*stack)
		*stack = (*stack)->prev;
}

void	swap_old(t_stack_data **top)
{
	t_stack_data	*new_top;

	if (!(*top) || (*top)->next == *top)
		return ;
	new_top = (*top)->next;
	if (new_top->next != *top)
	{
		(*top)->next = new_top->next;
		new_top->prev = (*top)->prev;
		(*top)->prev = new_top;
		new_top->next = (*top);
		(*top)->next->prev = (*top);
		new_top->prev->next = new_top;
	}
	(*top) = new_top;
}

void	push_old(t_stack_data **src, t_stack_data **dest)
{
	t_stack_data	*elem;

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
