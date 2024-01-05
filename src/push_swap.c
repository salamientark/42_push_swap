/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:11:55 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/05 09:34:37 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"

static void	free_push_swap(t_push_swap_env *ps_env, t_list **operation_buffer)
{
	free_op_buffer(operation_buffer, NULL);
	free_stack_data(&((*ps_env).stack_a.head));
	free_stack_data(&((*ps_env).stack_b.head));
}

// static void    print_op_buffer(t_list *op_buffer)
// {
//     t_list  *head;

// 	if (!op_buffer)
// 		return ;
//     head = op_buffer->next;
//     while (head != op_buffer)
//     {
//         ft_putendl_fd(head->content, 1);
//         head = head->next;
//     }
//     ft_putendl_fd(head->content, 1);
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
	else if (op && op[0] == 'r' && ft_strlen(op) == 2)
		op_env.operation = &rotate;
	else if (op && op[0] == 'r' && ft_strlen(op) == 3)
		op_env.operation = &r_rotate;
	else
		return (0);
	if (op_env.operation == &push || (op[2] == 'r'
			|| (op[1] == 'r' && op[2] == '\n') || op[1] == 's'))
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

void    push_swap(int ac, char **av)
{
	t_push_swap_env	ps_env;
    t_list  		*operation_buffer;

	ps_env = init_push_swap(ac, av);
    if (!(ps_env.stack_a.head))
	{
		free_push_swap(&ps_env, &operation_buffer);
		return ;
	}
	// if ((*ps_env).stack_a.size > 5)
	// 	operation = unstack_a()
	
    if (ps_env.stack_a.size <= 5)
		operation_buffer = sort_small_stack(&(ps_env.stack_a), ps_env.stack_a.size);
	print_op_buffer(operation_buffer);
	free_push_swap(&ps_env, &operation_buffer);
}
