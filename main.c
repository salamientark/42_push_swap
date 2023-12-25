/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:49:36 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/25 15:41:47 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.h"
#include "includes/stack_print.h"

// static void free_push_swap(t_stack **stack_a, t_stack **stack_b, char **op_str)
// {
//     if (op_str)
//         free(op_str);
//     free_printf_param();
//     free_stack(stack_a);
//     free_stack(stack_b);
// }

int    main(int ac, char **av)
{
    t_stack *a;
    t_stack *b;
    char *op_str;

    b = NULL;
    a = parse_arg(ac, av);
    if (!a)
        return (0);
    print_stack(a, b);
    ft_printf("enter operation : ");
    op_str = get_next_line(0);
    while (operation(&a, &b, op_str))
    {
        print_stack(a, b);
        ft_printf("enter operation : ");
        if (op_str != NULL)
        {
            free(op_str);
            op_str = NULL;
        }
        op_str = get_next_line(0);
    }
    if (op_str)
        free(op_str);
    free_printf_param();
    free_stack(&a);
    free_stack(&b);
    return (0);
}