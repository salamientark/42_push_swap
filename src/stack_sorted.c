/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:06:51 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/15 21:09:07 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/*  USE ON STACK_A ONLY:
	Check if value are in ASCENDING order.
	Return:
	0		: Is_sorted
	[1,n]	: Sorted but n rotate to start with minimum value
	-1	   : Not sorted
*/
int	a_sorted(t_stack *stack)
{
	int				rot;
	unsigned int	index;
	unsigned int	size;
	t_stack_data	*record;

	if (!(stack->head) || stack->head == stack->head->next)
		return (0);
	index = 0;
	size = stack->size;
	record = stack->head;
	rot = 0;
	while (index < size)
	{
		if ((record->key != (record->next)->key - 1)
			&& !(record->key == size && record->next->key == 1))
			return (-1);
		if (record->key == 1)
			rot = index;
		index++;
		record = record->next;
	}
	return (rot);
}

/*
	OBVIOUS
*/
int	is_sorted(t_stack *stack)
{
	unsigned int	index;
	t_stack_data	*record;

	if (!stack->head || stack->head == stack->head->prev)
		return (1);
	index = stack->size;
	record = stack->head;
	while (index > 0)
	{
		if ((record->prev->key > record->key)
			&& !(record->prev->key == stack->max && record->key == stack->min))
			return (0);
		index--;
		record = record->prev;
	}
	return (1);
}
