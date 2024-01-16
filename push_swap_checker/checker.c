/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:45:27 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 09:55:35 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int is_valid_operation(char *op)
{
    size_t  op_len;

    op_len  = ft_strlen(op);
    if (op_len != 2 && op_len != 3)
        return (0);
    if (op[0] != 's' && op[0] != 'r' && op[0] != 'p')
        return (0);
    if (op_len == 3)
        return (op[0] == 'r' && op[1] == 'r'
            && (op[2] == 'r' || op[2] == 'a' || op[2] == 'b'));
    if (op[0] == 'p')
        return (op[1] == 'a' || op[1] == 'b');
    return (op[0] == op[1] || op[1] == 'a' || op[1] == 'b');
}

static int	operation(t_stack *a, t_stack *b, char *op)
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

/*
	OBVIOUS
*/
static int	is_sorted(t_stack *stack)
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

void    checker(int ac, char **av)
{
    t_checker ps_env;
    char            *op;

	op = NULL;
    ps_env = init_push_swap(ac, av);
    if (!(ps_env.stack_a.head))
    {
        free_checker(&ps_env);
        return ;
    }
    op = get_next_line(0);
    while (op)
    {
        if (!is_valid_operation(op))
            return (end_checker(&ps_env, &op, "Error"));
        operation(&(ps_env.stack_a), &(ps_env.stack_b), op);
        free(op);
        op = get_next_line(0);
    }
    if (is_sorted(&(ps_env.stack_a)) && ps_env.stack_a.head->key == 1)
        return (end_checker(&ps_env, &op, "OK"));
    return (end_checker(&ps_env, &op, "KO"));
}