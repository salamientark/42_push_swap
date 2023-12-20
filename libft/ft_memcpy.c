/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:49:12 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/09 20:47:16 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_cp;
	const unsigned char	*src_cp;

	dest_cp = (unsigned char *)dest;
	src_cp = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (n-- > 0)
		*dest_cp++ = *src_cp++;
	return (dest);
}
