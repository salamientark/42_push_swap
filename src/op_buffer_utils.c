/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_buffer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:37:35 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/06 11:40:01 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

unsigned int	op_buffer_size(t_list *op_buffer)
{
	unsigned int	size;
	t_list			*record;

	if (!op_buffer)
		return (0);
	size = 1;
	record = op_buffer->next;
	while (record != op_buffer)
	{
		size++;
		record = record->next;
	}
	return (size);
}
