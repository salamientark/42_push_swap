/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:49:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/05 09:36:31 by dbaladro         ###   ########.fr       */
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

    push_swap(ac, av);

    // (void) ac;
    // (void) av;
    // t_list *l = add_op_buffer(NULL, "ra");
    // l = add_op_buffer(l, "ra");
    // l = add_op_buffer(l, "ra");
    // l = add_op_buffer(l, "ra");
    // l = add_op_buffer(l, "pa");

    // print_op_buffer(l);
    // l = lst_replace(l, make_op_buffer(5, "bbb"), 1);
    // print_op_buffer(l);

    // free_op_buffer(&l, NULL);


    // char    *op_str;
    // int     index;
    // t_push_swap_env ps_env;
    
    // ps_env = init_push_swap(ac, av);
    // if (!(ps_env.stack_a.head))
    //     return (0);
    // print_ps_env(&ps_env);
    // print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
    // if (a_sorted(ps_env.stack_a.head, ps_env.stack_a.size) == 0)
    //     return (0);
    // ft_printf("enter operation : ");
    // op_str = get_next_line(0);
    // index = 0;
    // while (!(is_sorted(&(ps_env.stack_a)) == 1 && ps_env.stack_a.head->key == 1
    //     && ps_env.stack_a.size == ps_env.max_size))
    // {
    //     index++;
    //     index += operation(&(ps_env.stack_a), &(ps_env.stack_b), op_str);
    //     print_stack_data(ps_env.stack_a.head, ps_env.stack_b.head, &get_elem_key);
    //     ft_printf("enter operation : ");
    //     if (op_str != NULL)
    //     {
    //         free(op_str);
    //         op_str = NULL;
    //     }
    //     op_str = get_next_line(0);
    // }
    // print_stack(ps_env.stack_a, ps_env.stack_b, &get_elem_key, &print_stack_data);
    // ft_printf("\nNbr de coup = %d\n", index);
    // free_printf_param();
    // if (op_str)
    //     free(op_str);
    // free_printf_param();
    // free_stack_data(&(ps_env.stack_a.head));
    // free_stack_data(&(ps_env.stack_b.head));
    return (0);
}