/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:11:55 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 10:50:48 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	free_push_swap(t_push_swap_env *ps_env, t_list **operation_buffer)
{
	free_op_buffer(operation_buffer, NULL);
	free_stack_data(&((*ps_env).stack_a.head));
	free_stack_data(&((*ps_env).stack_b.head));
}

static void	print_op_buffer(t_list *op_buffer)
{
	t_list	*head;

	if (!op_buffer)
		return ;
	head = op_buffer;
	ft_putendl_fd(head->content, 1);
	head = head->next;
	while (head != op_buffer)
	{
		ft_putendl_fd(head->content, 1);
		head = head->next;
	}
}

int	main(int ac, char **av)
{
	t_push_swap_env	ps_env;
	t_list			*operation_buffer;

	operation_buffer = NULL;
	ps_env = init_push_swap(ac, av);
	if (!(ps_env.stack_a.head) || (is_sorted(&(ps_env.stack_a)) == 1
			&& ps_env.stack_a.head->key == 1))
		return (free_push_swap(&ps_env, &operation_buffer), 0);
	if (ps_env.stack_a.size <= 5)
		operation_buffer = sort_small_stack(&(ps_env.stack_a), ps_env.max_size);
	else
		operation_buffer = sort_big_stack(ps_env);
	print_op_buffer(operation_buffer);
	free_push_swap(&ps_env, &operation_buffer);
	return (0);
}
