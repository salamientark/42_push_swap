/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:44:36 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/25 16:06:57 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

// REWORK TO FREE LAST ELEMENT OF LIST
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	if (!(*stack))
		return ;
	if (*stack == (*stack)->next)
	{
		free(*stack);
		*stack = NULL;
		return ;
	}
	tmp = (*stack)->next;
	(*stack)->prev->next = NULL;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

t_stack	*add_stack(const int val, t_stack *stack)
{
	t_stack	*elem;

	elem = (t_stack *)malloc(sizeof(struct s_stack));
	if (!elem)
		return (NULL);
	elem->value = val;
	if (!stack)
	{
		elem->next = elem;
		elem->prev = elem;
	}
	else
	{
		elem->prev = stack->prev;
		elem->next = stack;
		if (stack->next == stack)
			stack->next = elem;
		(elem->prev)->next = elem;
		stack->prev = elem;
	}
	return (elem);
}