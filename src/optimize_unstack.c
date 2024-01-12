/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_unstack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:41:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/13 00:24:35 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"
#include "../libft/libft.h"


/// LIBFT

///

// void    ft_lstclear(t_list **list, void (*free)(void *));

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
    ft_printf("] SIZE : %d\n", sr_map.size);
}

void    free_sr_map(t_swap_rotate_map sr_map)
{
    free(sr_map.map);
    sr_map.map = NULL;
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

int count_operation(t_swap_rotate_map big_sr_map, t_swap_rotate_map sml_sr_map,
    int start)
{
    int op_count;
    int index;

    op_count = start;
    index = 0;
    while (index < start)
    {
        op_count += ft_abs(big_sr_map.map[index]);
        index++;
    }
    index = 0;
    while (index < sml_sr_map.size)
    {
        if (index + start < big_sr_map.size)
            op_count += ft_abs(big_sr_map.map[start + index] - sml_sr_map.map[index]);
        else
            op_count += ft_abs(sml_sr_map.map[index]);
        op_count++;
        index++;
    }
    while (index + start < big_sr_map.size)
    {
        op_count += ft_abs(big_sr_map.map[index + start]);
        index++;
        op_count += (index + start < big_sr_map.size);
    }
    return (op_count);
}

int best_start(t_swap_rotate_map a_sr_map, t_swap_rotate_map b_sr_map)
{
    t_swap_rotate_map   min;
    t_swap_rotate_map   max;
    int                 start;
    int                 min_move;
    int                 index;

    max = b_sr_map;
    min = a_sr_map;
    if (a_sr_map.size > b_sr_map.size)
    {
        max = a_sr_map;
        min = b_sr_map;
    }
    start = 0;
    min_move = count_operation(max, min, start);
    index = 1;
    while (index < max.size)
    {
        if (count_operation(max, min, index) < min_move)
        {
            min_move = count_operation(max, min, index);
            start = index;
        }
        index++;
    }
    return (start);
}

t_list  *val_to_op_buffer(int val, char stack_id)
{
    if (val > 0)
    {
        if (stack_id == 'a')
            return (make_op_buffer(val, "ra"));
        else if (stack_id == 'b')
            return (make_op_buffer(val, "rb"));
        return (make_op_buffer(val, "rr"));
    }
    if (val < 0)
    {
        if (stack_id == 'a')
            return (make_op_buffer(abs(val), "rra"));
        else if (stack_id == 'b')
            return (make_op_buffer(abs(val), "rrb"));
        return (make_op_buffer(abs(val), "rrr"));
    }
    return (NULL);
}

t_list  *opti_val_to_op_buffer(int val_a, int val_b)
{
    t_list          *op_buffer;
    unsigned int     diff;

    op_buffer = NULL;
    if (val_a > 0)
    {
        if (val_b > 0)
        {
            diff = (unsigned int) ft_min(val_a, val_b);
            op_buffer = val_to_op_buffer(diff, 'r');
            if (val_a > val_b)
                return (lst_join(op_buffer, make_op_buffer(val_a - diff, "ra")));
            return (lst_join(op_buffer, make_op_buffer(val_b - diff, "rb")));
        }
        op_buffer = make_op_buffer(val_a, "ra");
        if (val_b < 0)
            op_buffer = lst_join(op_buffer, make_op_buffer(ft_abs(val_b), "rrb"));
        return (op_buffer);
    }
    if (val_a < 0)
    {
        if (val_b < 0)
        {
            diff = (unsigned int)ft_min(ft_abs(val_a), ft_abs(val_b));
            op_buffer = val_to_op_buffer(-diff, 'r');
            if (val_a < val_b)
                return (lst_join(op_buffer, make_op_buffer(ft_abs(val_a - diff), "rra")));
            return (lst_join(op_buffer, make_op_buffer(ft_abs(val_b - diff), "rb")));
        }
        op_buffer = make_op_buffer(ft_abs(val_a), "rra");
        if (val_b > 0)
            op_buffer = lst_join(op_buffer, make_op_buffer(val_b, "rb"));
        return (op_buffer);
    }
    if (val_b > 0)
        return (make_op_buffer(val_b, "rb"));
    return (make_op_buffer(ft_abs(val_b), "rrb"));
}

char    *best_swap(int index, int start, int a_size, int b_size)
{
    if (index < a_size && index + start < b_size)
        return ("ss");
    if (index < a_size)
        return ("sa");
    return ("sb");
}

/* b is bigger than a 
*/
t_list  *sr_map_to_op_buffer_a_smaller(t_swap_rotate_map a_sr_map,
    t_swap_rotate_map b_sr_map)
{
    int     index;
    int     start;
    t_list  *op_buffer;

    start = best_start(a_sr_map, b_sr_map);
    index = 0;
    op_buffer = NULL;
    while (index < start)
    {
        op_buffer = lst_join(op_buffer,
            val_to_op_buffer(b_sr_map.map[index], 'b'));
        index++;
        if (index < start)
            op_buffer = add_op_buffer(op_buffer, "sb");
    }
    index = 0;
    while (index < a_sr_map.size)
    {
        if (index + start < b_sr_map.size)
            op_buffer = lst_join(op_buffer,
                opti_val_to_op_buffer(a_sr_map.map[index],
                b_sr_map.map[start + index]));
        else
            op_buffer = lst_join(op_buffer, val_to_op_buffer(a_sr_map.map[index], 'a'));
        index++;
        if (index < a_sr_map.size || start + index < b_sr_map.size)
            op_buffer = add_op_buffer(op_buffer, best_swap(index, start, a_sr_map.size, b_sr_map.size));
    }
    while (index + start < b_sr_map.size)
    {
        op_buffer = lst_join(op_buffer,
            val_to_op_buffer(b_sr_map.map[index + start], 'b'));
        index++;
        if (index + start < b_sr_map.size)
            op_buffer = add_op_buffer(op_buffer, "sb");
    }
    return (op_buffer->next);
}



t_list  *optimize_unstack(t_list *op_buffer, unsigned int op_buffer_size)
{
    (void) op_buffer_size;
    t_list  *op_buffer_a;
    t_list  *op_buffer_b;
    t_list  *a_record;
    t_list  *b_record;
    t_list  *final_op_buffer;
    t_swap_rotate_map   a_sr_map;
    t_swap_rotate_map   b_sr_map;
    int     start;
    // t_list  *op_optimized;

    if (!op_buffer)
        return (NULL);
    // op_optimized = NULL;
    op_buffer_a = exract_a_op(op_buffer);
    op_buffer_b = exract_b_op(op_buffer);
    start = 0;
    a_record = op_buffer_a;
    b_record = op_buffer_b;
    final_op_buffer = NULL;
    while ((a_record != op_buffer_a && b_record != op_buffer_b) || start == 0)
    {
        if (((char *)a_record->content)[0] == 'p' && ((char *)b_record->content)[0] == 'p')
        {
            final_op_buffer = add_op_buffer(final_op_buffer, "pb");
            if (a_record != op_buffer_a || start == 0)
                a_record = a_record->next;
            if (b_record != op_buffer_b || start == 0)
                b_record = b_record->next;
            start++;        
        }
        else
        {
            a_sr_map = make_sr_map(&a_record);
            b_sr_map = make_sr_map(&b_record);
            final_op_buffer = lst_join(final_op_buffer, sr_map_to_op_buffer_a_smaller(a_sr_map, b_sr_map));
            free(a_sr_map.map);
            a_sr_map.map = NULL;
            free(b_sr_map.map);
            b_sr_map.map = NULL;
        }
        
    }
    free_sr_map(a_sr_map);
    free_sr_map(b_sr_map);
    free_op_buffer(&op_buffer_a, NULL);
    free_op_buffer(&op_buffer_b, NULL);
    final_op_buffer = final_op_buffer->next;
    op_buffer = final_op_buffer;
    return (op_buffer);
}