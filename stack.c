/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:44:36 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/24 13:40:51 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.h"

void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	if (!(*stack))
		return ;
	tmp = (*stack)->next;
	(*stack)->prev->next = NULL;
	while (tmp)
	{
		free(tmp->prev);
		tmp = tmp->next;
	}
	*stack = NULL;
}

// Init doubly rotary linked list
t_stack	*init_stack(const int value)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(struct s_stack));
	if (!stack)
		return (NULL);
	stack->value = value;
	stack->next = stack;
	stack->prev = stack;
	return (stack);
}

t_stack	*add_stack(const int val, t_stack *stack)
{
	t_stack	*elem;

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
t_stack	*delete(t_stack *top)
{
	t_stack	*tmp;

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
	return (top);
}

// Remove without free
//  Do nothing if no stack or one element only
t_stack	*remove(t_stack **top)
{
	t_stack	*elem;
	t_stack	*removed_top;

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

void	rotate(t_stack **stack)
{
	if (*stack)
		*stack = (*stack)->next;
}

// Reverse rotate
void	r_rotate(t_stack **stack)
{
	if (*stack)
		*stack = (*stack)->prev;
}

void	swap(t_stack **top)
{
	t_stack	*new_top;

	if (!(*top) || (*top)->next == *top)
		return ;
	new_top = (*top)->next;
	if (new_top->next != *top)
	{
		(*top)->next = new_top->next;
		new_top->prev = (*top)->prev;
		(*top)->prev = new_top;
		new_top->next = (*top);
		(*top)->next->prev = (*top);
		new_top->prev->next = new_top;
	}
	(*top) = new_top;
}

void	push(t_stack **src, t_stack **dest)
{
	t_stack	*elem;

	if (!(*src))
		return ;
	elem = *src;
	if (elem != elem->next)
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
		*src = elem->next;
	}
	if (elem == elem->next)
		*src = NULL;
	if (!(*dest))
		(*dest) = elem;
	elem->prev = (*dest)->prev;
	elem->next = (*dest);
	if ((*dest) == (*dest)->next)
		(*dest)->next = elem;
	else
		((*dest)->prev)->next = elem;
	(*dest)->prev = elem;
	*dest = elem;
}
