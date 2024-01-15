/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unstack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:04:34 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/15 20:17:16 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/*
	Shortest path between "rb" and "rrb"
*/
static char	*best_b_rotate(int rot, int size)
{
	if (rot > size / 2)
		return ("rrb");
	else
		return ("rb");
}

/*
	An aligned block is a block that can take both lower_limit value
	OR upper_limit value as valid push operation
	This is true when the last stack_value and the first_stack_value
	are from different block
*/
int	is_block_aligned(t_limit limit, t_stack_data *stack)
{
	if (!stack || stack->next == stack)
		return (1);
	if (!both_bound_in_block(limit, stack))
		return (1);
	if (is_in_bound(limit, stack->prev->key) && is_in_bound(limit, stack->key)
		&& !(are_in_same_block(stack->prev->key, stack->key, limit)))
		return (1);
	return (0);
}

/*
	Best rotate to align block
*/
char	*align_block(t_limit limit, t_stack *stack)
{
	t_stack_data	*record;
	unsigned int	rotate;
	unsigned int	r_rotate;

	record = stack->head;
	rotate = 0;
	while (!(is_block_aligned(limit, record)))
	{
		rotate++;
		record = record->next;
	}
	r_rotate = 0;
	record = stack->head;
	while (!(is_block_aligned(limit, record)))
	{
		r_rotate++;
		record = record->prev;
	}
	if (r_rotate < rotate)
		return (best_b_rotate(stack->size - r_rotate, stack->size));
	return (best_b_rotate(rotate, stack->size));
}

/*
	Make a t_limit element
*/
t_limit	make_limit(t_stack *stack)
{
	t_limit	limit;

	limit.a_high_lim = stack->size / 3 + stack->min - 1;
	limit.a_low_lim = stack->min - 1;
	limit.b_low_lim = stack->max - stack->size / 3;
	limit.b_high_lim = stack->max;
	return (limit);
}

/*
	Unstack value from stack a in a way that:
	The lowest one third numbers are at the top of stack_b
	The highest one third numbers are at the bottom of stack_b
		OR Vice Versa
	The middle value are kept in a
*/
t_list	*unstack_a(t_stack *stack_a, t_stack *stack_b)
{
	t_limit			limit;
	unsigned int	final_size;
	t_list			*op_buffer;

	op_buffer = NULL;
	limit = make_limit(stack_a);
	final_size = limit.b_low_lim - limit.a_high_lim;
	while (stack_a->size > final_size)
	{
		if (limit.a_high_lim < stack_a->head->key
			&& stack_a->head->key <= limit.b_low_lim)
			op_buffer = add_op_buffer(op_buffer, "ra");
		else if (stack_b->head && are_in_same_block(stack_a->head->key,
				stack_b->head->key, limit))
			op_buffer = add_op_buffer(op_buffer, "pb");
		else if (!is_block_aligned(limit, stack_b->head))
			op_buffer = add_op_buffer(op_buffer, align_block(limit, stack_b));
		else
			op_buffer = add_op_buffer(op_buffer, "pb");
		operation(stack_a, stack_b, op_buffer->content);
	}
	return (op_buffer->next);
}
