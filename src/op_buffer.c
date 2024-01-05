/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:49:57 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/05 10:12:34 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"

unsigned int op_buffer_size(t_list *op_buffer)
{
    unsigned int    size;
    t_list          *record;

    if (!op_buffer)
        return (0);
    size = 1;
    record = op_buffer->next;
    while (record != op_buffer)
    {
        size++;
        record = record->next;
    }
    return (size);
}

t_list  *lst_remove(t_list *head, unsigned int to_remove)
{
    t_list          *record;
    t_list          *prev;
    unsigned int    index;

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

t_list  *lst_insert(t_list *dest_head, t_list *to_insert)
{
    t_list  *record;

    if (!dest_head)
        return (to_insert);
    record = to_insert;
    while (record->next != to_insert)
        record = record->next;
    record->next = dest_head->next;
    dest_head->next = to_insert;
    return (record->next);
}

t_list  *lst_replace(t_list *dest, t_list *replace, unsigned int replace_size)
{
    t_list  *after_replace;

    after_replace = lst_remove(dest, replace_size);
    if (after_replace)
        after_replace = prev_op_buffer(after_replace);
    after_replace = lst_insert(after_replace, replace);
    return (after_replace);
}