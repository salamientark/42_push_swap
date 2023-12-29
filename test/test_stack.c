/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:24:46 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/29 13:50:26 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"

t_bool  stack_is_equal(t_stack_data *a, t_stack_data *b)
{
    t_stack_data *a_record;
    t_stack_data *b_record;

    if (!a && !b)
        return (TRUE);
    if (!a || !b)
        return (FALSE);
    if (a->value != b->value)
        return (FALSE);
    a_record = a->next;
    b_record = b->next;
    while(a_record != a && b_record != b)
    {
        if (a_record->value != b_record->value)
            return (FALSE);
        a_record = a_record->next;
        b_record = b_record->next;
    }
    return (a_record == a && b_record == b);
}

//  ==  
//  ==  >>> Rotate test <<< ==
//  ==  >>>     <<< ==
//  ==  >>>     <<< ==
//  ==  >>>     <<< ==
//  ==  >>>     <<< ==
//  ==  >>>     <<< ==