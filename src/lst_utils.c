/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:55:52 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 10:50:48 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
	Remove and head is the next element after remove
*/
t_list	*lst_remove(t_list *head, unsigned int to_remove)
{
	t_list			*record;
	t_list			*prev;
	unsigned int	index;

	if (!head)
		return (NULL);
	if (to_remove <= 0)
		return (head);
	record = head;
	prev = prev_op_buffer(head);
	index = 1;
	while (index < to_remove)
	{
		record = record->next;
		if (record == head)
			return (free_op_buffer(&record, NULL), NULL);
		index++;
	}
	if (record->next == head)
		return (free_op_buffer(&record, NULL), NULL);
	prev->next = record->next;
	record->next = head;
	free_op_buffer(&record, NULL);
	return (prev->next);
}

/*
	Dest_head = next elem after insert	
*/
t_list	*lst_insert(t_list *dest_head, t_list *to_insert)
{
	t_list	*record;

	if (!dest_head)
		return (to_insert);
	record = to_insert;
	while (record->next != to_insert)
		record = record->next;
	record->next = dest_head->next;
	dest_head->next = to_insert;
	return (record->next);
}

/*
	dest = next elem after insert	
*/
t_list	*lst_replace(t_list *dest, t_list *replace, unsigned int replace_size)
{
	t_list	*after_replace;

	after_replace = lst_remove(dest, replace_size);
	if (after_replace)
		after_replace = prev_op_buffer(after_replace);
	after_replace = lst_insert(after_replace, replace);
	return (after_replace);
}

/*
	dest_head point to last elem to be joined
	and
	No one care about what happend to to_join
*/
t_list	*lst_join(t_list *dest_head, t_list *to_join)
{
	t_list	*record;

	if (!to_join)
		return (dest_head);
	if (!dest_head)
		return (to_join);
	record = prev_op_buffer(to_join);
	record->next = dest_head->next;
	dest_head->next = to_join;
	return (record);
}

/*
	Concat two list and return the element after join
*/
t_list	*lst_concat(t_list *dest, t_list *src)
{
	t_list	*op_buffer;

	op_buffer = prev_op_buffer(dest);
	op_buffer = lst_join(op_buffer, src);
	op_buffer = op_buffer->next;
	return (op_buffer);
}
