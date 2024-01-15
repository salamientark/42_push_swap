/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:11:55 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/15 15:41:47 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"

static void	free_push_swap(t_push_swap_env *ps_env, t_list **operation_buffer)
{
	free_op_buffer(operation_buffer, NULL);
	free_stack_data(&((*ps_env).stack_a.head));
	free_stack_data(&((*ps_env).stack_b.head));
}

// static void    print_op_buffer(t_list *op_buffer)
// {
//     t_list  *head;

// 	if (!op_buffer)
// 		return ;
//     head = op_buffer->next;
//     while (head != op_buffer)
//     {
//         ft_putendl_fd(head->content, 1);
//         head = head->next;
//     }
//     ft_putendl_fd(head->content, 1);
// }

int	operation(t_stack *a, t_stack *b, char *op)
{
	t_operation	op_env;

	op_env.arg_a = a;
	op_env.arg_b = NULL;
	if (op && op[0] == 's')
		op_env.operation = &swap;
	else if (op && op[0] == 'p')
		op_env.operation = &push;
	else if (op && op[0] == 'r' && ft_strlen(op) == 2)
		op_env.operation = &rotate;
	else if (op && op[0] == 'r' && ft_strlen(op) == 3)
		op_env.operation = &r_rotate;
	else
		return (0);
	if (op_env.operation == &push || (op[1] == 'r' && !op[2])
			|| (op[2] && op[2] == 'r') || op[1] == 's')
		op_env.arg_b = b;
	if (op[1] == 'b' || (ft_strlen(op) == 3 && op[2] == 'b'))
	{
		op_env.arg_a = b;
		if (op_env.operation == &push)
			op_env.arg_b = a;
	}
	op_env.operation(op_env.arg_a, op_env.arg_b);
	return (1);
}

// static void	free_list(char ***p_list)
// {
// 	char	**list;
// 	int		index;

// 	list = *p_list;
// 	index = 0;
// 	while (list[index])
// 	{
// 		free(list[index]);
// 		list[index] = NULL;
// 		index++;
// 	}
// 	free(*p_list);
// 	*p_list = NULL;
// }

// static int	arg_is_valid(t_stack_data *stack, int val, char *s_val)
// {
// 	t_stack_data	*stack_cp;
// 	char			*val_to_str;
// 	int				is_valid;

// 	if (!ft_isnumber(s_val))
// 		return (0);
// 	val_to_str = ft_itoa(val);
// 	if (!val_to_str)
// 		return (0);
// 	is_valid = ft_strcmp(s_val, val_to_str);
// 	free(val_to_str);
// 	if (is_valid != 0)
// 		return (0);
// 	if (!stack)
// 		return (1);
// 	if (stack->next == stack && stack->value != val)
// 		return (1);
// 	stack_cp = stack->next;
// 	while (stack_cp != stack)
// 	{
// 		if (stack_cp->value == val)
// 			return (0);
// 		stack_cp = stack_cp->next;
// 	}
// 	return (stack_cp->value != val);
// }

// static t_stack	make_stack(char **arg, int size)
// {
// 	t_stack			stack;
// 	int				tmp_value;

// 	stack = init_stack('a');
// 	if (size == 0)
// 		return (stack);
// 	stack.size = size;
// 	stack.min = 1;
// 	stack.max = size;
// 	while (size-- > 0)
// 	{
// 		tmp_value = ft_atoi(arg[size]);
// 		if (!arg_is_valid(stack.head, tmp_value, arg[size]))
// 		{
// 			ft_putendl_fd("Error", 2);
// 			if (stack.head)
// 				free_stack_data(&stack.head);
// 			stack.size = 0;
// 			return (stack);
// 		}
// 		stack.head = add_stack_data(tmp_value, stack.head);
// 	}
// 	return (stack);
// }


// static t_stack	parse_arg(int ac, char **av)
// {
// 	char	**av_one_arg;
// 	int		size;
// 	t_stack	stack_a;

// 	if (ac <= 1)
// 		return (init_stack('a'));
// 	if (ac == 2)
// 	{
// 		av_one_arg = ft_split(av[1], ' ');
// 		size = 0;
// 		while (av_one_arg[size])
// 			size++;
// 		if (size == 0)
// 			return (stack_a);
// 		stack_a = make_stack(av_one_arg, size);
// 		free_list(&av_one_arg);
// 		return (stack_a);
// 	}
// 	return (make_stack(&(av[1]), ac - 1));
// }

void    push_swap(int ac, char **av)
{
	t_push_swap_env	ps_env;
    t_list  		*operation_buffer;

	operation_buffer = NULL;
	ps_env = init_push_swap(ac, av);
    if (!(ps_env.stack_a.head))
	{
		free_push_swap(&ps_env, &operation_buffer);
		return ;
	}
	// print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
	// t_stack test_a = parse_arg(ac, av);
	// t_stack test_b = init_stack('b');
	
	if (ps_env.stack_a.size <= 5)
	{
		operation_buffer = sort_small_stack(&(ps_env.stack_a), ps_env.max_size);
		// print_op_buffer(operation_buffer);
		free_push_swap(&ps_env, &operation_buffer);
		return ;
	}
	if (ps_env.stack_a.size > 5)
	{
		// ft_printf("AFTER_UNSTACK\n");
		operation_buffer = unstack_a(&(ps_env.stack_a), &(ps_env.stack_b));
		
		// print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
		// ft_printf("--- TEST ---\n");
		// test_a = parse_arg(ac, av);
		// test_b = init_stack('b');
		// execute_op_buffer(&test_a, &test_b, operation_buffer);
		// print_op_buffer(operation_buffer);
		// print_stack_data(test_a.head, test_b.head, &get_elem_key);
	
		while (ps_env.stack_a.size > 5)
		{
			operation_buffer = prev_op_buffer(operation_buffer);
			operation_buffer = lst_join(operation_buffer, unstack_a(&(ps_env.stack_a), &(ps_env.stack_b)));
			operation_buffer = operation_buffer->next;
		}
		// print_stack_data(ps_env.stack_a.head, ps_env.stack_b.head, &get_elem_key);
		// ft_printf("AFTER_SORT_SMALL_STACK\n");
		operation_buffer = prev_op_buffer(operation_buffer);
		operation_buffer = lst_join(operation_buffer, sort_small_stack(&(ps_env.stack_a), ps_env.stack_a.size));
		operation_buffer = operation_buffer->next;
		
		// print_stack_data(ps_env.stack_a.head, ps_env.stack_b.head, &get_elem_key);
		// ft_printf("--- TEST ---\n");
		// test_a = parse_arg(ac, av);
		// test_b = init_stack('b');
		// execute_op_buffer(&test_a, &test_b, operation_buffer);
		// print_op_buffer(operation_buffer);
		// print_stack_data(test_a.head, test_b.head, &get_elem_key);
		// print_stack_data(ps_env.stack_a.head, ps_env.stack_b.head, &get_elem_key);

		
			// print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);

		// ft_printf("Nbr Coup UNSTACK = %d\n", op_buffer_size(operation_buffer));
		// print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, print_stack_data);
		// print_op_buffer(operation_buffer);
		// ft_printf("\nbest restack:\n");
		// ft_printf("AFTER_RESTACK\n");
		while (ps_env.stack_a.size < ps_env.max_size)
		{
			operation_buffer = prev_op_buffer(operation_buffer);
			operation_buffer = lst_join(operation_buffer, best_move(&(ps_env.stack_a), &(ps_env.stack_b)));
			operation_buffer = operation_buffer->next;
		}
		
		// print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
		// ft_printf("--- TEST ---\n");
		// test_a = parse_arg(ac, av);
		// test_b = init_stack('b');
		// execute_op_buffer(&test_a, &test_b, operation_buffer);
		// print_op_buffer(operation_buffer);
		// print_stack_data(test_a.head, test_b.head, &get_elem_key);
		while (!(ps_env.stack_a.head->key == 1))
		{
			operation_buffer = prev_op_buffer(operation_buffer);
			operation_buffer = add_op_buffer(operation_buffer, best_a_rotate(a_sorted(&(ps_env.stack_a)), ps_env.stack_a.size));
			operation(&(ps_env.stack_a), &(ps_env.stack_b), operation_buffer->content);
			operation_buffer = operation_buffer->next;
			// print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
		}
		// print_op_buffer(operation_buffer);
		// ft_printf("SORTED\n");
		// print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
 		// ft_printf("FINAL OP_BUFFER\n");
		// print_op_buffer(operation_buffer);
		// ft_printf("--- TEST ---\n");
		// test_a = parse_arg(ac, av);
		// test_b = init_stack('b');
		// execute_op_buffer(&test_a, &test_b, operation_buffer);
		print_op_buffer(operation_buffer);
		// print_stack_data(test_a.head, test_b.head, &get_elem_key);
		// print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
		// ft_printf("Nbr Coup TOTAUX= %d\n", op_buffer_size(operation_buffer));
		free_push_swap(&ps_env, &operation_buffer);
		return ;
	}
	free_push_swap(&ps_env, &operation_buffer);
}
