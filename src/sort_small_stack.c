/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 20:18:42 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 10:50:48 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/stack_print.h"

/*
	Point of this is to make stack sort easier by having only
	easy to use value.
	[ 458, 98526, 2, 1156, 42, 666]
	 ===> Become
	[ 3, 6, 1, 5, 2, 4]
*/

/*
	Shortest move between "ra" && "rra"	
*/
char	*best_a_rotate(int rot, int size)
{
	if (rot > size / 2)
		return ("rra");
	else
		return ("ra");
}

/*  Check if the two value perfectly follow
	1 : TRUE
	0 : FALSE
*/
static int	follow(t_stack_data *elem_a, t_stack_data *elem_b,
	unsigned int total_stack_size)
{
	if (elem_a->key == elem_b->key - 1
		|| (elem_a->key - total_stack_size + 1 == elem_b->key))
		return (1);
	if ((elem_a->key == elem_b->key + 1
			|| (elem_a->key == 1 && elem_b->key == total_stack_size)))
		return (-1);
	return (0);
}

/*
	replace "ra" list by shorter "rra" list
	OR "rra" list by shorter "ra" list
*/
static t_list	*rotate_optimizer(t_list *op_buffer, unsigned int *index,
	unsigned int buffer_size, unsigned int stack_size)
{
	unsigned int	r_count;
	char			ref;
	t_list			*record;

	r_count = 0;
	record = op_buffer;
	ref = ((char *)(record->content))[1];
	while (*index + r_count < buffer_size
		&& ((char *)(record->content))[0] == 'r'
				&& ((char *)(record->content))[1] == ref)
	{
		record = record->next;
		r_count++;
	}
	if (r_count > stack_size / 2)
	{
		if (ref == 'r')
			record = lst_replace(op_buffer,
					make_op_buffer(stack_size - r_count, "ra"), r_count);
		else
			record = lst_replace(op_buffer,
					make_op_buffer(stack_size - r_count, "rra"), r_count);
	}
	*index = *index + r_count;
	return (record);
}

/*
	Check op_buffer and optimize what can be optimized
*/
static t_list	*optimize_operation(t_list *op_buffer, unsigned int stack_size)
{
	unsigned int	index;
	unsigned int	buffer_size;
	t_list			*record;

	if (!op_buffer)
		return (op_buffer);
	index = 0;
	record = op_buffer->next;
	buffer_size = op_buffer_size(op_buffer) - 1;
	while (index < buffer_size)
	{
		if (((char *)(record->content))[0] == 'r')
		{
			record = prev_op_buffer(record);
			record = rotate_optimizer(record->next, &index, buffer_size,
					stack_size);
		}
		else
		{
			record = record->next;
			index++;
		}
	}
	return (record->next);
}

/*
	Sort small stack without stack_b:
	RULES :
		"ra" or "rra" when sorted but not starting with minimum
		"sa" when FIRST and SECOND are reversed
		"ra" if IN_ORDER(LAST, FIRST) or IN_ORDER(FIRST, SECOND)
		"rra" if LAST and FIRST are reversed
		"sa" when lost
*/
t_list	*sort_small_stack(t_stack *stack_a, unsigned int size)
{
	int		sorted;
	t_list	*op_buffer;

	sorted = is_sorted(stack_a);
	op_buffer = NULL;
	while (!(sorted == 1 && stack_a->size == size
			&& stack_a->head->key == stack_a->min))
	{
		if (is_sorted(stack_a) > 0)
			op_buffer = add_op_buffer(op_buffer,
					best_a_rotate(a_sorted(stack_a), size));
		else if (follow(stack_a->head, stack_a->head->next, size) == -1)
			op_buffer = add_op_buffer(op_buffer, "sa");
		else if (follow(stack_a->head, stack_a->head->next, size) == 1
			|| follow(stack_a->head->prev, stack_a->head, size) == 1)
			op_buffer = add_op_buffer(op_buffer, "ra");
		else if (follow(stack_a->head->prev, stack_a->head, size) == -1)
			op_buffer = add_op_buffer(op_buffer, "rra");
		else
			op_buffer = add_op_buffer(op_buffer, "sa");
		operation(stack_a, NULL, op_buffer->content);
		sorted = is_sorted(stack_a);
	}
	op_buffer = optimize_operation(op_buffer, size);
	return (op_buffer);
}
