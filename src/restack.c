/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:18:17 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/15 09:55:02 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/* 
    Distance in rotate count OR -1 if not found
*/
int dist_from_head(t_stack *stack, unsigned int value)
{
    int             distance;
    t_stack_data    *record;

    if (stack->head->key == value)
        return (0);
    distance = 1;
    record = stack->head->next;
    while (record != stack->head)
    {
        if (record->key == value)
            return (distance);
        distance++;
        record = record->next;
    }
    return (-1);
}

// t_list  *distance_from_head_to_op_buffer();

/*
    Distance from stack_b->head to ideal spot in stack_b in rotate counting
    NOT_PRROTECTED
*/
int good_pos_in_stack(t_stack *stack, unsigned int val)
{
    t_stack_data    *record;
    unsigned int    distance;
    unsigned int    ref;

    record = stack->head;
    distance = 0;
    if (val < stack->min || stack->max < val)
    {
        ref = stack->min;
        while (record->key != ref)
        {
            distance++;
            record = record->next;
        }
    }
    else
    {
        while (!(record->prev->key < val && val < record->key))
        {
            distance++;
            record = record->next;
        }
    }
    return (distance);
}

// int best_dist(int stack_a_size, int stack_b_size,
//     int rot_a, int rot_b)
// {
//     int dist;

//     dist = abs(((stack_a_size - rot_a) - (stack_b_size - rot_b)));
//     dist = ft_min(dist, abs((stack_a_size - rot_a) -  rot_b));
//     dist = ft_min(dist, abs(rot_a -  (stack_b_size - rot_b)));
//     dist = ft_min(dist, abs(rot_a - rot_b));
//     return (dist);
// }

int best_dist(int stack_a_size, int stack_b_size,
    int rot_a, int rot_b)
{
    int dist;

    dist = ft_max(rot_a, rot_b);
    dist = ft_min(dist, rot_a + (stack_b_size - rot_b));
    dist = ft_min(dist, (stack_a_size - rot_a) + rot_b);
    dist = ft_min(dist, ft_max((stack_a_size - rot_a), (stack_b_size - rot_b)));
    return (dist);
}

int val_distance(t_stack *dest, t_stack *src, unsigned int val)
{
    int src_rotate;
    int dest_rotate;

    src_rotate = dist_from_head(src, val);
    dest_rotate = good_pos_in_stack(dest, val);
    return (best_dist(dest->size, src->size, dest_rotate, src_rotate));
}

// int best_rotate_dist(t_stack *dest, t_stack *src, unsigned int val)
// {
//     int place_in_src;
//     int place_in_dest;
//     int dist;

//     place_in_src = dist_from_head(src, val);
//     place_in_dest = good_pos_in_stack(dest, val);
//     dist = abs((((int)dest->size - place_in_dest)
//         - ((int)src->size - place_in_src)));
//     dist = ft_min(dist, abs(((int)dest->size - place_in_dest) -  place_in_src));
//     dist = ft_min(dist, abs(place_in_dest -  ((int)src->size - place_in_src + 1)));
//     dist = ft_min(dist, abs(place_in_dest - place_in_src));
//     return (dist); 
// }

int best_rotate_dist(t_stack *dest, t_stack *src, unsigned int val)
{
    int place_in_src;
    int place_in_dest;
    int dist;

    place_in_src = dist_from_head(src, val);
    place_in_dest = good_pos_in_stack(dest, val);
    dist = ft_max(place_in_dest, place_in_src);
    dist = ft_min(dist, place_in_dest + ((int)src->size - place_in_src));
    dist = ft_min(dist, ((int)dest->size - place_in_dest) + place_in_src);
    dist = ft_min(dist, ft_max((int)dest->size - place_in_dest,
        (int)src->size - place_in_src));
    return (dist); 
}

int best_head_dist(t_stack *stack, unsigned int val)
{
    int dist;
    t_stack_data    *record;

    record = stack->head;
    dist = 0;
    while (record->key != val)
    {
        dist++;
        record = record->next;
    }
    return (ft_min(dist, (stack->size - dist + 1)));
}

int best_val_insert(t_stack *dest, t_stack *src)
{
    unsigned int    val;
    int             dist;
    t_stack_data    *record;
    t_stack_data    *record_prev;

    record = src->head;
    record_prev = record->prev;
    val = src->head->key;
    dist = best_rotate_dist(dest, src, val);
    while (dist > best_head_dist(src, val) && record != record_prev)
    {
        if (best_rotate_dist(dest, src, record->key) < dist)
        {
            val = record->key;
            dist = best_rotate_dist(dest, src, record->key);
        }
        record = record->next;
        if (best_rotate_dist(dest, src, record_prev->key) < dist)
        {
            val = record_prev->key;
            dist = best_rotate_dist(dest, src, record_prev->key);
        }
        if (record_prev != record)
            record_prev = record_prev->prev;
    }
    return (val);
}

t_list  *best_insert(t_stack *dest, t_stack *src, unsigned int val)
{
    int place_in_src;
    int place_in_dest;
    unsigned int dist;
    t_list  *op_buffer;

    place_in_src = dist_from_head(src, val);
    place_in_dest = good_pos_in_stack(dest, val);
    dist = best_dist(dest->size, src->size, place_in_dest, place_in_src);
    if (dist == (unsigned int)ft_max(place_in_dest, place_in_src))
        op_buffer = lst_join(make_op_buffer(place_in_dest, "ra"),
        make_op_buffer(place_in_src, "rb"));
    else if (dist == (place_in_dest + (int)src->size - place_in_src) % src->size)
        op_buffer = lst_join(make_op_buffer(place_in_dest, "ra"),
        make_op_buffer(((int)src->size - place_in_src) % src->size, "rrb"));
    else if (dist == ((int)dest->size - place_in_dest) % dest->size + place_in_src)
        op_buffer = lst_join(make_op_buffer(((int)dest->size - place_in_dest) % dest->size, "rra"),
            make_op_buffer(place_in_src, "rb"));
    else
        op_buffer = lst_join(make_op_buffer((dest->size - place_in_dest)
            % dest->size, "rra"), make_op_buffer((src->size - place_in_src)
            % src->size, "rrb"));
    // op_buffer = op_buffer -> next
    // optimize_buffer(&op_buffer, op_buffer_size(op_buffer));
    return (op_buffer);
}

void    execute_op_buffer(t_stack *stack_a, t_stack *stack_b, t_list *op_buffer)
{
    t_list  *record;

    record = op_buffer;
    while(record->next != op_buffer)
    {
        operation(stack_a, stack_b, record->content);
        record = record->next;
    }
    operation(stack_a, stack_b, record->content);
}

t_list  *best_move(t_stack *dest, t_stack *src)
{
    unsigned int    best_val;
    t_list          *op_buffer;

    best_val = best_val_insert(dest, src);
    op_buffer = best_insert(dest, src, best_val);
    op_buffer = add_op_buffer(op_buffer, "pa");
    op_buffer = op_buffer->next;
    execute_op_buffer(dest, src, op_buffer);
    return (op_buffer);
}

// t_list  *restack(t_stack *stack_a, t_stack *stack_b)
// {
    // 
// }

// int get_next_size(t_stack stack_a, t_stack *stack_b)
// {
    
// }