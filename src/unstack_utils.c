/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unstack_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:27:09 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/15 19:47:18 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/*
	check if val is in the limit range. When unstack for the second time
	element in stack_b can be higher or lower than limit.
	So it make blocks whithin the same limit
*/
int	is_in_bound(t_limit limit, unsigned int val)
{
	return ((limit.a_low_lim < val && val <= limit.a_high_lim)
		|| (limit.b_low_lim < val && val <= limit.b_high_lim));
}

/*
	OBVIOUS
*/
int	is_in_block(unsigned int low_block_lim, unsigned int high_block_lim,
						unsigned int val)
{
	return (low_block_lim < val && val <= high_block_lim);
}

/*
	OBVIOUS
*/
int	are_in_same_block(unsigned int val_a, unsigned int val_b,
			t_limit limit)
{
	int	result;

	result = 0;
	result = is_in_block(limit.a_low_lim, limit.a_high_lim, val_a);
	if (result)
		return (result && is_in_block(limit.a_low_lim,
				limit.a_high_lim, val_b));
	result = is_in_block(limit.b_low_lim, limit.b_high_lim, val_a);
	if (result)
		return (result && is_in_block(limit.b_low_lim,
				limit.b_high_lim, val_b));
	result = is_in_block(limit.a_high_lim, limit.b_low_lim, val_a);
	return (result && is_in_block(limit.a_high_lim, limit.b_low_lim, val_b));
}

/*
	Check if block containt a value from lower limit and a value from upper limit
	
*/
int	both_bound_in_block(t_limit limit, t_stack_data *stack)
{
	t_stack_data	*record;
	t_stack_data	*first_bound;
	int				bound_nbr;

	if (!stack || stack->next == stack)
		return (0);
	bound_nbr = 0;
	bound_nbr = is_in_bound(limit, stack->prev->key);
	if (bound_nbr)
		first_bound = stack->prev;
	record = stack;
	while (record->next != stack)
	{
		if (bound_nbr == 1 && is_in_bound(limit, record->key)
			&& !are_in_same_block(first_bound->key, record->key, limit))
			return (1);
		if (bound_nbr == 0 && is_in_bound(limit, record->key))
		{
			bound_nbr++;
			first_bound = record;
		}
		record = record->next;
	}
	return (0);
}
