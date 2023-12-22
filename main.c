/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:49:36 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/22 22:05:18 by dbaladro         ###   ########.fr       */
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
    print_stack(a, NULL);

    // print_stack_debug(a, b);
    // swap(&a);
    // print_stack(a, b);

    b = NULL;
    push(&a, &b);
    push(&a, &b);
    print_stack(a, b);
    
    swap_chacal(&a, &b);
    // swap(&a);
    print_stack_debug(a, b);
    print_stack(a, b);

    swap(&a);
    swap(&b);
    print_stack(a, b);
    
    return (0);
}