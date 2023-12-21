/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:49:36 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/21 15:36:15 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.h"
#include "includes/stack_print.h"

int    main(int ac, char **av)
{
    // t_stack *a = add_stack(1, NULL);
    t_stack *a = parse_arg(ac, av);
    if (!a)
        return (0);
    // t_stack *b = add_stack(4, NULL);

    // a = add_stack(2, a);
    // a = add_stack(3, a);
    print_stack(a, NULL);

    // rotate(&a);
    // print_stack(a, b);

    // print_stack_debug(a, b);
    // swap(&a);
    // print_stack(a, b);

    // push(&a, &b);
    // push(&a, &b);
    // print_stack_debug(a, b);
    // print_stack(a, b);

    // push(&b, &a);
    // push(&b, &a);
    // print_stack_debug(a, b);
    // print_stack(a, b);
    
    return (0);
}