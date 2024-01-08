/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_unstack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:41:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/08 20:02:42 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"

/*  Int map of every operation between 2 push operation;
    This map contain the swap / rotate / r_rotate operation saved like this :
        r_rotate : saved as negative value (rra, rra, rra => -3)
        rotate   : saved as positive value (ra, ra, ra, ra => 4)
        swap     : saved as new index in map (sa, ra, ra, sa, pb => [0, 2, 0])
    Return :
        int *map :  Value   : Every ra or rra before and after swaps
        int size :  Size    : (Nbr of swap + 1)
    Exemple :
        (pb, pb) => [0]
        (pb, sa, pb) => [0, 0]
        (pb, ra, ra, sa, rra, sa, ra, pb) => [2, -1, 1]
        (pb, sa, ra, ra, sa) => [0, 3, 0]
    */
typedef struct s_swap_rotate_map
{
    int *map;
    int size;
}               t_swap_rotate_map;

void    print_sr_map(t_swap_rotate_map sr_map)
{
    int index;

    index = 0;
    ft_printf("[");
    while (index < sr_map.size)
    {
        ft_printf("%d", sr_map.map[index]);
        index++;
        if (index < sr_map.size)
            ft_printf(",");
    }
    ft_printf("]\n");
}

t_swap_rotate_map   make_sr_map(t_list **op_buffer)
{
    t_swap_rotate_map   map;
    t_list              *record;
    int                 map_index;

    map.map = NULL;
    record = *op_buffer;
    map.size = (((char *)record->content)[0] != 'p');
    while (((char *)record->content)[0] != 'p')
    {
        if (((char *)record->content)[0] == 's')
            (map.size)++;
        record = record->next;
    }
    if (map.size == 0)
    {
        *op_buffer = (*op_buffer)->next;
        return (map);
    }
    map.map = (int *)malloc(sizeof(int) * map.size);
    if (!map.map)
        map.size = -1;
    map_index = 0;
    record = *op_buffer;
    while (map_index < map.size)
    {
        map.map[map_index] = 0;
        while (((char *)record->content)[0] == 'r'
            && ((char *)record->content)[1] != 'r')
        {
            map.map[map_index] += 1;
            record = record->next;
        }
        while (((char *)record->content)[0] == 'r'
            && ((char *)record->content)[1] == 'r')
        {
            map.map[map_index] -= 1;
            record = record->next;
        }
        if (((char *)record->content)[0] == 's')
            record = record->next;
        map_index++;
    }
    *op_buffer = record;
    return (map);
}

t_list  *exract_a_op(t_list *op_buffer)
{
    t_list          *a_op_buffer;
    t_list          *record;
    unsigned int    index;
    size_t          op_len;

    a_op_buffer = NULL;
    record = op_buffer;
    index = 0;
    while (record != op_buffer || index == 0)
    {
        op_len = ft_strlen((char *)record->content);
        if (((char *)record->content)[0] == 'p'
            || (((char *)record->content)[op_len - 1] == 'a'))
            a_op_buffer = add_op_buffer(a_op_buffer, record->content);
        record = record->next;
        index++;
    }
    return (a_op_buffer->next);
}

t_list  *exract_b_op(t_list *op_buffer)
{
    t_list          *b_op_buffer;
    t_list          *record;
    unsigned int    index;
    size_t          op_len;

    b_op_buffer = NULL;
    record = op_buffer;
    index = 0;
    while (record != op_buffer || index == 0)
    {
        op_len = ft_strlen((char *)record->content);
        if (((char *)record->content)[0] == 'p'
            || (((char *)record->content)[op_len - 1] == 'b'))
            b_op_buffer = add_op_buffer(b_op_buffer, record->content);
        record = record->next;
        index++;
    }
    return (b_op_buffer->next);
}

// t_list  *make_optimize_op_buffer(t_list *a_op_buffer, t_list *b_op_buffer,
//     unsigned int a_buffer_size, unsigned int b_buffer_size)
// {
        
// }

t_list  *optimize_unstack(t_list *op_buffer, unsigned int op_buffer_size)
{
    (void) op_buffer_size;
    t_list  *op_buffer_a;
    t_list  *op_buffer_b;
    t_list  *a_record;
    t_list  *b_record;
    // int     start;
    // t_list  *op_optimized;

    if (!op_buffer)
        return (NULL);
    // op_optimized = NULL;
    op_buffer_a = exract_a_op(op_buffer);
    op_buffer_b = exract_b_op(op_buffer);
    // start = 0;
    a_record = op_buffer_a;
    b_record = op_buffer_b;
	print_op_buffer_a_and_b(a_record, b_record);
    print_sr_map(make_sr_map(&a_record));
    print_sr_map(make_sr_map(&b_record));

    // while(a_record != op_buffer_a && b_record != op_buffer_b && start == 0)
    // {
    //     if (((char *)a_record->content)[0] == 'p')
    //     {
            
    //     }
    // }

	print_op_buffer_a_and_b(a_record, b_record);

    ft_printf("===\n");
    print_op_buffer(op_buffer);
    return (op_buffer);
}