/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:49:36 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/24 19:17:26 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.h"
#include "includes/stack_print.h"

int    main(int ac, char **av)
{
    t_stack *a;
    t_stack *b;
    a = parse_arg(ac, av);
    if (!a)
        return (0);
    b = NULL;
    print_stack_debug(a, b);
    char *operation;
    operation = get_next_line(0);
    // b = NULL;
    ft_printf("operation: %s\n", operation);
    // op(&a, &b, operation);
    while (operation)
    {
        ft_printf("operation: %s\n", operation);
        op(&a, &b, operation);
        print_stack(a, b);
        operation = get_next_line(0);
    }
    // print_stack_debug(a, b);
    // swap_chacal(&a, &b);
    // swap_chacal(&a, &b);
    // swap(&a);
    // swap(&b);
    print_stack(a, b);
    free_stack(&a);
    free_stack(&b);
    
    return (0);
}