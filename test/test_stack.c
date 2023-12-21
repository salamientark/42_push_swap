/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:24:46 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/21 01:26:10 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"

t_bool  stack_is_equal(t_stack *a, t_stack *b)
{
    t_stack *a_record;
    t_stack *b_record;

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