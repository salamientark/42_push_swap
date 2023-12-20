/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:47:44 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/09 20:46:10 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	size_t	size;
	void	*mem;

	size = nelem * elsize;
	if (size == 0 || (size >= nelem && size >= elsize))
	{
		mem = (void *)malloc(size);
		if (mem)
			return (ft_memset(mem, '\0', size));
	}
	return (NULL);
}
