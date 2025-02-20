/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneves-a <nneves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:16:40 by nneves-a          #+#    #+#             */
/*   Updated: 2024/04/24 20:40:23 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;

	node = *lst;
	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		node = (*lst)->next;
		(del)((*lst)->content);
		free (*lst);
		*lst = node;
	}
}
