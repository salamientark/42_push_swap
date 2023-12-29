/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 23:51:47 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/29 13:51:42 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.h"

// Init doubly rotary linked list
t_stack_data	*init_stack_data(const int value)
{
	t_stack_data	*stack;

	stack = (t_stack_data *)malloc(sizeof(struct s_stack_data));
	if (!stack)
		return (NULL);
	stack->value = value;
	stack->next = stack;
	stack->prev = stack;
	return (stack);
}

// DELETE ELEM FROM STACK IF EXIST
t_stack_data	*delete(t_stack_data *top)
{
	t_stack_data	*tmp;

	if (!top)
		return (NULL);
	if (top->next == top)
	{
		free(top);
		top = NULL;
		return (top);
	}
	tmp = top->prev;
	tmp->next = top->next;
	tmp = tmp->next;
	tmp->prev = top->prev;
	free(top);
	top = tmp->prev;
	return (top);
}

// Remove without free
//  Do nothing if no stack or one element only
t_stack_data	*remove(t_stack_data **top)
{
	t_stack_data	*elem;
	t_stack_data	*removed_top;

	if (!(*top) || (*top)->next == (*top))
		return (*top);
	removed_top = *top;
	elem = (*top)->prev;
	elem->next = (*top)->next;
	elem = (*top)->next;
	elem->prev = (*top)->prev;
	removed_top->next = NULL;
	removed_top->prev = NULL;
	(*top) = elem;
	return (removed_top);
}