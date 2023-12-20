/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:44:36 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/20 01:33:10 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "stack.h"

// Init doubly rotary linked list
t_stack *init_stack(const int value)
{
    t_stack *stack;

    stack = (t_stack *)malloc(sizeof(struct s_stack));
    if (!stack)
        return (NULL);
    stack->value = value;
    stack->next = stack;
    stack->prev = stack;
    return (stack);
}

t_stack *add_stack(const int val, t_stack *stack)
{
    t_stack *elem;

    elem = (t_stack *)malloc(sizeof(struct s_stack));
    if (!elem)
        return (NULL);
    elem->value = val;
    if (!stack)
    {
        elem->next = elem;
        elem->prev = elem;
    }
    else
    {
        elem->prev = stack->prev;
        elem->next = stack;
        if (stack->next == stack)
            stack->next = elem;
        (elem->prev)->next = elem;
        stack->prev = elem;
    }
    return (elem);
}

// DELETE ELEM FROM STACK IF EXIST
t_stack *delete(t_stack *top)
{
    t_stack *tmp;

    if (!top)
        return (NULL);
    if (top->next == top)
    {
        free(top);
        top = NULL;
        return (top);
    }
    tmp = top->prev;
    tmp->next = top->next;
    tmp = tmp->next;
    tmp->prev = top->prev;
    free(top);
    top = tmp->prev;
    return top;
}

// Remove without free
//  Do nothing if no stack or one element only
// void    remove(t_stack *stack)
// {
//     t_stack *elem;

//     if (!stack || stack->next == stack)
//         return ;
//     elem = stack->prev;
//     elem->next = stack->next->next;
//     elem = stack->next;
//     elem->prev = stack->prev->prev;
//     stack->next = stack;
//     stack->prev = stack;
//     stack = elem->prev;
//     return ;
// }

// // Find the element containing value
// //  if exist remove it
// void    remove_val(t_stack *stack, const int value)
// {
//     t_stack *elem;

//     if (!stack)
//         return ;
//     if (stack->next == stack)
//         return(delete(stack));
//     elem = stack->next;
//     while (elem != stack)
//     {
//         if (elem->value == value)
//             return (delete(elem));
//         elem = elem->next;
//     }
//     return ;
// }

// rotate
t_stack *rotate(t_stack *stack)
{
    if (!stack)
        return (NULL);
    return (stack->next);
}

// Reverse rotate
t_stack *rev_rotate(t_stack *stack)
{
    if (!stack)
        return (NULL);
    return (stack->prev);
}

// REMOVE FIRST FROM DEST AND ADD TO SRC
// t_stack *push(t_stack *dest, t_stack *src)
// {
//     t_stack *tmp;

//     if (!src)
//         return (dest);
//     if (src->next != src)
//     {
//         tmp = dest->prev;
//         tmp->next = src;
//         src->prev = dest->prev;
//         dest->prev = src;
//         tmp = src->
//         (dest->prev)->next = dest->next;
//         (dest->next)->prev = dest->prev;
//     }
//     dest->prev = src->prev;
//     dest->next = src;
//     src = dest;
//     return (src);
// }

// Swap the two first element of the stack
t_stack *swap(t_stack *top)
{
    t_stack *new_head;
    t_stack *tmp;

    if (!top || top->next == top)
        return (top);
    new_head = top->next;
    tmp = top->prev;
    top->next = new_head->next;
    top->prev = new_head;
    new_head->next = top;
    new_head->prev = tmp;
    tmp->next = new_head;
    tmp = top->next;
    tmp->prev = top;
    return (new_head);
}
