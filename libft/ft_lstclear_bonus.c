/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:10:55 by yihssan           #+#    #+#             */
/*   Updated: 2019/10/10 21:46:14 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*after;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		after = list->next;
		(*del)(list->content);
		free(list);
		list = after;
	}
	*lst = NULL;
}
