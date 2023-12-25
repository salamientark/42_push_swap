/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:49:36 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/25 09:20:48 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.h"
#include "includes/stack_print.h"

int    main(int ac, char **av)
{
    t_stack *a;
    t_stack *b;
    char *op_str;

    b = NULL;
    a = parse_arg(ac, av);
    if (!a)
        return (0);
    print_stack_debug(a, b);
    ft_printf("enter operation : ");
    op_str = get_next_line(0);
    while (op_str)
    {
        operation(&a, &b, op_str);
        print_stack(a, b);
        ft_printf("enter operation : ");
        op_str = get_next_line(0);
    }
    print_stack(a, b);
    free_stack(&a);
    free_stack(&b);    
    return (0);
}