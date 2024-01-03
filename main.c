/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:49:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/03 08:10:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.h"
#include "includes/stack_print.h"

// static void free_push_swap(t_stack_data **stack_a, t_stack_data **stack_b, char **op_str)
// {
//     if (op_str)
//         free(op_str);
//     free_printf_param();
//     free_stack_data(stack_a);
//     free_stack_data(stack_b);
// }

int    main(int ac, char **av)
{
    char    *op_str;
    int     index;

    // op_str = NULL;
    t_push_swap_env ps_env;
    
    ps_env = init_push_swap(ac, av);
    if (!(ps_env.stack_a.head))
        return (0);
    // print_ps_env(&ps_env);
    // print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);

    if (ps_env.max_size == 3)
    {
        sort_stack_data_3(&(ps_env.stack_a));
        // print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
        return (0);
    }
    if (ps_env.max_size == 5)
    {
        sort_stack_data_5(&(ps_env.stack_a), &(ps_env.stack_b));
        // print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
        return (0);
    }
    
    if (a_sorted(ps_env.stack_a.head, ps_env.stack_a.size) == 0)
        return (0);
    ft_printf("enter operation : ");
    op_str = get_next_line(0);
    index = 0;
    while (operation(&(ps_env.stack_a), &(ps_env.stack_b), op_str) && a_sorted(ps_env.stack_a.head, ps_env.stack_a.size) != 0)
    {
        index++;
        // operation(&(ps_env.stack_a.head), &(ps_env.stack_b.head), op_str);
        print_stack_data(ps_env.stack_a.head, ps_env.stack_b.head, &get_elem_key);
        ft_printf("enter operation : ");
        if (op_str != NULL)
        {
            free(op_str);
            op_str = NULL;
        }
        op_str = get_next_line(0);
    }
    print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
    ft_printf("\nNbr de coup = %d\n", index);
    free_printf_param();
    // print_stack_data(a, b, &get_stack_data_value);
    if (op_str)
        free(op_str);
    free_printf_param();
    free_stack_data(&(ps_env.stack_a.head));
    free_stack_data(&(ps_env.stack_b.head));
    return (0);
}