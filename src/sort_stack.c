/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 20:18:42 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/29 13:50:26 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/*
    Point of this is to make stack sort easier by having only
    easy to use value.
    [ 458, 98526, 2, 1156, 42, 666]
     ===> Become
    [ 3, 6, 1, 5, 2, 4]
*/

// 5 2 3 1 4
// BEST : ra ra sa rra sa
// Swap when not ordered

// 2 3 1 5 4
// BEST : pb pb sa rra pa pa rra
// push to b when no link
// Find a way to rotate a to good pos

// 1 2 4 5 3
// BEST : pb rra sa pa
// --
//  pb   -> NO link && Broke ctual link to create new one
//  rra  -> follow(first, last) == -1 <=> swap(first, last)
//  sa   -> 
//  pa   -> a sorted && follow(b_head, a_head)

// 5 1 3 4 2
// BEST         :   rra sa ra sa
// MOST_LIKELY  :   pb rra sa pa ra

// 3 4 5 2 1
// BEST : rra rra sa
// MOST_LIKELY : pb pb pb sa pa pa pa

// 3 4 2 1 5 
// BEST : rra rra sa rra sa ra sa
//      : pb rra sa pa rra rra sa

// 1 5 3 2 4
// BEST : pb ra sa pa 
// MOST_LIKELY : 

// 4 2 1 3 5
// BEST : rra sa ra ra sa 

// 1 3 4 2 5
// BEST : rra rra sa ra sa 
// --
//  rra -> Pushing back
//  rra -> 
//  sa  -> follow(second, last)
//  ra  -> Push forward
//  sa  ->

// 1 5 4 2 3
// BEST  : pb sa ra ra pa
// NO_PB : sa ra sa rra sa ra ra
// --

// 1 4 3 2 5
// BEST : ra sa ra sa rra sa rra
// --
//  ra  -> follow 1 + link
//  sa  -> 
//  ra  -> 

// 4 2 1 5 3
// BEST  : ra sa pb sa ra pa
// NO_PB : ra sa (Put aftter sorted block at the beginning) ra sa rra sa (Best rotate) ra

// 2 4 5 3 1
// BEST : rra rra sa ra sa rra
// --
//  rra -> Push back
//  rra -> Push_back
//  sa  -> Bring first number back
//  ra  ->
//  sa  -> 
//  rra -> best rotate



// 5 3 4 2 1
// BEST    : sa ra sa ra ra sa
// --
//  sa  -> We are trying to bring 5 to the end of sorted block
//  ra  -> We are trying to bring 5 to the end of sorted block
//  sa  -> We are trying to bring 5 to the end of sorted block
//  ra  -> We are trying to bring 5 to the end of sorted block
//  ra  -> Now block is sorted, we rotate to the end
//  sa  -> 



// 5 1 6 4 3 2
// BEST : sa rra sa pb rra sa pb rra sa pa pa
// --
//  sa  -> follow(first, first->next->next) <=> after swap, second and third follow
//  rra -> Instead of pb because swap_follow(first && last)
//  sa  -> 
//  pb  -> No link && follow(first, first->next)
//  rra -> instead of pb because swap_follow(first && last)
//  sa  ->
//  pb  -> Priority: follow(a.first, b.first), Also  No link && follow(first, first->next)
//  rra -> instead of pb because swap_follow(first && last)
//  pa  -> a_sorted && b_sorted <=> Join stack
//  pa  -> a_sorted && b_sorted <=> Join stack


static char *best_rotate(int rot, int size)
{
    if (rot > size / 2)
        return ("rra\n");
    else
        return ("ra\n");
}

void    sort_stack_data_3(t_stack *stack)
{
    int sorted;

    sorted = a_sorted(stack->head, stack->size);
    while (sorted != 0)
    {
        if (sorted > 0)
            operation(stack, NULL, best_rotate(sorted, stack->size));
        else
            operation(stack, NULL, "sa\n");
        sorted = a_sorted(stack->head, stack->size);
    }
}

void    sort_stack_data_5(t_stack *stack_a)
{
    int sorted;

    if (r_sorted(stack_a->head, stack_a->size))
        operation(stack_a, NULL, "sa\n");
    sorted = a_sorted(stack_a->head, stack_a->size);
    while (sorted != 0)
    {
        if (sorted > 0)
            operation(stack_a, NULL, best_rotate(sorted, 5));
        else if (follow(stack_a->head, stack_a->head->next, 5) == 1)
            operation(stack_a, NULL, "ra\n");
        else if (follow(stack_a->head->prev, stack_a->head->next, 5) == 1
            && follow(stack_a->head->prev, stack_a->head, 5) != 1)
            operation(stack_a, NULL, "sa\n");
        else if (follow(stack_a->head->prev, stack_a->head, 5) == -1)
            operation(stack_a, NULL, "rra\n");
        else if (follow(stack_a->head, stack_a->head->next->next, 5)
            && !(follow(stack_a->head->next, stack_a->head->next->next->next, 5)))
            operation(stack_a, NULL, "sa\n");
        else if (follow(stack_a->head->prev, stack_a->head, 5) == 1)
            operation(stack_a, NULL, "ra\n");
        else if (follow(stack_a->head, stack_a->head->next, 5) == -1)
            operation(stack_a, NULL, "sa\n");
        else
            operation(stack_a, NULL, "ra\n");
        sorted = a_sorted(stack_a->head, stack_a->size);
    }
}

// void    b_analyze_a(t_stack_data **a, t_stack_data **b)
// {
//     if ()
// }

/*  Anayze different situation for swap
        Second_follow_first     (Second  -> First)=> rotate
        r_second_follow_first   (Second  <- First)=> swap

        first_follow_last       (First  -> Last)  => r ?   <= !First.block
        r_first_follow_last     (First  <- Last)  => rr

        second_follow_last      (Second -> Last)  => swap  <= !First.block
        r_second_follow_last    (Second <- Last)  => swap ?<= !First.block

        third_follow_first      (Third  -> First) => swap ?<= !First.block
        r_third_follow_first      (Third  <- First) => swap ?<=!First.block
*/
// int swap_analyze(t_stack_data **stack)
// {

// }