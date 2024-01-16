/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restack_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:45:01 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 10:50:48 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/* 
	Distance in rotate count OR -1 if not found
*/
int	dist_from_head(t_stack *stack, unsigned int value)
{
	int				distance;
	t_stack_data	*record;

	if (stack->head->key == value)
		return (0);
	distance = 1;
	record = stack->head->next;
	while (record != stack->head)
	{
		if (record->key == value)
			return (distance);
		distance++;
		record = record->next;
	}
	return (-1);
}

/*
	Distance from stack_b->head to ideal spot in stack_b in rotate counting
	NOT_PROTECTED
*/
int	good_pos_in_stack(t_stack *stack, unsigned int val)
{
	t_stack_data	*record;
	unsigned int	distance;
	unsigned int	ref;

	record = stack->head;
	distance = 0;
	if (val < stack->min || stack->max < val)
	{
		ref = stack->min;
		while (record->key != ref)
		{
			distance++;
			record = record->next;
		}
	}
	else
	{
		while (!(record->prev->key < val && val < record->key))
		{
			distance++;
			record = record->next;
		}
	}
	return (distance);
}

/*
	Return closest move_nbr between :
	[(rr +) (ra || rb)]
	[ra + rrb]
	[rra + rb]
	[(rrr +) (rra || rrb)]
*/
int	best_dist(int stack_a_size, int stack_b_size,
	int rot_a, int rot_b)
{
	int	dist;

	dist = ft_max(rot_a, rot_b);
	dist = ft_min(dist, rot_a + (stack_b_size - rot_b) % stack_b_size);
	dist = ft_min(dist, (stack_a_size - rot_a) % stack_a_size + rot_b);
	dist = ft_min(dist, ft_max((stack_a_size - rot_a) % stack_a_size,
				(stack_b_size - rot_b) % stack_b_size));
	return (dist);
}
