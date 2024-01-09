/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:39:49 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/09 16:13:01 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/*
    dest_head point to last elem ot be joined
    and
    No one care about what happend to to_join
*/
t_list  *lst_join(t_list *dest_head, t_list *to_join)
{
    t_list *record;

    if (!to_join)
        return (dest_head);
    if (!dest_head)
        return (to_join);
    record = prev_op_buffer(to_join);
    record->next = dest_head->next;
    dest_head->next = to_join;
    return (record);
}