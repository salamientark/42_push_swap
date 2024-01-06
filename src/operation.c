/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 23:59:12 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/06 08:50:33 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/*	Description
		Alt version make all function with two arg
		to make a "one call recursvie" kind of function
	Exemple :
		func(a, b) = func(a) + func(b)
	This often implies a call with of func(a, NULL)
	to stop the function
*/

void	rotate(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a && stack_a->head)
		stack_a->head = stack_a->head->next;
	if (stack_b && stack_b->head)
		rotate(stack_b, NULL);
}

// Reverse rotate
void	r_rotate(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a && stack_a->head)
		stack_a->head = stack_a->head->prev;
	if (stack_b && stack_b->head)
		r_rotate(stack_b, NULL);
}

void	swap(t_stack *stack_a, t_stack *stack_b)
{
	t_stack_data	*new_top;

	if (!(stack_a->head) || (stack_a->head)->next == stack_a->head)
		return ;
	new_top = stack_a->head->next;
	if (stack_a->head != new_top->next)
	{
		(stack_a->head)->next = new_top->next;
		new_top->prev = (stack_a->head)->prev;
		(stack_a->head)->prev = new_top;
		new_top->next = (stack_a->head);
		(stack_a->head)->next->prev = (stack_a->head);
		new_top->prev->next = new_top;
	}
	(stack_a->head) = new_top;
	if (!stack_b || !(stack_b->head))
		return ;
	swap(stack_b, NULL);
}

static void	update_stack_after_push(t_stack *dest, t_stack *src)
{
	unsigned int	push_value;

	push_value = dest->head->key;
	if (!(dest->head))
		return ;
	dest->size++;
	if (push_value > dest->max || dest->max == 0)
		dest->max = push_value;
	if (push_value < dest->min || dest->min == 0)
		dest->min = push_value;
	if (!(src->head))
	{
		src->size = 0;
		src->min = 0;
		src->max = 0;
		return ;
	}
	src->size--;
	if (push_value == src->max)
		src->max = biggest_key(src);
	if (push_value == src->min)
		src->min = smallest_key(src);
}

void	push(t_stack *dest, t_stack *src)
{
	t_stack_data	*elem;

	if (!src->head)
		return ;
	elem = src->head;
	if (elem != elem->next)
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
		src->head = elem->next;
	}
	if (elem == elem->next)
		src->head = NULL;
	if (!(dest->head))
		(dest->head) = elem;
	elem->prev = (dest->head)->prev;
	elem->next = (dest->head);
	if ((dest->head) == (dest->head)->next)
		(dest->head)->next = elem;
	else
		((dest->head)->prev)->next = elem;
	(dest->head)->prev = elem;
	dest->head = elem;
	update_stack_after_push(dest, src);
}
