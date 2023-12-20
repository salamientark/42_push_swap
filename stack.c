/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:44:36 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/20 11:07:18 by dbaladro         ###   ########.fr       */
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
t_stack    *remove(t_stack **top)
{
    t_stack *elem;
    t_stack *removed_top;

    if (!(*top) || (*top)->next == (*top))
        return (*top);
    removed_top = *top;
    elem = (*top)->prev;
    elem->next = (*top)->next;
    elem = (*top)->next;
    elem->prev = (*top)->prev;
    removed_top->next = NULL;
    removed_top->prev = NULL;
    (*top) = elem;
    return (removed_top);
}

// void    push(t_stack **dest,t_stack **src)
// {
//     t_stack *elem;
//     t_stack *tmp;

//     if (!(*src) || (*src)->next == (*src))
//         return ;
//     elem = (*src);
//     tmp = (*src)->next;
//     tmp->prev = (*src)->prev;
//     (tmp->prev)->next = tmp;
//     // tmp = (*src)->prev;
//     // tmp->next = (*src)->next;

//     *src = tmp;
//     if (!(*dest))
//     {
//         elem->next = elem;
//         elem->prev = elem;
//         (*dest) = elem;;
//     }
//     else if ((*dest)->next == (*dest))
//     {
//         (*dest)->next = elem;
//         (*dest)->prev = elem;
//         elem->next = (*dest);
//         elem->prev = (*dest);
//         (*dest) = elem;
//     }
//     else
//     {
//         tmp = (*dest)->prev;
//         tmp->next = (*src);
//         // ((*dest)->prev)->next = (*src);
//         ((*dest)->next)->prev = (*src);
//         tmp = (*src)->prev;
//         tmp->next = (*src)->next;
//         tmp = tmp->next;
//         tmp = (*src)->next;
//         tmp->prev = (*src)->prev;
//         (*src)-
//     }
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
// t_stack *rotate(t_stack *stack)
// {
//     if (!stack)
//         return (NULL);
//     return (stack->next);
// }

void    rotate(t_stack **stack)
{
    if (*stack)
        *stack = (*stack)->next;
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
// t_stack *swap(t_stack *top)
// {
//     t_stack *new_head;
//     t_stack *tmp;

//     if (!top || top->next == top)
//         return (top);
//     new_head = top->next;
//     tmp = top->prev;
//     top->next = new_head->next;
//     top->prev = new_head;
//     new_head->next = top;
//     new_head->prev = tmp;
//     tmp->next = new_head;
//     tmp = top->next;
//     tmp->prev = top;
//     return (new_head);
// }

void    swap(t_stack **top)
{
    t_stack *new_head;
    t_stack *tmp;

    if (!(*top) || (*top)->next == *top)
        return ;
    new_head = (*top)->next;
    tmp = (*top)->prev;
    (*top)->next = new_head->next;
    (*top)->prev = new_head;
    new_head->next = (*top);
    new_head->prev = tmp;
    tmp->next = new_head;
    tmp = (*top)->next;
    tmp->prev = (*top);
    *top = new_head;
}
