/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:18:17 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/15 19:26:44 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

int	best_rotate_dist(t_stack *dest, t_stack *src, unsigned int val)
{
	int	place_in_src;
	int	place_in_dest;
	int	dist;

	place_in_src = dist_from_head(src, val);
	place_in_dest = good_pos_in_stack(dest, val);
	dist = ft_max(place_in_dest, place_in_src);
	dist = ft_min(dist, place_in_dest + ((int)src->size - place_in_src));
	dist = ft_min(dist, ((int)dest->size - place_in_dest) + place_in_src);
	dist = ft_min(dist, ft_max((int)dest->size - place_in_dest,
				(int)src->size - place_in_src));
	return (dist);
}

int	best_head_dist(t_stack *stack, unsigned int val)
{
	int				dist;
	t_stack_data	*record;

	record = stack->head;
	dist = 0;
	while (record->key != val)
	{
		dist++;
		record = record->next;
	}
	return (ft_min(dist, (stack->size - dist + 1)));
}

int	best_val_to_insert(t_stack *dest, t_stack *src)
{
	unsigned int	val;
	int				dist;
	t_stack_data	*record;
	t_stack_data	*record_prev;

	record = src->head;
	record_prev = record->prev;
	val = src->head->key;
	dist = best_rotate_dist(dest, src, val);
	while (dist > best_head_dist(src, val) && record != record_prev)
	{
		if (best_rotate_dist(dest, src, record->key) < dist)
			val = record->key;
		dist = ft_min(dist, best_rotate_dist(dest, src, record->key));
		record = record->next;
		if (best_rotate_dist(dest, src, record_prev->key) < dist)
		{
			val = record_prev->key;
			dist = best_rotate_dist(dest, src, record_prev->key);
		}
		if (record_prev != record)
			record_prev = record_prev->prev;
	}
	return (val);
}

t_list	*best_insert(t_stack *dest, t_stack *src, unsigned int val)
{
	int				src_rot;
	int				dest_rot;
	unsigned int	dist;
	t_list			*op_buffer;

	src_rot = dist_from_head(src, val) % src->size;
	dest_rot = good_pos_in_stack(dest, val) % dest->size;
	dist = best_dist(dest->size, src->size, dest_rot, src_rot);
	if (dist == (unsigned int)ft_max(dest_rot, src_rot))
		op_buffer = lst_join(make_op_buffer(dest_rot, "ra"),
				make_op_buffer(src_rot, "rb"));
	else if (dist == (dest_rot + ((int)src->size - src_rot) % src->size))
		op_buffer = lst_join(make_op_buffer(dest_rot, "ra"),
				make_op_buffer(((int)src->size - src_rot) % src->size, "rrb"));
	else if (dist == ((int)dest->size - dest_rot) % dest->size + src_rot)
		op_buffer = lst_join(make_op_buffer(((int)dest->size - dest_rot)
					% dest->size, "rra"), make_op_buffer(src_rot, "rb"));
	else
		op_buffer = lst_join(make_op_buffer((dest->size - dest_rot)
					% dest->size, "rra"), make_op_buffer((src->size - src_rot)
					% src->size, "rrb"));
	if (op_buffer)
		optimize_restack(&op_buffer);
	return (op_buffer);
}

t_list	*restack(t_stack *dest, t_stack *src)
{
	unsigned int	best_val;
	t_list			*op_buffer;

	best_val = best_val_to_insert(dest, src);
	op_buffer = best_insert(dest, src, best_val);
	op_buffer = add_op_buffer(op_buffer, "pa");
	op_buffer = op_buffer->next;
	execute_op_buffer(dest, src, op_buffer);
	return (op_buffer);
}
