/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:49:57 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/04 12:12:05 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

void free_op_buffer(t_list **list, void (*free_content)(void *))
{
    t_list *end;
    t_list *tmp;

    if (!(*list))
        return ;
    end = (*list)->next;
    while (end != *list)
    {
        tmp = end->next;
        if (free_content)
            free_content(end->content);
        end->content = NULL;
        free(end);
        end = NULL;
        end = tmp;
    }
    if (free_content)
            free_content(end->content);
    end->content = NULL;
    free(end);
    end = NULL;
    *list = NULL;
}

t_list  *init_op_buffer(char *op)
{
    t_list *new_list;

    if (!op)
        return (NULL);
    new_list = (t_list *)malloc(sizeof(struct s_list));
    if (!new_list)
        return (NULL);
    new_list->next = new_list;
    new_list->content = op;
    return (new_list);
}

t_list  *add_op_buffer(t_list *op_buffer, char *op)
{
    t_list *new_elem;

    new_elem = init_op_buffer(op);
    if (!new_elem)
    {
        free_op_buffer(&op_buffer, NULL);
        return (NULL);
    }
    if (!op_buffer)
        return (new_elem);
    new_elem->next = op_buffer->next;
    op_buffer->next = new_elem;
    return (new_elem);
}