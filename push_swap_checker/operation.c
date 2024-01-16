/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:27:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 10:29:33 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

unsigned int	biggest_key(t_stack *stack)
{
	unsigned int	biggest_key;
	t_stack_data	*record;

	if (!(stack->head))
		return (0);
	biggest_key = stack->head->key;
	record = stack->head->next;
	while (record != stack->head)
	{
		if (record->key > biggest_key)
			biggest_key = record->key;
		record = record->next;
	}
	return (biggest_key);
}

unsigned int	smallest_key(t_stack *stack)
{
	unsigned int	smallest_key;
	t_stack_data	*record;

	if (!(stack->head))
		return (0);
	smallest_key = stack->head->key;
	record = stack->head->next;
	while (record != stack->head)
	{
		if (record->key < smallest_key)
			smallest_key = record->key;
		record = record->next;
	}
	return (smallest_key);
}

int	operation(t_stack *a, t_stack *b, char *op)
{
	t_operation	op_env;

	op_env.arg_a = a;
	op_env.arg_b = NULL;
	if (op && op[0] == 's')
		op_env.operation = &swap;
	else if (op && op[0] == 'p')
		op_env.operation = &push;
	else if (op && op[0] == 'r' && ft_strlen(op) == 2)
		op_env.operation = &rotate;
	else if (op && op[0] == 'r' && ft_strlen(op) == 3)
		op_env.operation = &r_rotate;
	else
		return (0);
	if (op_env.operation == &push || (op[1] == 'r' && !op[2])
		|| (op[2] && op[2] == 'r') || op[1] == 's')
		op_env.arg_b = b;
	if (op[1] == 'b' || (ft_strlen(op) == 3 && op[2] == 'b'))
	{
		op_env.arg_a = b;
		if (op_env.operation == &push)
			op_env.arg_b = a;
	}
	op_env.operation(op_env.arg_a, op_env.arg_b);
	return (1);
}
