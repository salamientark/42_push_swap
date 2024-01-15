/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_buffer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:37:35 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/15 18:42:20 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/*
	OBVIOUS
*/
unsigned int	op_buffer_size(t_list *op_buffer)
{
	unsigned int	size;
	t_list			*record;

	if (!op_buffer)
		return (0);
	size = 1;
	record = op_buffer->next;
	while (record != op_buffer)
	{
		size++;
		record = record->next;
	}
	return (size);
}

/*
	execute every operation on stacks
*/
void	execute_op_buffer(t_stack *stack_a, t_stack *stack_b, t_list *op_buffer)
{
	t_list	*record;

	record = op_buffer;
	while (record->next != op_buffer)
	{
		operation(stack_a, stack_b, record->content);
		record = record->next;
	}
	operation(stack_a, stack_b, record->content);
}
