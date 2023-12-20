/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:48:38 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/07 09:48:39 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*pos;

	if (lst && *lst)
	{
		pos = *lst;
		while (pos)
		{
			pos = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = pos;
		}
		*lst = NULL;
	}
}
