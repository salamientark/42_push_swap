/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_chacal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:39:24 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/24 23:02:01 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

#include "includes/stack_print.h"

/*	Description
		Chacal version make all function with two arg
		to make a "one call recursvie" kind of function
	Exemple :
		func_chacal(a, b) = func(a) + func(b)
	This often implies a call with of func_chacal(a, NULL)
	to stop the function
*/

void	rotate_chacal(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a)
		*stack_a = (*stack_a)->next;
	if (stack_b && *stack_b)
		rotate_chacal(stack_b, NULL);
}

// Reverse rotate_chacal
void	r_rotate_chacal(t_stack **stack_a, t_stack **stack_b)
{
	if (*stack_a)
		*stack_a = (*stack_a)->prev;
	if (stack_b && *stack_b)
		r_rotate_chacal(stack_b, NULL);
}

void	swap_chacal(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*new_top;

	if (!(*stack_a) || (*stack_a)->next == *stack_a)
		return ;
	new_top = (*stack_a)->next;
	if (*stack_a != new_top->next)
	{
		(*stack_a)->next = new_top->next;
		new_top->prev = (*stack_a)->prev;
		(*stack_a)->prev = new_top;
		new_top->next = (*stack_a);
		(*stack_a)->next->prev = (*stack_a);
		new_top->prev->next = new_top;
	}
	(*stack_a) = new_top;
	if (!stack_b)
		return ;
	swap_chacal(stack_b, NULL);
}

typedef struct s_operation
{
	t_stack	**arg_a;
	t_stack	**arg_b;
	void	(*operation)(t_stack **, t_stack **);
}				t_operation;

void	print_operation(t_operation op)
{
	ft_printf("=== PRINT_OPERATION ===\n");
	ft_printf("| ");
	if (!op.arg_a || !(*op.arg_a))
	{
		ft_printf("op.arg_a = NULL | ");
		return ;
	}
	if (!(*op.arg_a))
		ft_printf("*op.arg_a = NULL | ");
	if (!op.arg_b)
		ft_printf("op.arg_b = NULL | ");
	if (!(*op.arg_b))
		ft_printf("*op.arg_b = NULL |");
	ft_printf("\n");
	ft_printf("op.operation = %p\n", op.operation);
}

void	op(t_stack **a, t_stack **b, char *op)
{
	t_operation	op_env;

	op_env.arg_a = a;
	if (op[0] == 's')
		op_env.operation = &swap_chacal;
	else if (op[0] == 'p')
		op_env.operation = &push;
	else if (op[0] == 'r' && ft_strlen(op) == 2)
		op_env.operation = &rotate_chacal;
	else
		op_env.operation = &r_rotate_chacal;
	if (op_env.operation != &push)
		op_env.arg_b = NULL;
	else
		op_env.arg_b = b;
	if (op[1] == 'b' || (ft_strlen(op) == 3 && op[2] == 'b'))
	{
		op_env.arg_a = b;
		if (op_env.operation == &push)
			op_env.arg_b = a;
	}
	op_env.operation(op_env.arg_a, op_env.arg_b);
}

void	operation(t_stack **a, t_stack **b, char *op)
{
	if (ft_strncmp(op, "sa", 4) == 0 || ft_strncmp(op, "ss", 0) == 0)
		swap(a);
	if (ft_strncmp(op, "sb", 4) == 0 || ft_strncmp(op, "ss", 0) == 0)
		swap(b);
	if (ft_strncmp(op, "ra", 4) == 0 || ft_strncmp(op, "rr", 0) == 0)
		rotate(a);
	if (ft_strncmp(op, "rb", 4) == 0 || ft_strncmp(op, "rr", 0) == 0)
		rotate(b);
	if (ft_strncmp(op, "rra", 4) == 0 || ft_strncmp(op, "rrr", 4) == 0)
		r_rotate(a);
	if (ft_strncmp(op, "rrb", 4) == 0 || ft_strncmp(op, "rrr", 4) == 0)
		r_rotate(b);
	if (ft_strncmp(op, "pa", 4) == 0)
		push(a, b);
	if (ft_strncmp(op, "pb", 4) == 0)
		push(b, a);
	else
		(void)ft_printf("Bug");
}
