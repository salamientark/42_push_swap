/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:44:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/04 12:23:09 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

t_stack	init_stack(char id)
{
	t_stack	stack;

	stack.id = id;
	stack.size = 0;
	stack.min = 0;
	stack.max = 0;
	stack.head = NULL;
	return (stack);
}

// REWORK TO FREE LAST ELEMENT OF LIST
void	free_stack_data(t_stack_data **stack)
{
	t_stack_data	*tmp;

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

static void	update_val(t_stack_data *stack)
{
	t_stack_data	*index;

	index = stack->next;
	while (index != stack)
	{
		if (index->value > stack->value)
			index->key++;
		else
			stack->key++;
		index = index->next;
	}
}

t_stack_data	*add_stack_data(const int val, t_stack_data *stack)
{
	t_stack_data	*elem;

	elem = (t_stack_data *)malloc(sizeof(struct s_stack_data));
	if (!elem)
		return (NULL);
	elem->key = 1;
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
	update_val(elem);
	return (elem);
}

int	stack_size(t_stack_data *stack)
{
	int				size;
	t_stack_data	*stack_cp;

	size = 0;
	if (!stack)
		return (0);
	size++;
	if (stack == stack->next)
		return (1);
	stack_cp = stack->next;
	while (stack_cp != stack)
	{
		size++;
		stack_cp = stack_cp->next;
	}
	return (size);
}
