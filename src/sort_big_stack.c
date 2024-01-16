/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:45:26 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 10:50:48 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_list	*sort_big_stack(t_push_swap_env ps_env)
{
	t_list	*operation_buffer;

	operation_buffer = unstack_a(&(ps_env.stack_a), &(ps_env.stack_b));
	while (ps_env.stack_a.size > 5)
		operation_buffer = lst_concat(operation_buffer,
				unstack_a(&(ps_env.stack_a), &(ps_env.stack_b)));
	operation_buffer = lst_concat(operation_buffer,
			sort_small_stack(&(ps_env.stack_a), ps_env.stack_a.size));
	while (ps_env.stack_a.size < ps_env.max_size)
		operation_buffer = lst_concat(operation_buffer,
				restack(&(ps_env.stack_a), &(ps_env.stack_b)));
	while (!(ps_env.stack_a.head->key == 1))
	{
		operation_buffer = prev_op_buffer(operation_buffer);
		operation_buffer = add_op_buffer(operation_buffer,
				best_a_rotate(a_sorted(&(ps_env.stack_a)),
					ps_env.stack_a.size));
		operation(&(ps_env.stack_a), &(ps_env.stack_b),
			operation_buffer->content);
		operation_buffer = operation_buffer->next;
	}
	return (operation_buffer);
}
