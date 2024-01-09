/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:06:51 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/09 18:16:52 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/*  USE ON STACK_A ONLY:
	Check if value are in ASCENDING order.
	Return:
	0		: Is_sorted
	[1,n]	: Sorted but n rotate to start with 1
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

int	is_r_sorted(t_stack *stack)
{
	unsigned int	index;
	t_stack_data	*record;

	if (!stack->head || stack->head == stack->head->prev)
		return (1);
	index = stack->size;
	record = stack->head;
	while (index > 0)
	{
		if ((record->prev->key < record->key)
			&& !(record->prev->key == stack->min && record->key == stack->max))
			return (0);
		index--;
		record = record->prev;
	}
	return (1);
}

/*  Check if the two value perfectly follow
	1 : TRUE
	0 : FALSE
*/
int	follow(t_stack_data *elem_a, t_stack_data *elem_b,
	unsigned int total_stack_size)
{
	if (elem_a->key == elem_b->key - 1
		|| (elem_a->key == total_stack_size && elem_b->key == 1))
		return (1);
	if ((elem_a->key == elem_b->key + 1
			|| (elem_a->key == 1 && elem_b->key == total_stack_size)))
		return (-1);
	return (0);
}
