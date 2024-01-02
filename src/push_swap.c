/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:11:55 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/02 17:08:34 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

// void    push_swap(t_push_swap_env *ps_env)
// {
//     t_list  *operation_buffer;

//     operation_buffer = NULL;
//     while ((*ps_env).stack_a->size != (*ps_env).max_size && a_sorted((*ps_env).stack_a->head) != 0)
//     {
        
//     }
    
// }

int	operation(t_stack *a, t_stack *b, char *op)
{
	t_operation	op_env;

	op_env.arg_a = a;
	op_env.arg_b = NULL;
	if (op && op[0] == 's')
		op_env.operation = &swap;
	else if (op && op[0] == 'p')
		op_env.operation = &push;
	else if (op && op[0] == 'r' && ft_strlen(op) == 3)
		op_env.operation = &rotate;
	else if (op && op[0] == 'r' && ft_strlen(op) == 4)
		op_env.operation = &r_rotate;
	else
		return (0);
	if (op_env.operation == &push || (op[2] == 'r'
			|| (op[1] == 'r' && op[2] == '\n') || op[1] == 's'))
		op_env.arg_b = b;
	if (op[1] == 'b' || (ft_strlen(op) == 4 && op[2] == 'b'))
	{
		op_env.arg_a = b;
		if (op_env.operation == &push)
			op_env.arg_b = a;
	}
	op_env.operation(op_env.arg_a, op_env.arg_b);
	ft_printf("%s",op);
	return (1);
}